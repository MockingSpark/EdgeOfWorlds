#include "stdafx.h"
#include "IdCard.h"
#include <assert.h>
/*
IdCard::IdCard(Character *c) :
	m_character(c)
{
	initialise();
	update();
}

void IdCard::initialise()
{
	switch (m_character->getTeam())
	{
	case Character::RED:
			m_fillColor = sf::Color::Red;
#ifndef _DEBUG
		m_miniatureTexture.loadFromFile("../Assets/sprites/redFace.png");
		m_miniatureTextureDead.loadFromFile("../Assets/sprites/redFaceDead.png");
#else
		assert(m_miniatureTexture.loadFromFile("../Assets/sprites/redFace.png"));
		assert(m_miniatureTextureDead.loadFromFile("../Assets/sprites/redFaceDead.png"));
#endif // _DEBUG
		
		break;
	case Character::BLUE:
		m_fillColor = sf::Color::Red;
#ifndef _DEBUG
		m_miniatureTexture.loadFromFile("../Assets/sprites/blueFace.png");
		m_miniatureTextureDead.loadFromFile("../Assets/sprites/blueFaceDead.png");
#else
		assert(m_miniatureTexture.loadFromFile("../Assets/sprites/blueFace.png"));
		assert(m_miniatureTextureDead.loadFromFile("../Assets/sprites/blueFaceDead.png"));
#endif // _DEBUG
		break;
	}

	m_background.setFillColor(m_fillColor);
	m_background.setSize(sf::Vector2f(200., 500.));

	m_miniature.setTexture(m_miniatureTexture);
	m_miniature.setPosition(50., 50.);

	sf::Text name;
	name.setColor(sf::Color::Black);
	name.setFont(sf::Font());
	m_texts.emplace("Name", );


}
*/