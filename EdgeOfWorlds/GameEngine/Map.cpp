#include "stdafx.h"
#include "Map.h"


#ifdef _DEBUG

#include <iostream>
#endif // 



Map::Map(std::string s) :
	m_cursor(Position{0,0, TECH})
{
	m_tileToPlay = nullptr;

	tmx::Map m_map;
	
	
#ifdef  _DEBUG
	assert(m_map.load(s));
	if (m_map.getOrientation() != tmx::Orientation::Isometric)
	{
		std::cout << "Mauvaise orientation de la Map" << std::endl;
	}
	else if (m_map.getLayers().size() != 2)
	{
		std::cout << "Not Enough sides" << std::endl;
	}
	else if (m_map.getLayers()[0]->getType() != tmx::Layer::Type::Tile ||
		m_map.getLayers()[1]->getType() != tmx::Layer::Type::Tile)
	{
		std::cout << "Map mal construite" << std::endl;
	}
#else
	m_map.load(s);
#endif //  _DEBUG


	m_tileset.tmx = m_map.getTilesets()[0]; // TODO gestion de plusieurs tilesets


	std::uint32_t maxID = std::numeric_limits<std::uint32_t>::max();

	sf::Image fallback;
	fallback.create(2, 2, sf::Color::Magenta);


           

	std::string texturePath = m_tileset.tmx.getImagePath();
/*
#ifndef _DEBUG
	m_tileset.texture.loadFromFile(texturePath);
#else
	assert(m_tileset.texture.loadFromFile(texturePath));
#endif // _DEBUG*/
	std::unique_ptr<sf::Texture> newTexture = std::unique_ptr<sf::Texture>(new sf::Texture());
	sf::Image img;

	if (!img.loadFromFile(texturePath))
	{
		m_tileset.texture.loadFromImage(fallback);
	}
	else
	{
		if (m_tileset.tmx.hasTransparency())
		{
			auto transparency = m_tileset.tmx.getTransparencyColour();
			img.createMaskFromColor({ transparency.r, transparency.g, transparency.b, transparency.a });
		}
		m_tileset.texture.loadFromImage(img);
	}

	tmx::TileLayer m_tileLayerTech = *dynamic_cast<tmx::TileLayer*>(m_map.getLayers()[0].get());
	tmx::TileLayer m_tileLayerMed = *dynamic_cast<tmx::TileLayer*>(m_map.getLayers()[1].get());

	const std::vector<tmx::TileLayer::Tile>& tileIDsTech = m_tileLayerTech.getTiles();
	const std::vector<tmx::TileLayer::Tile>& tileIDsMed = m_tileLayerMed.getTiles();


	tmx::Vector2u mapSize = m_map.getTileCount();
	m_xSize = mapSize.x;
	m_ySize = mapSize.y;

	auto tileSize = m_tileset.tmx.getTileSize();

	for (int side = 0; side < 2; side++)
	{
		for ( int y = 0; y < mapSize.y; y++) // mismatch but ...
		{
			for ( int x = 0; x < mapSize.x; x++) // mismatch but ...
			{
				Position p = { x, y, (side == 0 ? TECH : MEDIEVAL) };
				Tile tmpTile(p);
				int id = tileID(p);


				tmpTile.entity = nullptr;
				tmpTile.sprite.setTexture(m_tileset.texture);

				auto idIndex = (side == 0 ? tileIDsTech[id].ID : tileIDsMed[id - m_xSize*m_ySize].ID) - m_tileset.tmx.getFirstGID();
				sf::Vector2i tileIndex(idIndex % m_tileset.tmx.getColumnCount(), idIndex / m_tileset.tmx.getColumnCount());
				tileIndex.x *= tileSize.x;
				tileIndex.y *= tileSize.y;

				sf::IntRect tileRect(tileIndex.x, tileIndex.y, tileSize.x,tileSize.y);
				tmpTile.sprite.setTextureRect(tileRect);

				//tile.sprite.setOrigin(tileSize.x / 2, tileSize.y / 2);

				tmpTile.sprite.setPosition((x + y)*m_tileset.tmx.getTileSize().x /2.f,
										(y - x + m_xSize - 1)*m_tileset.tmx.getTileSize().y /4.f); // isometric

				m_tileList.push_back(tmpTile);
				m_tileList.back().entity = nullptr;
			}
		}
	}


	sf::Image imgCur;

	if (!imgCur.loadFromFile("../Assets/sprites/cursor.png"))
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		textCur.loadFromImage(imgCur);
		m_cursor.sprite.setTexture(textCur);
	}
	m_cursor.pos = { 0, 0, TECH };
	m_cursor.sprite.setPosition(tile({ 0, 0, TECH }).sprite.getPosition());
	
}

