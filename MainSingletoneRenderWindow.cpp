#include "MainSingletoneRenderWindow.h"

namespace ava {

	MainSingletoneRenderWindow::MainSingletoneRenderWindow()
	{
	}


	MainSingletoneRenderWindow::~MainSingletoneRenderWindow()
	{
	}

	sf::RenderWindow* MainSingletoneRenderWindow::getInstance() {
		static sf::RenderWindow instance(sf::VideoMode(800, 600), "AVA_GAME");
		return &instance;
	}

}
