#pragma once

#include "Character.h"

class IdCard
{
public:
	IdCard();

	void update();
	void draw(sf::RenderTarget&);
	void initialise(Character*);
	void setPosition(sf::Vector2f v) ;
	void setRight();
	void setLeft();

protected :
	Character * m_character;  //< Ptr d'observation uniquement

	// Corps :
	std::map<std::string, sf::Text> m_texts;
	std::map<Element, sf::CircleShape> m_weaknesses;
	sf::RenderTexture m_card;
	sf::RectangleShape m_background;
	sf::Texture m_miniatureTexture;
	sf::Texture m_miniatureTextureDead;
	sf::Sprite m_miniature;
	sf::Font m_font;

	bool m_left = false;

	sf::Vector2f m_position;
};

