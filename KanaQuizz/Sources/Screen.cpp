#include "Screen.h"
#include "Event.h"
#include "Button.h"
#include "Kana.h"
#include <sstream>

IScreen::IScreen(sf::RenderWindow& window, eGamestate state) : _window(window), _state(state)
{
	std::string					type[3] = { "menu", "options", "quizz" };
	std::vector<sf::Color>		color_chart(eColorChart::SIZE_COLOR_CHART);
	std::vector<unsigned int>	text_sizes(eTextSize::SIZE_TEXT_SIZE);
	sf::Vector2f				win_size(window.getSize());

	std::cout << "Creating " << type[(int)state] << " screen with index " << this->_index << "." << std::endl;

	this->_index = all_screens.size();
	this->_events.push_back(new WindowDefaultEvent); // Event handler for options, close window, buttons, etc.
	if (!this->_unicode_font.loadFromFile(FONTS_DIR"/Arial_Unicode.TTF"))
		std::cerr << "Failed to load font " << FONTS_DIR"/Arial_Unicode.TTF" << std::endl;
	if (!this->_fancy_font.loadFromFile(FONTS_DIR"/Lato-Regular.ttf"))
		std::cerr << "Failed to load font " << FONTS_DIR"/Lato-Regular.ttf" << std::endl;

	color_chart[eColorChart::PRIMARY_BACKGROUND] = sf::Color(21, 21, 21);
	color_chart[eColorChart::SECONDARY_BACKGROUND] = sf::Color(10, 10, 10);
	color_chart[eColorChart::TEXT_NORMAL] = sf::Color(255, 250, 220);
	color_chart[eColorChart::TEXT_HIGHLIGHT] = sf::Color(114, 137, 218);
	color_chart[eColorChart::TEXT_GREEN] = sf::Color(90, 175, 10);
	color_chart[eColorChart::TEXT_YELLOW] = sf::Color(250, 220, 5);
	color_chart[eColorChart::TEXT_RED] = sf::Color(175, 10, 10);
	this->_color_chart = color_chart;

	text_sizes[eTextSize::TINY] = win_size.y / 32.f;
	text_sizes[eTextSize::SMALL] = win_size.y / 18.f;
	text_sizes[eTextSize::AVERAGE] = win_size.y / 12.f;
	text_sizes[eTextSize::LARGE] = win_size.y / 8.f;
	text_sizes[eTextSize::EXTRA_LARGE] = win_size.y / 4.f;
	this->_text_sizes = text_sizes;
}

MenuScreen::MenuScreen(sf::RenderWindow& window) : IScreen(window, MENU)
{
	this->_events.push_back(new MenuEvent); // Update menu, draw it and react in terms of user inputs.

	sf::Vector2f	win_size(window.getSize());

	this->_grey_rect_title.setSize(sf::Vector2f(win_size.x, win_size.y / 3.f));
	this->_grey_rect_title.setFillColor(sf::Color(10, 10, 10));
	this->_title_texture.loadFromFile(SPRITES_DIR"/game_title.png");
	this->_title.setTexture(this->_title_texture);
	this->_title.setOrigin(this->_title.getGlobalBounds().width / 2, this->_title.getGlobalBounds().height / 2);
	this->_title.setPosition(sf::Vector2f(
		win_size.x / 2.f,
		win_size.y / 6.f));
	this->_buttons.push_back(new Button("Start quizz", this->_text_sizes[eTextSize::AVERAGE], this->_fancy_font, sf::Vector2f(
		win_size.x / 2.f,
		win_size.y / 2.1f), CENTER_X, CENTER_Y));
	this->_buttons.push_back(new Button("Options", this->_text_sizes[eTextSize::AVERAGE], this->_fancy_font, sf::Vector2f(
		win_size.x / 2.f,
		win_size.y / 1.52f), CENTER_X, CENTER_Y));
	this->_buttons.push_back(new Button("Exit", this->_text_sizes[eTextSize::AVERAGE], this->_fancy_font, sf::Vector2f(
		win_size.x / 2.f,
		win_size.y / 1.2f), CENTER_X, CENTER_Y));
	this->_buttons[0]->onClick(&IEvent::changeScreen, this->_events[1], QUIZZ, static_cast<IScreen *>(this));
	this->_buttons[1]->onClick(&IEvent::changeScreen, this->_events[1], OPTIONS, static_cast<IScreen *>(this));
	this->_buttons[2]->onClick(&IEvent::changeScreen, this->_events[1], EXIT, static_cast<IScreen *>(this));

	for (auto it : this->_buttons)
	{
		it->onHover(&IEvent::changeButtonColor, this->_events[1], it, this->_color_chart[eColorChart::TEXT_HIGHLIGHT]);
		it->onUnhover(&IEvent::changeButtonColor, this->_events[1], it, this->_color_chart[eColorChart::TEXT_NORMAL]);
	}
}

