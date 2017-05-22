#include <SFML/Graphics.hpp>
#include"MainSingletoneRenderWindow.h"
#include"GameEgine.h"

int main()
{
	sf::RenderWindow* window = ava::MainSingletoneRenderWindow::getInstance();
	sf::Texture background_texture;
	background_texture.loadFromFile("Images//miphi.jpg");
	sf::Sprite background_sprite(background_texture);
	ava::GameEngine engine(window->getSize());
	sf::Clock clock;
	sf::Keyboard::Key left_key = sf::Keyboard::Left;
	sf::Keyboard::Key right_key = sf::Keyboard::Right;
	while (window->isOpen() && !engine.is_game_over())
	{
		float dt = clock.restart().asSeconds();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			engine.fire();
		}
		if (sf::Keyboard::isKeyPressed(left_key)) {
			engine.do_iteration(left_key, dt);
		}
		else if (sf::Keyboard::isKeyPressed(right_key)) {
			engine.do_iteration(right_key, dt);
		}
		else {
			engine.do_iteration(sf::Keyboard::Unknown, dt);
		}
		window->clear();
		window->draw(background_sprite);
		engine.draw_scene(window);
		window->display();
	}

	return 0;
}