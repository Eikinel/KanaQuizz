#pragma once

#include "Constants.h"
#include "Kana.h"

class	IEvent;
class	Button;

enum	eGamestate
{
	EXIT = -1,
	MENU,
	OPTIONS,
	QUIZZ,
	SIZE_GAMESTATE
};

enum	eColorChart
{
	PRIMARY_BACKGROUND,
	SECONDARY_BACKGROUND,
	TEXT_NORMAL,
	TEXT_HIGHLIGHT,
	TEXT_GREEN,
	TEXT_YELLOW,
	TEXT_RED,
	SIZE_COLOR_CHART
};

enum	eTextSize
{
	TINY,
	SMALL,
	AVERAGE,
	LARGE,
	EXTRA_LARGE,
	SIZE_TEXT_SIZE
};

enum	eScoreUI
{
	BAD_ANSWER_UI,
	GOOD_ANSWER_UI,
	SCORE_TOTAL_UI,
	SCORE_ADD_UI,
	SIZE_SCORE_UI
};


class IScreen
{
public: 
	IScreen(sf::RenderWindow& window, eGamestate state);
	virtual ~IScreen();

	//GETTERS
	virtual sf::RenderWindow&				getWindow();
	virtual std::vector<IEvent *>&			getEvents();
	virtual eGamestate						getState() const;
	virtual const sf::Font&					getUnicodeFont() const;
	virtual const sf::Font&					getFancyFont() const;
	virtual const unsigned int				getIndex() const;
	virtual const std::vector<sf::Color>&	getColorChart() const;
	virtual const std::vector<Button *>&	getButtons() const;

	//METHODS
	virtual int		run();
	virtual void	draw(const sf::Drawable& object, sf::RenderStates states = sf::RenderStates());

	//STATIC VARIABLE FOR CONSOLE DEBUG
	static const char* gamestate_name[eGamestate::SIZE_GAMESTATE];

protected:
	sf::RenderWindow&		_window;
	std::vector<IEvent *>	_events;
	eGamestate				_state;
	sf::Font				_unicode_font;
	sf::Font				_fancy_font;
	unsigned int			_index;
	std::vector<sf::Color>	_color_chart;
	std::vector<Button *>	_buttons;
	std::vector<unsigned int>	_text_sizes;
};

class				MenuScreen : public IScreen
{
public:
	MenuScreen(sf::RenderWindow& window);
	virtual ~MenuScreen();

	//GETTERS
	virtual const sf::RectangleShape&	getGreyRectTitle() const;
	virtual const sf::Sprite&			getTitleImage() const;

protected:
	sf::RectangleShape		_grey_rect_title;
	sf::Texture				_title_texture;
	sf::Sprite				_title;
};

class				QuizzScreen : public IScreen
{
public:
	QuizzScreen(sf::RenderWindow& window);
	virtual ~QuizzScreen();

	//GETTERS
	virtual const eKana						getSelectedKana() const;
	virtual const eKanaType					getSelectedKanaType() const;
	virtual const sf::Text&					getKanaText() const;
	virtual const sf::Text&					getInputText() const;
	virtual const sf::RectangleShape&		getInputBackground() const;
	virtual const sf::RectangleShape&		getInputBar() const;
	virtual const sf::Text&					getCorrectionText() const;
	virtual const std::vector<bool>&		getAnswerCounter() const;
	virtual const unsigned int				getAnswerCounterByType(const bool type) const;
	virtual const unsigned long long		getScore() const;
	virtual const std::vector<sf::Text>&	getScoreTexts() const;
	virtual const sf::Text&					getScoreTextByID(const size_t id) const;
	virtual const std::vector<std::string>&	getScoreStrings() const;
	virtual const sf::Text&					getCountdownText() const;
	virtual const sf::Text&					getHintText() const;

	//SETTERS
	void	setInputUser(const std::string& input);
	void	setRandomKana();
	void	setCorrectionText(const sf::Text& correction_text);
	void	setScore(const unsigned long long score);
	void	setScoreTexts(const std::vector<std::string>& score_texts);
	void	setScoreTextByID(const std::string& score_text, const size_t id);
	void	setCountdownText(const std::string& countdown_text);
	void	setHintText(const std::string& hint_text);

	//METHODS
	void	addCharToInput(const sf::Uint32& c_input);
	void	removeCharToInput();
	void	cleanInput();
	void	centerTextElements();
	void	addAnswer(const bool answer);
	void	addScoreToTotal(const unsigned long long score);
	void	updateUIWithAnswer(const bool answer, const unsigned long long score);

protected:
	//Quizz elements
	eKana					_random_kana;
	eKanaType				_random_kana_type;
	sf::Text				_kana_text;
	std::string				_input;
	std::vector<bool>		_answers_ct;

	//UI
	sf::Text					_input_text;
	sf::RectangleShape			_input_background;
	sf::RectangleShape			_input_bar;
	sf::Text					_correction_text;
	sf::Text					_coutdown_text;
	sf::Text					_hint_text;
	unsigned long long			_total_score;
	std::vector<sf::Text>		_score_texts;
	std::vector<std::string>	_score_strings;
};