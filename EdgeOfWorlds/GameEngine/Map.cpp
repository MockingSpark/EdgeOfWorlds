#include "stdafx.h"
#include "Map.h"

/***
**** CHUNK 
***/

using TextureResource = std::map<std::string, std::unique_ptr<sf::Texture>>;

















Map::Map(std::string s)
{
	m_map.load(s);
	int i = 0;
	m_layers = new MapLayer(m_map, i);/*
	for (int i = 0; i < m_map.getLayers().size(); i++)
	{
		m_layers.push_back(MapLayer(m_map, i));
	}*/
}

void Map::draw(sf::RenderWindow & w)
{

	/*for (auto & layer : m_layers)
	{*/
		w.draw(*m_layers);
	/*}*/
}

Map::MapLayer::MapLayer(tmx::Map const & map, int & layerID)
{

	const auto& layers = map.getLayers();
	const auto tileSize = map.getTileSize();
	m_chunkSize.x = std::floor(m_chunkSize.x / tileSize.x) * tileSize.x;
	m_chunkSize.y = std::floor(m_chunkSize.y / tileSize.y) * tileSize.y;

	const auto& layer = *dynamic_cast<const tmx::TileLayer*>(layers[layerID].get());
	createChunks(map, layer);

	auto mapSize = map.getBounds();
	m_globalBounds.width = mapSize.width;
	m_globalBounds.height = mapSize.height;
}
