#pragma once

# include "Constants.h"
# include <functional>

enum eGamestate;

enum	eIndentX
{
	LEFT = 0,
	CENTER_X,
	RIGHT,
	INDENT_X_SIZE
};

enum	eIndentY
{
	TOP = 0,
	CENTER_Y,
	BOTTOM,
	INDENT_Y_SIZE
};

enum	eEventType
{
	CLICK,
	HOVER,
	UNHOVER,
	EVENT_TYPE_SIZE
};

class	Button
{
public:
	Button(const std::string& text, const unsigned int& size, const sf::Font& font, const sf::Vector2f& pos = sf::Vector2f(0, 0),
		const eIndentX& indent_x = LEFT, const eIndentY& indent_y = TOP, const sf::Texture& texture = sf::Texture());
	Button(const Button& other);
	virtual ~Button();

	//GETTERS
	virtual const sf::Text&	getText() const;
	virtual const std::vector<std::function<int()>>&	Button::getEvents() const;
	virtual const bool getHoverState() const;

	//SETTERS
	void	setText(const sf::Text& text);
	void	setEvent(const std::vector<std::function<int()>> events);
	void	setEventByType(const std::function<int()> event, const eEventType event_type);

	//METHODS
	template <typename U, typename... T> void onClick(int (U::*func)(int, T...), U* event, int index, T... params)
	{
		this->_events[eEventType::CLICK] = std::bind(func, event, index, params...);
	}
	template <typename U, typename... T> void onClick(int (U::*func)(eGamestate, T...), U* event, eGamestate gamestate, T... params)
	{
		this->_events[eEventType::CLICK] = std::bind(func, event, gamestate, params...);
	}
	template <typename U, typename... T> void onHover(int (U::*func)(Button*, T...), U* event, Button* button, T... params)
	{
		this->_events[eEventType::HOVER] = std::bind(func, event, button, params...);
	}
	template <typename U, typename... T> void onUnhover(int (U::*func)(Button*, T...), U* event, Button* button, T... params)
	{
		this->_events[eEventType::UNHOVER] = std::bind(func, event, button, params...);
	}

	bool isHovered(const sf::Vector2i& mouse_pos);
	int triggerEvent(const eEventType event_type);

private:
	sf::Font			_font;
	sf::Text			_text;
	sf::Texture			_texture;
	sf::Sprite			_sprite;
	sf::RectangleShape	_background;
	bool				_isHovered;

	std::vector<std::function<int()>>	_events;
};