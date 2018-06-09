#include "stdafx.h"
#include "Map.h"


#ifdef _DEBUG

#include <iostream>
#endif // 



Map::Map(std::string s)
{
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

#ifndef _DEBUG
	m_tileset.texture.loadFromFile(texturePath);
#else
	assert(m_tileset.texture.loadFromFile(texturePath));
#endif // _DEBUG
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
		for (unsigned int x = 0; x < mapSize.x; x++)
		{
			for (unsigned int y = 0; y < mapSize.y; y++)
			{
				int id = (m_xSize -x -1) * mapSize.y + y;

				Position p = { x, y, (side == 0 ? TECH : MEDIEVAL) };
				Tile tile(p);

				tile.entity = nullptr;
				tile.sprite.setTexture(m_tileset.texture);

				auto idIndex = (side == 0 ? tileIDsTech[id].ID : tileIDsMed[id].ID) - m_tileset.tmx.getFirstGID();
				sf::Vector2i tileIndex(idIndex % m_tileset.tmx.getColumnCount(), idIndex / m_tileset.tmx.getColumnCount());
				tileIndex.x *= tileSize.x;
				tileIndex.y *= tileSize.y;

				sf::IntRect tileRect(tileIndex.x, tileIndex.y, tileSize.x,tileSize.y);
				tile.sprite.setTextureRect(tileRect);

				//tile.sprite.setOrigin(tileSize.x / 2, tileSize.y / 2);

				tile.sprite.setPosition((x + y)*m_tileset.tmx.getTileSize().x /2, 
										(y - x + m_xSize - 1)*m_tileset.tmx.getTileSize().y /4); // isometric

				m_tileList.push_back(tile);
			}
		}
	}
	
}

void Map::draw(sf::RenderTarget & t, Side s)
{
		for (int x = 0; x < m_xSize; x++)
		{
			for (int y = 0; y < m_ySize; y++)
			{
				int id = (m_ySize - y - 1) * m_xSize + x;

				int offset = ((s == MEDIEVAL) ? 1 : 0) * (m_xSize*m_ySize);

				t.draw(m_tileList[id + offset ].sprite);

				if (m_tileList[id + offset].entity != nullptr)
				{
					m_tileList[id + offset].entity->draw(t);
				}
				
			}
		}

}

void Map::addCharacter(Character* character,  Position p)
{
	m_fighters.push_back(std::tuple<Position, std::shared_ptr<Character>>{ p, std::shared_ptr<Character>(character) });
	tile(p).entity = std::shared_ptr<Character>(character);

	int id = (m_ySize - p.y - 1) * m_xSize + p.x;

	int offset = ((p.side == MEDIEVAL) ? 1 : 0) * (m_xSize*m_ySize);

	m_tileList[id + offset].entity->setPosition(m_tileList[id + offset].sprite.getPosition());
}


Map::Tile::Tile(Position & p) :
	pos(p)
{
}
