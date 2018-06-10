#include "stdafx.h"
#include "IdCard.h"
#include <assert.h>

void IdCard::update()
{
	std::string nameStr("HP : ");
	nameStr = nameStr + std::to_string(m_character->getHP());
	m_texts["HP"].setString(nameStr);

	std::string attackStr("Attk : ");
	attackStr += std::to_string(m_character->getStats().strength);
	m_texts["Attack"].setString(attackStr);

	std::string DefenseStr("Def  : ");
	DefenseStr += std::to_string(m_character->getStats().defense);
	m_texts["Defense"].setString(DefenseStr);

	std::string PowerStr("Pow  : ");
	PowerStr += std::to_string(m_character->getStats().power);
	m_texts["Power"].setString(PowerStr);

	std::string ResistStr("Res  : ");
	ResistStr += std::to_string(m_character->getStats().resist);
	m_texts["Resist"].setString(ResistStr);

	std::string SpeedStr("Mvt  : ");
	SpeedStr += std::to_string(m_character->getStats().speed);
	m_texts["Speed"].setString(SpeedStr);




}

void IdCard::draw(sf::RenderTarget & t)
{

	if (m_character->isDead()) {
		m_background.setFillColor(sf::Color(100, 100, 100));
		m_miniature.setTexture(m_miniatureTextureDead);
	}

	m_card.draw(m_background);
	m_card.draw(m_miniature);

	for (auto & text : m_texts) {
		m_card.draw(text.second);
	}

	for (auto & circle : m_weaknesses) {
		m_card.draw(circle.second);
	}

	m_card.display();
	sf::Sprite sprite(m_card.getTexture());
	sprite.setPosition(m_position);
	t.draw(sprite);

}

