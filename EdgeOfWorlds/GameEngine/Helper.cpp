#include "stdafx.h"
#include "Helper.h"

void Helper::update(bool move, bool change, bool attack)
{
	if (move)
	{
		m_moveText.setFillColor(sf::Color(100, 100, 100));
	}
	else
	{
		m_moveText.setFillColor(sf::Color::Black);
	}
	if (change)
	{
		m_changeSideText.setFillColor(sf::Color(100, 100, 100));
	}
	else
	{
		m_changeSideText.setFillColor(sf::Color::Black);
	}
	if (attack)
	{
		for (auto & text : m_skillsTexts)
			text.setFillColor(sf::Color(100, 100, 100));
	}
	else
	{
		for (auto & text : m_skillsTexts)
			text.setFillColor(sf::Color::Black);
	}
}

void Helper::draw(sf::RenderTarget &t)
{
	m_texture.draw(m_background);
	m_texture.draw(m_changeSideText);
	m_texture.draw(m_cursorText);
	m_texture.draw(m_moveText);
	m_texture.draw(m_skipText);

	for (auto & text : m_skillsTexts) {
		m_texture.draw(text);
	}
	m_texture.display();
	sf::Sprite sprite(m_texture.getTexture());
	sprite.setPosition(m_position);
	t.draw(sprite);
}

void Helper::initialise(Character *c)
{
	m_character = c;

	sf::Color color(100, 100, 100);

	m_font.loadFromFile("../Assets/alagard.ttf");
	m_texture.create(1400, 200);

	m_background.setFillColor(sf::Color(215,200,150));
	m_background.setSize(sf::Vector2f(1400., 200.));
	m_background.setPosition(sf::Vector2f(0., 0.));

	m_moveText.setFillColor(color);
	m_moveText.setCharacterSize(30);
	m_moveText.setFont(m_font);
	m_moveText.setPosition(20.,20.);
	m_moveText.setString("space : Move");

	m_changeSideText.setFillColor(color);
	m_changeSideText.setCharacterSize(30);
	m_changeSideText.setFont(m_font);
	m_changeSideText.setPosition(20., 65.);
	m_changeSideText.setString("E : Change side");

	m_cursorText.setFillColor(color);
	m_cursorText.setCharacterSize(30);
	m_cursorText.setFont(m_font);
	m_cursorText.setPosition(20., 110.);
	m_cursorText.setString("Z, Q, S, D : Move cursor");

	m_skipText.setFillColor(color);
	m_skipText.setCharacterSize(30);
	m_skipText.setFont(m_font);
	m_skipText.setPosition(20., 154.);
	m_skipText.setString("A : Skip turn");

	sf::Text m_moveText;

	for (int i = 0; i < 6; i++)
	{

		m_skillsTexts[i].setFillColor(color);
		m_skillsTexts[i].setCharacterSize(30);
		m_skillsTexts[i].setFont(m_font);
		m_skillsTexts[i].setPosition(450 * (1 + i/3) + 20, 60 * (i % 3) + 20);
		std::string Str;
		if (m_character->getSkill(i) == nullptr)
		{
			Str = std::to_string(i) + " : ";
		}
		else {
			Str = std::to_string(i) + " : " + m_character->getSkill(i)->getName() ;
		}
		m_skillsTexts[i].setString(Str);

	}

	sf::RenderTexture m_texture;
}
