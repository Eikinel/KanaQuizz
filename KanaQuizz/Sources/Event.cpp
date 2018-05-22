#include "Event.h"
#include "Screen.h"
#include "Button.h"
#include "Kana.h"
#include <sstream>

//CONSTRUCTORS
IEvent::IEvent()
{
	for (int i = eToggleable::BUTTON; i < eToggleable::SIZE_TOGGLEABLE; i++)
		this->_toggleable_entities.push_back(true);
	this->_general_clock.restart();
}

WindowDefaultEvent::WindowDefaultEvent()
{
	std::cout << "Creating window default event" << std::endl;
}

MenuEvent::MenuEvent()
{
	std::cout << "Creating menu event" << std::endl;
}

QuizzEvent::QuizzEvent()
{
	std::cout << "Creating quizz event" << std::endl;
	this->_quizz_clock.restart();
	this->_input_bar_clock.restart();
	this->_has_answered = false;
	if (COUNTDOWN_SEC > 0)
		this->_countdown_finished = false;
	else
		this->_countdown_finished = true;
	this->_hint_given = 0;
	this->_penalty = SCORE_BASE;
}

QuizzEvent::~QuizzEvent()
{
	std::cout << "Deleting GameEvent subevents" << std::endl;
}


//UPDATE & DRAW METHODS
int		WindowDefaultEvent::update(Screen& screen, sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		return (EXIT);
		break;
	case sf::Event::MouseMoved:
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(screen.getWindow());

		//Highlight buttons on mouse hover
		for (auto it : screen.getButtons())
		{
			if (!it->getHoverState() && it->isHovered(mouse_pos))
				for (int i = 0; i < it->getEventsByType(eEventType::HOVER).size(); i++)
					it->triggerEvent(eEventType::HOVER, i);
			else if (it->getHoverState() && !it->isHovered(mouse_pos))
				for (int i = 0; i < it->getEventsByType(eEventType::UNHOVER).size(); i++)
					it->triggerEvent(eEventType::UNHOVER, i);
		}
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		if (event.mouseButton.button == sf::Mouse::Button::Left)
		{
			int status = screen.getIndex();

			std::cout << Screen::gamestate_name[screen.getState()] << "Event : left click at position : [" <<
			event.mouseButton.x << " ; " << event.mouseButton.y << "]." << std::endl;

			for (auto it : screen.getButtons())
			{
				if (it->isHovered(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
					for (int i = 0; i < it->getEventsByType(eEventType::CLICK).size(); i++)
						if ((status = it->triggerEvent(eEventType::CLICK, i)) != screen.getIndex())
							return (status);
			}
		}
		break;
	}
	default:
		break;
	}

	return (screen.getIndex());
}

int		MenuEvent::update(Screen& screen, sf::Event& event)
{
	MenuScreen*	mscreen = static_cast<MenuScreen *>(&screen);

	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			return (EXIT);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return (screen.getIndex());
}

void		MenuEvent::draw(Screen& screen)
{
	MenuScreen*	mscreen = static_cast<MenuScreen *>(&screen);

	mscreen->draw(mscreen->getGreyRectTitle());
	mscreen->draw(mscreen->getTitleImage());
	for (auto it : mscreen->getButtons())
		mscreen->draw(it->getText());
}

int		QuizzEvent::update(Screen& screen, sf::Event& event)
{
	QuizzScreen*	qscreen = static_cast<QuizzScreen *>(&screen);
	int				status = screen.getIndex();

	// If the game is launched, change countdown value
	if (!this->_countdown_finished)
	{
		float ct = (COUNTDOWN_SEC + 1) - this->_quizz_clock.getElapsedTime().asSeconds();

		if (ct > 1.f)
		{
			if (qscreen->getCountdownText().getString().toAnsiString() != std::to_string((int)ct))
				qscreen->setCountdownText(std::to_string((int)ct));
		}
		else if (ct > 0.f)
		{
			if (qscreen->getCountdownText().getString().toAnsiString() != COUNTDOWN_GO)
				qscreen->setCountdownText(COUNTDOWN_GO);
		}
		else
			this->_countdown_finished = true;
	}
	else
	{
		// Handle user event
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			// Remove a letter if it exists
			case sf::Keyboard::Backspace:
				qscreen->removeCharToInput();
				qscreen->centerTextElements();
				this->_input_bar_clock.restart();
				break;
			// Submit an answer
			case sf::Keyboard::Return:
			{
				if (!this->_has_answered)
				{
					const std::vector<std::string> romaji = qscreen->getSelectedKanaTable().getRomajiByID(qscreen->getSelectedKanaID());
					bool answer = false;

					// Check if the input submitted is the same as the romaji
					// In case of multiple romaji, if one is right then it's correct
					// The romaji is case sensitive, depending if it's a Hiragana (lower) or a Katakana (upper)
					for (int i = 0; i < MAX_ROMAJI; i++)
					{
						if (!romaji[i].empty())
						{
							std::cout << "Answer is '" << romaji[i] << "'" << std::endl;
							if (qscreen->getInputText().getString().toAnsiString() == romaji[i])
							{
								answer = true;
								break;
							}
						}
					}

					int score = (answer ? 1 : -1) * SCORE_POINT + this->_penalty;
					qscreen->addScoreToTotal(score);
					qscreen->updateUIWithAnswer(answer, score);
					this->_has_answered = true;
					this->_answer_time = this->_quizz_clock.getElapsedTime();
					break;
				}
			}
			default:
				break;
			}
			break;
		case sf::Event::TextEntered:
			// Process user input only when he's still answering
			if (!this->_has_answered)
			{
				// Between A-Za-z, write on the screen
				if ((event.key.code >= 65 && event.text.unicode <= 90) ||
					(event.key.code >= 97 && event.text.unicode <= 122))
				{
					qscreen->addCharToInput(event.text.unicode);
					qscreen->centerTextElements();
					this->_input_bar_clock.restart();
				}
			}
		default:
			break;
		}

		// After an answer, wait a second and change kana
		if (this->_has_answered &&
			this->_quizz_clock.getElapsedTime().asSeconds() - this->_answer_time.asSeconds() >= 1)
		{
			qscreen->cleanInput();
			qscreen->centerTextElements();
			qscreen->setRandomKana();
			qscreen->setHintText("");
			this->_hint_given = 0;
			this->_penalty = SCORE_BASE;
			this->_has_answered = false;
		}
	}

	return (status);
}