void Map::draw(sf::RenderTarget & t)
{
		for (int x = m_xSize -1; x >=0; x--)
		{
			for (int y = 0; y < m_ySize; y++)
			{
				int id = tileID(Position{ x, y, m_viewSide });
				int idOtherSide = (id + m_xSize * m_ySize) % (m_xSize * m_ySize * 2);

				t.draw(m_tileList[id].sprite);

				if (m_cursor.pos.x == x && m_cursor.pos.y == y)
				{
					m_cursor.sprite.setPosition(m_tileList[id].sprite.getPosition());
					t.draw(m_cursor.sprite);
				}
				if (m_tileList[id].entity)
				{
					m_tileList[id].entity->draw(t);
				}
				if (m_tileList[idOtherSide].entity)
				{
					m_tileList[idOtherSide].entity->drawGohst(t);
				}
			}
		}

}

void Map::addCharacter(Character * character,  Position p)
{
	m_fighters.push_back(std::tuple<Position, Character*>{ p, character });
	Map::Tile * tilebla = &tile(p);
	tilebla->entity = character;

	tilebla->entity->setPosition(tilebla->sprite.getPosition());

	m_tileToPlay = tilebla;
}

int Map::dist(Position p, Position q)
{
	return abs(p.x - q.x) + abs(p.y - q.y);
}

bool Map::makeMove()
{
	if (m_cursor.pos.side != m_tileToPlay->pos.side) {
#ifdef _DEBUG
		std::cout << "tu ne peux pas passer de l'autre côté" << std::endl;
#endif // DEBUG
		return false;
	}
	if (dist(m_cursor.pos, m_tileToPlay->pos) == 0){
#ifdef _DEBUG
		std::cout << "ce n'est pas un déplacement ça ..." << std::endl;
#endif // DEBUG
		return false;
	}
	if (dist(m_cursor.pos, m_tileToPlay->pos) > m_tileToPlay->entity->getStats().speed) {
#ifdef _DEBUG
		std::cout << "c'est trop loin pour toi, petit pas !" << std::endl;
#endif // DEBUG
		return false;
	}


	Position p = m_cursor.pos;

	int id = tileID(p);

	if (m_tileList[id].entity) {
#ifdef _DEBUG
		std::cout << "quelqu'un a déja pris la place" << std::endl;
#endif // DEBUG
		return false;
	}

	m_tileToPlay->entity->setPosition(m_tileList[id].sprite.getPosition());

	m_tileList[id].entity = m_tileToPlay->entity;
	m_tileToPlay->entity = nullptr;

	m_tileToPlay = &m_tileList[id];

	return true;
}


bool Map::hitable(Position& target, Position& origin, EdgeSide side)
{
	switch (side)
	{
	case S_BOTH:
		return true;
	case S_EITHER:
		return true;
	case S_MEDIEVAL:
		return target.side == MEDIEVAL;
	case S_TECH:
		return target.side == TECH;
	case S_OTHER:
		return target.side != origin.side;
	case S_SAME:
		return target.side == origin.side;
	default:
		return false;
	}
};

bool Map::inRange(Position& p1, Position& p2, int rg, SkillRange rangeType)
{
	switch (rangeType)
	{
	case R_ALL:
		return true;
	case R_OTHERS:
		return p1.x != p2.x && p1.y != p2.y && p1.side != p2.side;
	case R_TEAM:
		return true;
	case R_AREA:
		return dist(p1, p2) <= rg;
	default:
		return false;
	}
}

