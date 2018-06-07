#include "stdafx.h"
#include "GameEngine.h"


int GameEngine::run()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	Map map("../Assets/testMap.tmx");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		map.draw(window);
		window.display();
	}
	return EXIT_SUCCESS;
}