QuizzScreen::QuizzScreen(sf::RenderWindow& window) : IScreen(window, QUIZZ)
{
	this->_events.push_back(new QuizzEvent); // Update menu, draw it and react in terms of user inputs.
	std::srand((unsigned int)std::time(nullptr)); // Randomize kana order

	sf::Vector2f	win_size(window.getSize());

	//Initialize a countdown before the quizz begin
	this->_coutdown_text.setFont(this->_fancy_font);
	this->_coutdown_text.setCharacterSize(this->_text_sizes[eTextSize::EXTRA_LARGE]);
	this->_coutdown_text.setFillColor(this->_color_chart[eColorChart::TEXT_NORMAL]);

	// Button initialization
	this->_buttons.push_back(new Button("Back to menu", this->_text_sizes[eTextSize::TINY], this->_fancy_font, sf::Vector2f(
		win_size.x / 48.f,
		win_size.y - win_size.y / 24.f), LEFT, BOTTOM));
	this->_buttons.push_back(new Button("Hint", this->_text_sizes[eTextSize::AVERAGE], this->_fancy_font, sf::Vector2f(
		win_size.x / 2.f,
		win_size.y - win_size.y / 24.f), CENTER_X, BOTTOM));
	this->_buttons[0]->onClick(&IEvent::changeScreen, this->_events[1], MENU, static_cast<IScreen *>(this));
	//this->_buttons[1]->onClick(&IEvent::giveHint, this->_events[1], static_cast<IScreen *>(this));

	for (auto it : this->_buttons)
	{
		it->onHover(&IEvent::changeButtonColor, this->_events[1], it, this->_color_chart[eColorChart::TEXT_HIGHLIGHT]);
		it->onUnhover(&IEvent::changeButtonColor, this->_events[1], it, this->_color_chart[eColorChart::TEXT_NORMAL]);
	}

	//Set basic info for kana SFML text form
	this->_kana_text.setFont(this->_unicode_font);
	this->_kana_text.setCharacterSize(this->_text_sizes[eTextSize::EXTRA_LARGE]);
	this->_kana_text.setFillColor(this->_color_chart[eColorChart::TEXT_NORMAL]);
	this->setRandomKana();

	//Initialize the user input field
	this->_input = "";

	this->_input_background.setSize(sf::Vector2f(win_size.x, win_size.y / 6.f));
	this->_input_background.setOrigin(sf::Vector2f(
		this->_input_background.getGlobalBounds().width / 2,
		this->_input_background.getGlobalBounds().height / 2));
	this->_input_background.setPosition(sf::Vector2f(win_size.x / 2, win_size.y / 1.5f));
	this->_input_background.setFillColor(this->_color_chart[eColorChart::SECONDARY_BACKGROUND]);

	sf::FloatRect input_bg_rect = this->_input_background.getGlobalBounds();

	this->_input_text.setFont(this->_fancy_font);
	this->_input_text.setCharacterSize(this->_text_sizes[eTextSize::LARGE]);
	this->_input_text.setOrigin(sf::Vector2f(
		this->_input_text.getGlobalBounds().width / 2.f,
		0));
	this->_input_text.setPosition(sf::Vector2f(
		input_bg_rect.left + input_bg_rect.width / 2.f,
		input_bg_rect.top - input_bg_rect.height / 25.f));
	this->_input_text.setFillColor(this->_color_chart[eColorChart::TEXT_NORMAL]);

	this->_input_bar.setSize(sf::Vector2f(4, input_bg_rect.height / 1.75f));
	this->_input_bar.setOrigin(sf::Vector2f(
		this->_input_bar.getGlobalBounds().width / 2,
		this->_input_bar.getGlobalBounds().height / 2));
	this->_input_bar.setPosition(sf::Vector2f(
		this->_input_text.getGlobalBounds().left,
		input_bg_rect.top + input_bg_rect.height / 2.f));
	this->_input_bar.setFillColor(this->_color_chart[eColorChart::TEXT_NORMAL]);

	//Create right/wrong text displayed when the user submit an answer
	this->_correction_text.setFont(this->_fancy_font);
	this->_correction_text.setCharacterSize(this->_text_sizes[eTextSize::SMALL]);

	//Score managing
	this->_answers = std::vector<bool>();
	this->_answer_ct_texts = std::vector<sf::Text>(2);
	for (int i = 0; i < 2; i++)
	{
		this->_answer_ct_texts[i].setFont(this->_fancy_font);
		this->_answer_ct_texts[i].setCharacterSize(this->_text_sizes[eTextSize::TINY]);
		this->_answer_ct_texts[i].setFillColor(this->_color_chart[eColorChart::TEXT_NORMAL]);
		this->_answer_ct_texts[i].setPosition(sf::Vector2f(
			win_size.x / 48.f,
			i * this->_text_sizes[eTextSize::TINY] * 2 + win_size.y / 24.f));
	}
	std::stringstream ss;

	ss << RIGHT_COUNTER << "0";
	this->_answer_ct_texts[0].setString(ss.str());
	ss.str("");
	ss << WRONG_COUNTER << "0";
	this->_answer_ct_texts[1].setString(ss.str());
}