bool Map::isTargetTeam(Character* target, Character* active, TargetTeam targetTeam)
{
	switch (targetTeam)
	{
	case T_ALLY:
		return target->getTeam() == active->getTeam();
	case T_ENEMY:
		return target->getTeam() != active->getTeam();
	case T_BOTH:
		return target != active;
	case T_SELF:
		return target == active;
	default:
		return false;
	}
}

bool Map::makeHit(int skill)
{
	int id = tileID(m_cursor.pos);

	SkillRange rangeType = m_tileToPlay->entity->getSkill(skill)->getTargeted();

	TargetTeam targetTeam = m_tileToPlay->entity->getSkill(skill)->getTargetTeam();

	EdgeSide targetSide = m_tileToPlay->entity->getSkill(skill)->getTargetSide();

	int rg = m_tileToPlay->entity->getSkill(skill)->getRange();

	int radius = m_tileToPlay->entity->getSkill(skill)->getRadius();

	bool someoneHit = false;

	for (auto & ti : m_tileList)
	{
		if (ti.entity &&
			inRange(ti.pos, m_tileToPlay->pos, rg, rangeType) &&
			isTargetTeam(ti.entity, m_tileToPlay->entity, targetTeam) &&
			hitable(ti.pos, m_tileToPlay->pos, targetSide) &&
			dist(ti.pos, m_tileList[id].pos) <= radius )
		{
			someoneHit = true; 
			m_tileToPlay->entity->hit(skill, ti.entity);

			int x = ti.pos.x - m_tileToPlay->pos.x;
			int y = ti.pos.y - m_tileToPlay->pos.y;
			Direction direction;
			if (x >= 0 && y >= 0 )
				direction = NORTH;
			if (x >= 0 && y < 0)
				direction = EAST;
			if (x < 0 && y < 0)
				direction = WEST;
			if (x < 0 && y >= 0)
				direction = SOUTH;
			m_tileToPlay->entity->HitAnimation(direction);
		}
	}

	return someoneHit;
}

void Map::moveCursor(Direction d)
{
	switch (d)
	{
	case NORTH:
		m_cursor.pos.x += 1;
		break;
	case SOUTH:
		m_cursor.pos.x -= 1;
		break;
	case WEST:
		m_cursor.pos.y -= 1;
		break;
	case EAST:
		m_cursor.pos.y += 1;
		break;
	}
	m_cursor.pos.x = ( m_cursor.pos.x + m_xSize) % m_xSize;
	m_cursor.pos.y = ( m_cursor.pos.y + m_ySize) % m_ySize;
}

bool Map::makeChangeSide()
{
	Position p = m_tileToPlay->pos;
	Position nextp = { p.x, p.y, (p.side == TECH ? MEDIEVAL : TECH) };

	int id = tileID(p);
	int nextid = tileID(nextp);

	if (m_tileList[nextid].entity)
	{
#ifdef _DEBUG
		std::cout << "Il y a déjà quelqu'un ici sur l'autre plan (on s'y perd avec ces indications de lieu)" << std::endl;
#endif // _DEBUG
		return false;
	}

	m_tileToPlay->entity->setPosition(m_tileList[nextid].sprite.getPosition());

	m_tileList[nextid].entity = m_tileToPlay->entity;
	m_tileToPlay->entity = nullptr;

	m_tileToPlay = &m_tileList[nextid];

	return true;
}

void Map::changeViewSide()
{

	m_viewSide = (m_viewSide == TECH ? MEDIEVAL : TECH); 
	m_cursor.pos.side = m_viewSide;
}

void Map::nextPlayer(Character const *c)
{
	for (auto & t : m_tileList)
	{
		if (&*t.entity == c)	// si ça référence le même character
		{
			m_tileToPlay = &t;
			m_cursor.pos = { t.pos.x, t.pos.y, t.pos.side };
			break;
		}
	}
}

void Map::makeChangeDirection(Direction d)
{
	m_tileToPlay->entity->changeDirection(d);
}

void Map::resetMap()
{
	for (auto & tile : m_tileList)
	{
		tile.entity = nullptr;;
	}
}

Map::Tile::Tile(Position p) :
	pos(p)
{
}
