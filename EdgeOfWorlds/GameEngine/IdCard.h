#pragma once

#include "Character.h"

class IdCard
{
public:
	IdCard(Character*);

	void update();
	void draw(sf::RenderTarget&);

private:
	void initialise();

protected :
	Character const * m_character;  //< Ptr d'observation uniquement

	// Corps :
	sf::Sprite m_card;
	sf::RenderTexture m_texture;
	std::map<std::string, sf::Text> m_texts;
	sf::RectangleShape m_background;
	sf::Color m_fillColor;
	sf::Texture m_miniatureTexture;
	sf::Texture m_miniatureTextureDead;
	sf::Sprite m_miniature;
};

