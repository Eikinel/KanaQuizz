#include <iostream>
#include <map>
#include "Screen.h"

std::vector<Screen *>	all_screens;
Screen* delete_queue = NULL;
SScreen* SScreen::instance = NULL;

int main(int argc, char** argv)
{
	sf::RenderWindow	window(sf::VideoMode(
		(unsigned int)(sf::VideoMode::getDesktopMode().width * ASPECT_RATIO),
		(unsigned int)(sf::VideoMode::getDesktopMode().height * ASPECT_RATIO)),
		"KanaQuizz - Challenge your Japanese !",
		sf::Style::Close);

	// Create screen infos and push menu screen to the stack
	all_screens.push_back(new MenuScreen(window));

	// Run every elements in the stack. If there's no more screen left or a close request is done, break the loop.
	int status = 0;
	while ((status = all_screens[status]->run()) != EXIT);

	// On exit request, delete all screens properly
	for (auto it : all_screens)
	{
		std::cout << "Delete screen n°" << it->getIndex() << " : " << std::endl;
		delete(it);
	}
	return (status);
}