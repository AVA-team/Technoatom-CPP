#ifndef _AVA_MAIN_SINGLETONE_RENDER_WINDOW_H_
#define _AVA_MAIN_SINGLETONE_RENDER_WINDOW_H_

#include"SFML\Graphics.hpp"

namespace ava {

	class MainSingletoneRenderWindow
	{
	public:
		static sf::RenderWindow* getInstance();
	private:
		MainSingletoneRenderWindow();
		~MainSingletoneRenderWindow();
		MainSingletoneRenderWindow(const MainSingletoneRenderWindow& that);
		MainSingletoneRenderWindow& operator=(MainSingletoneRenderWindow& that);
	};

}

#endif // !_AVA_MAIN_SINGLETONE_RENDER_WINDOW_H_