IScreen::~IScreen()
{
	std::cout << "Deleting window events" << std::endl;
	for (auto it : this->_events)
		delete(it);
	for (auto it : this->_buttons)
		delete (it);
}

MenuScreen::~MenuScreen()
{
	std::cout << "Deleting menu screen" << std::endl;
}

QuizzScreen::~QuizzScreen()
{
	std::cout << "Deleting menu screen" << std::endl;
}


//METHODS
int		IScreen::run()
{
	int			status;
	sf::Event	event;
	bool		user_input;

	while (user_input = this->_window.pollEvent(event))
	{
		for (auto it : this->_events)
		{
			if ((status = it->update(*this, event)) != this->_index)
				return (status);
		}
	}
	
	// Allow the game to continue even if no user input is given
	if (!user_input)
		this->_events[1]->update(*this, sf::Event());

	this->_window.clear(this->_color_chart[eColorChart::PRIMARY_BACKGROUND]);
	for (auto it : this->_events)
		it->draw(*this);
	this->_window.display();

	return (this->_index);
}

void	IScreen::draw(const sf::Drawable& object, sf::RenderStates states)
{
	this->_window.draw(object, states);
}


//GETTERS
sf::RenderWindow&		IScreen::getWindow()
{
	return (this->_window);
}

std::vector<IEvent *>&	IScreen::getEvents()
{
	return (this->_events);
}

eGamestate				IScreen::getState() const
{
	return (this->_state);
}

const sf::Font&			IScreen::getUnicodeFont() const
{
	return (this->_unicode_font);
}

const sf::Font&			IScreen::getFancyFont() const
{
	return (this->_fancy_font);
}

const unsigned int		IScreen::getIndex() const
{
	return (this->_index);
}

const std::vector<sf::Color>	IScreen::getColorChart() const
{
	return (this->_color_chart);
}

const std::vector<Button *>&	IScreen::getButtons() const
{
	return (this->_buttons);
}


const sf::RectangleShape&	MenuScreen::getGreyRectTitle() const
{
	return (this->_grey_rect_title);
}

const sf::Sprite&		MenuScreen::getTitleImage() const
{
	return (this->_title);
}


const eKana		QuizzScreen::getRandomKanaID() const
{
	return (this->_random_kana);
}

const sf::Text&		QuizzScreen::getKanaText() const
{
	return (this->_kana_text);
}

const sf::Text&		QuizzScreen::getInputText() const
{
	return (this->_input_text);
}

const sf::RectangleShape&	QuizzScreen::getInputBackground() const
{
	return (this->_input_background);
}

const sf::RectangleShape&	QuizzScreen::getInputBar() const
{
	return (this->_input_bar);
}

const sf::Text&		QuizzScreen::getCorrectionText() const
{
	return (this->_correction_text);
}

const std::vector<bool>&	QuizzScreen::getAnswerCounter() const
{
	return (this->_answers);
}

