#include <iostream>
#include <map>
#include "Screen.h"

std::vector<IScreen *>	all_screens;

int main(int argc, char** argv)
{
	sf::RenderWindow	window(sf::VideoMode(
		(unsigned int)(sf::VideoMode::getDesktopMode().width / 1.25f),
		(unsigned int)(sf::VideoMode::getDesktopMode().height / 1.25f)),
		"KanaQuizz - Challenge your Japanese !",
		sf::Style::Close);

	// Pushing screens to the stack
	all_screens.push_back(new QuizzScreen(window));

	// Run every elements in the stack. If there's no more screen left or a close request is done, break the loop.
	int status = MENU;
	while ((status = all_screens[status]->run()) != EXIT && (size_t)status < all_screens.size());

	// On exit request, delete all screens properly
	for (auto it : all_screens)
	{
		std::cout << "Delete screen n°" << it->getIndex() << " : " << std::endl;
		delete(it);
	}
	return (status);
}