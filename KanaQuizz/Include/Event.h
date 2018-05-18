#pragma once

#include "Constants.h"

enum	eGamestate;
enum	eAccuracy;
class	IScreen;
class	QuizzScreen;
class	Note;
class	Phase;
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

	virtual int		update(IScreen& screen, sf::Event& event) = 0;
	virtual void	draw(IScreen& screen) = 0;

	//GETTERS
	virtual std::vector<bool>&	getToggleableEntities();

	//SETTERS
	virtual	void	setToggleableEntities(const std::vector<bool>& toggleable_entities);

	//METHODS
	virtual int	changeScreen(eGamestate gamestate, IScreen* screen);
	virtual int	createScreen(eGamestate gamestate, IScreen* screen);
	virtual int changeButtonColor(Button* button, const sf::Color color);

protected:
	std::vector<bool>	_toggleable_entities;
	sf::Clock			_general_clock;
};

class				WindowDefaultEvent : public IEvent
{
public:
	WindowDefaultEvent();

	virtual int		update(IScreen& screen, sf::Event& event);
	virtual void	draw(IScreen& screen) {}
};

class				MenuEvent : public IEvent
{
public:
	MenuEvent();

	virtual int		update(IScreen& screen, sf::Event& event);
	virtual void	draw(IScreen& screen);
};

class				QuizzEvent : public IEvent
{
public:
	QuizzEvent();
	virtual ~QuizzEvent();

	virtual int		update(IScreen& screen, sf::Event& event);
	virtual void	draw(IScreen& screen);

private:
	sf::Clock	_quizz_clock;
	sf::Clock	_input_bar_clock;
	sf::Time	_answer_time;
	bool		_has_answered;
	bool		_countdown_finished;
	void		updateUIAnswer(QuizzScreen* screen, const bool answer);
};

// NOT COOL, MUST BE INSIDE BUTTON.H