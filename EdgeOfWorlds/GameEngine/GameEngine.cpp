#include "stdafx.h"
#include "GameEngine.h"


int GameEngine::run()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window");

	Map map("..\\Assets\\maps\\exampleMap.tmx");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		map.draw(window, MEDIEVAL);
		window.display();
	}
	return EXIT_SUCCESS;
}