const unsigned int		QuizzScreen::getAnswerNumberByType(const bool type) const
{
	unsigned int i = 0;

	for (auto it : this->_answers)
		if (it == type)
			i++;

	return (i);
}

const std::vector<sf::Text>& 	QuizzScreen::getAnswerCountersTexts() const
{
	return (this->_answer_ct_texts);
}

const sf::Text&		QuizzScreen::getCountdownText() const
{
	return (this->_coutdown_text);
}


//SETTERS
void	QuizzScreen::setInputUser(const std::string& input)
{
	this->_input = input;
}

void	QuizzScreen::setRandomKana()
{
	this->_random_kana = (eKana)(std::rand() % eKana::KANA_SIZE);

	this->_kana_text.setString(Hiragana::kana(this->_random_kana));
	this->_kana_text.setOrigin(sf::Vector2f());
	this->_kana_text.setPosition(sf::Vector2f());
	this->_kana_text.setOrigin(sf::Vector2f(
		this->_kana_text.getGlobalBounds().left + this->_kana_text.getGlobalBounds().width / 2.f,
		this->_kana_text.getGlobalBounds().top + this->_kana_text.getGlobalBounds().height / 2.f));
	this->_kana_text.setPosition(sf::Vector2f(
		this->_window.getSize().x / 2.f,
		this->_window.getSize().y / 3.5f));
}

void	QuizzScreen::setCorrectionText(const sf::Text& correction_text)
{
	this->_correction_text = correction_text;
	
	this->_correction_text.setOrigin(sf::Vector2f());
	this->_correction_text.setPosition(sf::Vector2f());
	this->_correction_text.setOrigin(sf::Vector2f(
		this->_correction_text.getGlobalBounds().left + this->_correction_text.getGlobalBounds().width / 2.f,
		this->_correction_text.getGlobalBounds().top + this->_correction_text.getGlobalBounds().height / 2.f));
	this->_correction_text.setPosition(sf::Vector2f(
		this->_window.getSize().x / 2.f,
		this->_window.getSize().y / 2.1f));
}

void	QuizzScreen::setAnswerCountersTexts(const std::vector<sf::Text>& answer_ct_texts)
{
	this->_answer_ct_texts = answer_ct_texts;
}

void	QuizzScreen::setCountdownText(const std::string& countdown_text)
{
	this->_coutdown_text.setString(countdown_text);
	this->_coutdown_text.setOrigin(sf::Vector2f(
		this->_coutdown_text.getGlobalBounds().width / 2.f,
		this->_coutdown_text.getGlobalBounds().height / 2.f));
	this->_coutdown_text.setPosition(sf::Vector2f(
		this->_window.getSize().x / 2.f,
		this->_window.getSize().y / 2.f - this->_coutdown_text.getGlobalBounds().height / 2.f));
}


//METHODS
void	QuizzScreen::addCharToInput(const sf::Uint32& c_input)
{
	this->_input.push_back(c_input);
	this->_input_text.setString(this->_input);
}

void	QuizzScreen::removeCharToInput()
{
	if (this->_input.size() > 0)
	{
		this->_input.pop_back();
		this->_input_text.setString(this->_input);
	}
}

void	QuizzScreen::cleanInput()
{
	this->_input = "";
	this->_input_text.setString(this->_input);
}

void	QuizzScreen::centerTextElements()
{
	sf::FloatRect input_bg_rect = this->_input_background.getGlobalBounds();

	this->_input_text.setOrigin(sf::Vector2f(
		this->_input_text.getGlobalBounds().width / 2.f,
		0));
	this->_input_text.setPosition(sf::Vector2f(
		input_bg_rect.left + input_bg_rect.width / 2.f,
		input_bg_rect.top - input_bg_rect.height / 25.f));
	this->_input_bar.setPosition(sf::Vector2f(
		this->_input_text.getGlobalBounds().left + (this->_input.size() > 0 ? this->_input_text.getGlobalBounds().width + 20 : 0),
		input_bg_rect.top + input_bg_rect.height / 2.f));
}

void	QuizzScreen::addAnswer(const bool answer)
{
	this->_answers.push_back(answer);
}

const char* IScreen::gamestate_name[eGamestate::SIZE_GAMESTATE] = { "Menu", "Options", "Quizz" };