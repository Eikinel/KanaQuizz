#pragma once

#include "Constants.h"

enum	eGamestate;
enum	eKana;
enum	eKanaType;
class	Screen;
class	QuizzScreen;
class	Button;

enum	eToggleable
{
	BUTTON,
	SIZE_TOGGLEABLE
};

class				IEvent
{
public:
	IEvent();
	virtual ~IEvent() {}

	virtual int		update(Screen& screen, sf::Event& event) = 0;
	virtual void	draw(Screen& screen) = 0;

	//GETTERS
	virtual std::vector<bool>&	getToggleableEntities();

	//SETTERS
	virtual	void	setToggleableEntities(const std::vector<bool>& toggleable_entities);

	//METHODS
	virtual int	changeScreen(Screen* screen, eGamestate gamestate);
	virtual int	createScreen(Screen* screen, eGamestate gamestate);
	virtual int addScreenToDeleteQueue(Screen* to_remove);
	virtual int changeButtonColor(Button* button, const sf::Color color);

protected:
	std::vector<bool>		_toggleable_entities;
	sf::Clock				_general_clock;
};

class				WindowDefaultEvent : public IEvent
{
public:
	WindowDefaultEvent();

	virtual int		update(Screen& screen, sf::Event& event);
	virtual void	draw(Screen& screen) {}
};

class				MenuEvent : public IEvent
{
public:
	MenuEvent();

	virtual int		update(Screen& screen, sf::Event& event);
	virtual void	draw(Screen& screen);
};

class				QuizzEvent : public IEvent
{
public:
	QuizzEvent();
	virtual ~QuizzEvent();

	virtual int		update(Screen& screen, sf::Event& event);
	virtual void	draw(Screen& screen);

	virtual int		giveHint(QuizzScreen* qscreen);

private:
	sf::Clock			_quizz_clock;
	sf::Clock			_input_bar_clock;
	sf::Time			_answer_time;
	bool				_has_answered;
	bool				_countdown_finished;
	int					_penalty;
	unsigned int		_hint_given;
};