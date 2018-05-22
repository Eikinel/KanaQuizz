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


class SScreen
{
public:
	//GETTERS
	static SScreen*						getInstance(sf::RenderWindow& window);
	const sf::Font&						getUnicodeFont() const;
	const sf::Font&						getFancyFont() const;
	const std::vector<sf::Color>&		getColorChart() const;
	const std::vector<unsigned int>&	getTextSizes() const;

private:
	SScreen(sf::RenderWindow& window);

	static SScreen*				instance;
	sf::Font					unicode_font;
	sf::Font					fancy_font;
	std::vector<sf::Color>		color_chart;
	std::vector<unsigned int>	text_sizes;
};

class Screen
{
public: 
	Screen(sf::RenderWindow& window, eGamestate state);
	virtual ~Screen();

	//GETTERS
	virtual sf::RenderWindow&				getWindow();
	virtual std::vector<IEvent *>&			getEvents();
	virtual eGamestate						getState() const;
	virtual const unsigned int				getIndex() const;
	virtual const std::vector<Button *>&	getButtons() const;

	//SETTERS
	virtual void	setIndex(const unsigned int index);

	//METHODS
	virtual int		run();
	virtual void	draw(const sf::Drawable& object, sf::RenderStates states = sf::RenderStates());

	//STATIC VARIABLE FOR CONSOLE DEBUG
	static const std::vector<Screen *>& getScreensByGamestate(const eGamestate gamestate);
	static const char* gamestate_name[eGamestate::SIZE_GAMESTATE];

protected:
	SScreen*				_infos;
	sf::RenderWindow&		_window;
	std::vector<IEvent *>	_events;
	eGamestate				_state;
	unsigned int			_index;
	std::vector<Button *>	_buttons;
};

class				MenuScreen : public Screen
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

class				QuizzScreen : public Screen
{
public:
	QuizzScreen(sf::RenderWindow& window);
	virtual ~QuizzScreen();

	//GETTERS
	virtual const KanaTable&				getSelectedKanaTable() const;
	virtual const eKana						getSelectedKanaID() const;
	virtual const eKanaType					getSelectedKanaType() const;
	virtual const sf::Sprite&				getSelectedKanaSprite() const;
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
	void	addScoreToTotal(const int score);
	void	updateUIWithAnswer(const bool answer, const int score);

protected:
	//Quizz elements
	std::vector<KanaTable*>	_kanas;
	KanaTable*				_selected_kana_table;
	eKana					_selected_kana_id;
	eKanaType				_selected_kana_type;
	sf::Sprite				_selected_kana_sprite;
	std::string				_input;
	std::vector<bool>		_answers_ct;

	//UI
	sf::Text					_input_text;
	sf::RectangleShape			_input_background;
	sf::RectangleShape			_input_bar;
	sf::Text					_correction_text;
	sf::Text					_coutdown_text;
	sf::Text					_hint_text;
	long long					_total_score;
	std::vector<sf::Text>		_score_texts;
	std::vector<std::string>	_score_strings;
};