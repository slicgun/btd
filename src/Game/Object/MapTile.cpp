#include "MapTile.h"

MapTile::MapTile(bool track, Direction dir, const std::string& textureName)
{
	m_data = {track, dir, textureName};
}