void IdCard::initialise(Character* c)
{
	m_card.create(307, 120);

	m_character = c;

	sf::Color m_fillColor;
	switch (m_character->getTeam())
	{
	case Character::RED:
			m_fillColor = sf::Color(128,0,0);
#ifndef _DEBUG
		m_miniatureTexture.loadFromFile("../Assets/sprites/redFace.png");
		m_miniatureTextureDead.loadFromFile("../Assets/sprites/redFaceDead.png");
#else
		assert(m_miniatureTexture.loadFromFile("../Assets/sprites/redFace.png"));
		assert(m_miniatureTextureDead.loadFromFile("../Assets/sprites/redFaceDead.png"));
#endif // _DEBUG
		
		break;
	case Character::BLUE:
		m_fillColor = sf::Color(0,0,128);
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
	m_background.setSize(sf::Vector2f(300., 120.));
	m_background.setPosition(sf::Vector2f(0., 0.));

	m_miniature.setTexture(m_miniatureTexture);
	m_miniature.setPosition(10., 10.);

	m_font.loadFromFile("../Assets/alagard.ttf");
	int charSize = 20;

	sf::Text name;
	name.setFillColor(sf::Color::Black);
	name.setCharacterSize(charSize);
	name.setFont(m_font);
	std::string nameStr(m_character->getName());
	name.setString(nameStr);
	name.setPosition(120., 10.);
	m_texts.emplace("Name", name);

	sf::Text hp;
	hp.setFillColor(sf::Color::Black);
	hp.setCharacterSize(charSize);
	hp.setFont(m_font);
	std::string hpStr("HP : ");
	hp.setString(hpStr);
	hp.setPosition(120., 36.);
	m_texts.emplace("HP", hp);

	sf::Text Attack;
	Attack.setFillColor(sf::Color::Black);
	Attack.setCharacterSize(charSize);
	Attack.setFont(m_font);
	std::string attackStr("Attk : ");
	Attack.setString(attackStr);
	Attack.setPosition(200., 36.);
	m_texts.emplace("Attack", Attack);

	sf::Text Defense;
	Defense.setFillColor(sf::Color::Black);
	Defense.setCharacterSize(charSize);
	Defense.setFont(m_font);
	std::string DefenseStr("Def  : ");
	Defense.setString(DefenseStr);
	Defense.setPosition(120., 62.);
	m_texts.emplace("Defense", Defense);

	sf::Text Power;
	Power.setFillColor(sf::Color::Black);
	Power.setCharacterSize(charSize);
	Power.setFont(m_font);
	std::string PowerStr("Pow  : ");
	Power.setString(PowerStr);
	Power.setPosition(200., 62.);
	m_texts.emplace("Power", Power);

	sf::Text Resist;
	Resist.setFillColor(sf::Color::Black);
	Resist.setCharacterSize(charSize);
	Resist.setFont(m_font);
	std::string ResistStr("Res  : ");
	Resist.setString(ResistStr);
	Resist.setPosition(120., 88.);
	m_texts.emplace("Resist", Resist);

	sf::Text Speed;
	Speed.setFillColor(sf::Color::Black);
	Speed.setCharacterSize(charSize);
	Speed.setFont(m_font);
	std::string SpeedStr("Mvt  : ");
	Speed.setString(SpeedStr);
	Speed.setPosition(200., 88.);
	m_texts.emplace("Speed", Speed);


	{
		sf::CircleShape circle;
		sf::Color color(255, 0, 0);
		circle.setPosition(295., 7.);
		circle.setRadius(5);
		switch (m_character->getWeakness(E_FIRE))
		{
			case W_ABSORB:
				circle.setFillColor(sf::Color::White);
				circle.setOutlineColor(color);
				circle.setOutlineThickness(1);
				break;
			case W_IMMUNE:
				circle.setFillColor(color);
				circle.setOutlineColor(color);
				circle.setOutlineThickness(1);
				break;
			case W_RESISTANT:
				circle.setFillColor(color);
				circle.setOutlineColor(sf::Color::Black);
				circle.setOutlineThickness(1);
				break;
			case W_WEAK:
				circle.setFillColor(sf::Color::Black);
				circle.setOutlineColor(color);
				circle.setOutlineThickness(1);
				break;
			default:
				circle.setFillColor(sf::Color::Black);
				circle.setOutlineColor(sf::Color::Black);
				circle.setOutlineThickness(1);
				break;
		}
		m_weaknesses.emplace(E_FIRE, circle);
	}
	// fire

	{
		sf::CircleShape circle;
		sf::Color color(0, 0, 255);
		circle.setPosition(295., 22.);
		circle.setRadius(5);
		switch (m_character->getWeakness(E_WATER))
		{
		case W_ABSORB:
			circle.setFillColor(sf::Color::White);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_IMMUNE:
			circle.setFillColor(color);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_RESISTANT:
			circle.setFillColor(color);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		case W_WEAK:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		default:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		}
		m_weaknesses.emplace(E_WATER, circle);
	}
	// Water

	{
		sf::CircleShape circle;
		sf::Color color(115,80, 20); //brown
		circle.setPosition(295., 37.);
		circle.setRadius(5);
		switch (m_character->getWeakness(E_EARTH))
		{
		case W_ABSORB:
			circle.setFillColor(sf::Color::White);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_IMMUNE:
			circle.setFillColor(color);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_RESISTANT:
			circle.setFillColor(color);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		case W_WEAK:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		default:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		}
		m_weaknesses.emplace(E_EARTH, circle);
	}
	// Earth

	{
		sf::CircleShape circle;
		sf::Color color(255, 255, 0);
		circle.setPosition(295., 52.);
		circle.setRadius(5);
		switch (m_character->getWeakness(E_THUNDER))
		{
		case W_ABSORB:
			circle.setFillColor(sf::Color::White);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_IMMUNE:
			circle.setFillColor(color);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_RESISTANT:
			circle.setFillColor(color);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		case W_WEAK:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		default:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		}
		m_weaknesses.emplace(E_THUNDER, circle);
	}
	// thunder

	{
		sf::CircleShape circle;
		sf::Color color(0, 255, 255);
		circle.setPosition(295., 67.);
		circle.setRadius(5);
		switch (m_character->getWeakness(E_WIND))
		{
		case W_ABSORB:
			circle.setFillColor(sf::Color::White);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_IMMUNE:
			circle.setFillColor(color);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_RESISTANT:
			circle.setFillColor(color);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		case W_WEAK:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		default:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		}
		m_weaknesses.emplace(E_WIND, circle);
	}
	// wind

	{
		sf::CircleShape circle;
		sf::Color color(200, 200, 200);
		circle.setPosition(295., 82.);
		circle.setRadius(5);
		switch (m_character->getWeakness(E_HOLY))
		{
		case W_ABSORB:
			circle.setFillColor(sf::Color::White);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_IMMUNE:
			circle.setFillColor(color);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_RESISTANT:
			circle.setFillColor(color);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		case W_WEAK:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		default:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		}
		m_weaknesses.emplace(E_HOLY, circle);
	}
	// holy

	{
		sf::CircleShape circle;
		sf::Color color(50, 50, 50);
		circle.setPosition(295., 97.);
		circle.setRadius(5);
		switch (m_character->getWeakness(E_DARK))
		{
		case W_ABSORB:
			circle.setFillColor(sf::Color::White);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_IMMUNE:
			circle.setFillColor(color);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		case W_RESISTANT:
			circle.setFillColor(color);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		case W_WEAK:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(color);
			circle.setOutlineThickness(1);
			break;
		default:
			circle.setFillColor(sf::Color::Black);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(1);
			break;
		}
		m_weaknesses.emplace(E_DARK, circle);
	}
	// dark

	update();
}

void IdCard::setPosition(sf::Vector2f v)
{
	m_position = v;
}

void IdCard::setRight()
{
	if (!m_left)
		return;

	sf::Vector2f offset(-6., 0.);

	m_background.move(offset);
	m_miniature.move(offset);
	for (auto & txt : m_texts)
		txt.second.move(offset);

	m_weaknesses[E_FIRE].setPosition(295., 7.);
	m_weaknesses[E_WATER].setPosition(295., 22.);
	m_weaknesses[E_EARTH].setPosition(295., 37.);
	m_weaknesses[E_THUNDER].setPosition(295., 52.);
	m_weaknesses[E_WIND].setPosition(295., 67.);
	m_weaknesses[E_HOLY].setPosition(295., 82.);
	m_weaknesses[E_DARK].setPosition(295., 97.);
}

void IdCard::setLeft()
{
	if (m_left)
		return;

	sf::Vector2f offset(6., 0.);

	m_background.move(offset);
	m_miniature.move(offset);
	for (auto & txt : m_texts)
		txt.second.move(offset);

	m_weaknesses[E_FIRE].setPosition(1., 7.);
	m_weaknesses[E_WATER].setPosition(1., 22.);
	m_weaknesses[E_EARTH].setPosition(1., 37.);
	m_weaknesses[E_THUNDER].setPosition(1., 52.);
	m_weaknesses[E_WIND].setPosition(1., 67.);
	m_weaknesses[E_HOLY].setPosition(1., 82.);
	m_weaknesses[E_DARK].setPosition(1., 97.);
}


