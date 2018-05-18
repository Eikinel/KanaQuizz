#pragma once

# include <SFML\Graphics.hpp>
# include <vector>
# include <iostream>

// Directories
# define ASSETS_DIR		"../KanaQuizz/Assets"
# define SPRITES_DIR	ASSETS_DIR"/Sprites"
# define FONTS_DIR		ASSETS_DIR"/Fonts"

// Global variable for screens, containing menu, game, etc.
class IScreen;
extern std::vector<IScreen *> all_screens;

// Misc
# define MAX_ROMAJI	2
# define RIGHT_ANSWER	"Correct !"
# define WRONG_ANSWER	"Wrong"
# define RIGHT_COUNTER	"Right answer(s) given : "
# define WRONG_COUNTER	"Wrong answer(s) given : "
# define COUNTDOWN_SEC	0
# define COUNTDOWN_GO	"GO !!!"