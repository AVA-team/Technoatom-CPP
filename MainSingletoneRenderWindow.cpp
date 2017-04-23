#include "MainSingletoneRenderWindow.h"

namespace ava {

	MainSingletoneRenderWindow::MainSingletoneRenderWindow()
	{
	}


	MainSingletoneRenderWindow::~MainSingletoneRenderWindow()
	{
	}

	sf::RenderWindow* MainSingletoneRenderWindow::getInstance() {
		static sf::RenderWindow instance(sf::VideoMode(1024, 800), "AVA_GAME");
		return &instance;
	}

}
