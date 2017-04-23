#include <SFML/Graphics.hpp>
#include"MainSingletoneRenderWindow.h"

int main()
{
	sf::RenderWindow* window = ava::MainSingletoneRenderWindow::getInstance();

	while (window->isOpen())
	{

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		window->display();
	}

	return 0;
}