void	QuizzEvent::draw(Screen& screen)
{
	QuizzScreen*	qscreen = static_cast<QuizzScreen *>(&screen);

	if (!this->_countdown_finished)
		qscreen->draw(qscreen->getCountdownText());
	else
	{
		qscreen->draw(qscreen->getSelectedKanaSprite());
		qscreen->draw(qscreen->getInputBackground());
		if ((int)this->_input_bar_clock.getElapsedTime().asSeconds() % 2 == 0)
			qscreen->draw(qscreen->getInputBar());
		qscreen->draw(qscreen->getInputText());
		qscreen->draw(qscreen->getHintText());

		if (this->_has_answered &&
			this->_quizz_clock.getElapsedTime().asSeconds() - this->_answer_time.asSeconds() <= 1)
		{
			qscreen->draw(qscreen->getCorrectionText());
			qscreen->draw(qscreen->getScoreTextByID(eScoreUI::SCORE_ADD_UI));
		}
		for (int i = 0; i < qscreen->getScoreTexts().size(); i++)
			if (i != eScoreUI::SCORE_ADD_UI)
				qscreen->draw(qscreen->getScoreTextByID(i));
		for (auto it : qscreen->getButtons())
			qscreen->draw(it->getText());
	}
}


//GETTERS
std::vector<bool>&	IEvent::getToggleableEntities()
{
	return (this->_toggleable_entities);
}


//SETTERS
void	IEvent::setToggleableEntities(const std::vector<bool>& toggleable_entities)
{
	this->_toggleable_entities = toggleable_entities;
}


//METHODS
int	IEvent::changeScreen(Screen* screen, eGamestate gamestate)
{
	int	index;

	if (gamestate == eGamestate::EXIT)
		return (gamestate);
	
	// Check if a screen with the gamestate passed as parameter already exist.
	// If true, copy options and return the gamestate.
	// Else, create the screen before performing operations.
	for (auto it : all_screens)
	{
		if (it->getState() == gamestate)
		{
			if (it->getEvents()[1]->getToggleableEntities() != this->_toggleable_entities)
			{
				std::cout << "Replacing old options" << std::endl;
				it->getEvents()[1]->setToggleableEntities(this->_toggleable_entities);
			}
			std::cout << "Switching screen to " << Screen::gamestate_name[(int)gamestate] <<
				" at index " << it->getIndex() << "." << std::endl << std::endl;
			// If the player switch from quizz to menu, make a delete request
			// It will be executed once the screen finished to switch
			return (it->getIndex());
		}
	}
	index = this->createScreen(screen, gamestate);
	std::cout << "Switching screen to " << Screen::gamestate_name[(int)gamestate] <<
		" at index " << index << "." << std::endl << std::endl;
	return (index);
}

int	IEvent::createScreen(Screen* screen, eGamestate gamestate)
{
	Screen*	new_screen = NULL;

	std::cout << std::endl << "Creating new " << Screen::gamestate_name[(int)gamestate] << "." << std::endl;

	if (gamestate == MENU)
		new_screen = new MenuScreen(screen->getWindow());
	else if (gamestate == OPTIONS)
		new_screen = NULL;//new OptionsScreen(screen->getWindow());
	else
		new_screen = new QuizzScreen(screen->getWindow());
	// Need to do a function to pass all options
	new_screen->getEvents()[1]->setToggleableEntities(this->_toggleable_entities);
	all_screens.push_back(new_screen);
	return (new_screen->getIndex());
}

int		IEvent::addScreenToDeleteQueue(Screen* to_remove)
{
	std::cout << "Added " << Screen::gamestate_name[to_remove->getState()] << " screen to the delete queue" << std::endl;
	delete_queue = to_remove;
		
	return (to_remove->getIndex());
}

int		IEvent::changeButtonColor(Button* button, const sf::Color color)
{
	sf::Text *tmp = new sf::Text(button->getText());

	tmp->setFillColor(color);
	button->setText(*tmp);
	delete(tmp);

	return 0;
}

int	QuizzEvent::giveHint(QuizzScreen* qscreen)
{
	const eKana kana = qscreen->getSelectedKanaID();
	const eKanaType type = qscreen->getSelectedKanaType();
	const std::vector<std::string> romaji = qscreen->getSelectedKanaTable().getRomajiByID(qscreen->getSelectedKanaID());
	std::stringstream hint;

	this->_hint_given < romaji[0].length() ? this->_hint_given++ : 0;
	for (int i = 0; i < this->_hint_given; i++)
		hint << romaji[0][i];
	this->_penalty = SCORE_PENALTY * this->_hint_given;
	if (this->_hint_given == romaji[0].length() && !romaji[1].empty())
		hint << " (" << romaji[1] << ")";
	qscreen->setHintText(hint.str());
	std::cout << "Hint is now '" << hint.str() << "'" << std::endl;

	return (qscreen->getIndex());
}