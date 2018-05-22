#pragma once

# include <SFML\Graphics.hpp>
# include <vector>
# include <iostream>

// Directories
# define ASSETS_DIR		"../KanaQuizz/Assets"
# define SPRITES_DIR	ASSETS_DIR"/Sprites"
# define FONTS_DIR		ASSETS_DIR"/Fonts"
# define KANA_DIR		ASSETS_DIR"/Kana"
# define HIRAGANA_DIR	KANA_DIR"/Hiragana"
# define KATAKANA_DIR	KANA_DIR"/Katakana"

// Global variable for screens, containing menu, game, etc.
class Screen;
extern std::vector<Screen *> all_screens;
extern Screen* delete_queue;

// Misc
# define ASPECT_RATIO	0.75f
# define MAX_ROMAJI		2
# define RIGHT_ANSWER	"Correct !"
# define WRONG_ANSWER	"Wrong"
# define RIGHT_COUNTER	"Right answer(s) given : "
# define WRONG_COUNTER	"Wrong answer(s) given : "
# define TOTAL_SCORE_COUNTER	"Score : "
# define ADD_SCORE_COUNTER		"+ "
# define SUB_SCORE_COUNTER		"- "
# define SCORE_BASE		0
# define SCORE_POINT	200
# define SCORE_PENALTY	-100
# define COUNTDOWN_SEC	4
# define COUNTDOWN_GO	"GO !!!"