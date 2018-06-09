#include "stdafx.h"
#include <pugixml.hpp>
#include "GameEngine.h"
#include <time.h>
#include <windows.h>


int GameEngine::run()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window");

	Map map("..\\Assets\\maps\\exampleMap.tmx");


	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");

	Position pos{ 5, 5, TECH };

	pugi::xml_node node = doc.child("lol").child("Character");

	Character c(node);
	c.setTexture();
	
	map.addCharacter(&c, pos);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					c.move(UP);
					break;
				case sf::Keyboard::Down:
					c.move(DOWN);
					break;
				case sf::Keyboard::Left:
					c.move(LEFT);
					break;
				case sf::Keyboard::Right:
					c.move(RIGHT);
					break;
				case sf::Keyboard::Z:
					c.HitAnimation(UP);
					break;
				case sf::Keyboard::S:
					c.HitAnimation(DOWN);
					break;
				case sf::Keyboard::Q:
					c.HitAnimation(LEFT);
					break;
				case sf::Keyboard::D:
					c.HitAnimation(RIGHT);
					break;
				case sf::Keyboard::Escape:
					c.die();
					break;
				}
			}
		}

		window.clear(sf::Color::Black);
		map.draw(window, TECH);
		std:Sleep(180);
		window.display();
	}
	return EXIT_SUCCESS;
}
