#include "stdafx.h"
#include <pugixml.hpp>
#include "GameEngine.h"
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

	Position pos2{ 3, 9, TECH };

	pugi::xml_node node2 = doc.child("lol").child("Character2");

	Character c2(node2);
	c2.setTeam(Character::BLUE);
	c2.setTexture();

	map.addCharacter(&c2, pos2);

	bool isC2 = true;

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
					map.moveCursor(UP);
					break;
				case sf::Keyboard::Down:
					map.moveCursor(DOWN);
					break;
				case sf::Keyboard::Left:
					map.moveCursor(LEFT);
					break;
				case sf::Keyboard::Right:
					map.moveCursor(RIGHT);
					break;
				case sf::Keyboard::Space:
					if (! map.makeHit())
						map.makeMove();
					break;
				case sf::Keyboard::Return:
					map.changeViewSide();
					break;
				case sf::Keyboard::RShift:
					map.makeChangeSide();
					break;
				case sf::Keyboard::Escape:
					if (isC2) { map.nextPlayer(&c); isC2 = false; }
					else { map.nextPlayer(&c2); isC2 = true; }
				default:
					break;
				}
			}
		}

		window.clear(sf::Color::Black);
		map.draw(window);
		Sleep(180);
		window.display();
	}
	return EXIT_SUCCESS;
}
