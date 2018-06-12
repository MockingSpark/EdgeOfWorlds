#pragma once

#include "Character.h"

class Helper
{
public:
	void update(bool move = true, bool change = true, bool attack = true);
	void draw(sf::RenderTarget&);
	void initialise();
	void changeCharacter(Character const *);
	void setPosition(sf::Vector2f v) { m_position = v; };

protected:
	Character const * m_character; //< pointeur d'observation uniquement.

	sf::RenderTexture m_texture;
	sf::RectangleShape m_background;
	sf::Text m_skillsTexts[6];
	sf::Text m_changeSideText;
	sf::Text m_moveText;
	sf::Text m_cursorText;
	sf::Text m_skipText;
	sf::Font m_font;

	sf::Vector2f m_position;
};

