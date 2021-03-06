#include "Button.h"

//CONSTRUCTORS
Button::Button(const std::string& text, const unsigned int& size, const sf::Font& font, const sf::Color& text_color,
	const sf::Vector2f& pos, const eIndentX& indent_x, const eIndentY& indent_y, const sf::Texture& texture)
{
	std::string	format_x[eIndentX::INDENT_X_SIZE] = { "LEFT", "CENTER", "RIGHT" };
	std::string	format_y[eIndentY::INDENT_Y_SIZE] = { "TOP", "CENTER", "BOTTOM" };
	sf::FloatRect text_rect;

	std::cout << "Add button with text \"" << text << "\" and indentation " <<
		format_x[(int)indent_x] << " " << format_y[(int)indent_y] << " at position [" <<
		pos.x << " ; " << pos.y << "]." << std::endl;
	this->_font = font;
	this->_text.setString(text);
	this->_text.setFont(this->_font);
	this->_text.setCharacterSize(size);
	this->_text.setFillColor(text_color);
	text_rect = this->_text.getGlobalBounds();
	this->_text.setOrigin(sf::Vector2f(
		text_rect.left + (text_rect.width / 2.f) * (int)indent_x,
		text_rect.top + (text_rect.height / 2.f) * (int)indent_y));
	this->_text.setPosition(pos);
	this->_events = std::vector<std::vector<std::function<int()>>>(eEventType::EVENT_TYPE_SIZE);
	this->_isHovered = false;
}

Button::Button(const Button& other)
{
	this->_font = sf::Font(other._font);
	this->_text = sf::Text(other._text);
	this->_events = other._events;
}

Button::~Button()
{
	std::cout << "Deleting button with text '" << this->_text.getString().toAnsiString() << "'" << std::endl;
}


//GETTERS
const sf::Text&				Button::getText() const
{
	return (this->_text);
}

const std::vector<std::vector<std::function<int()>>>&	Button::getAllEvents() const
{
	return (this->_events);
}

const std::vector<std::function<int()>>&	Button::getEventsByType(const eEventType type) const
{
	return (this->_events[type]);
}


//SETTERS
void	Button::setText(const sf::Text& text)
{
	this->_text = text;
}

void	Button::addEventByType(const std::function<int()> event, const eEventType event_type)
{
	this->_events[event_type].push_back(event);
}


//METHODS
bool	Button::isHovered(const sf::Vector2i& mouse_pos)
{
	if (this->_text.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
		return (this->_isHovered = true);
	return (this->_isHovered = false);
}

const bool Button::getHoverState() const
{
	return (this->_isHovered);
}

int		Button::triggerEvent(const eEventType event_type, int index)
{
	if (index < this->_events[event_type].size() &&
		this->_events[event_type][index] != NULL)
		return(this->_events[event_type][index]());
	return NULL;
}