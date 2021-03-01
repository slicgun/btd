#pragma once

#include<string>

enum class Direction
{
	left = 0,
	right,
	up,
	down,
	None = 4
};

///a map will be 16 * 9 tiles
/// there will be some tiles the bloons can walk on to get to the end
/// and some tiles where you can place towers

class MapTile
{
	struct Data
	{
		bool track = false;
		Direction dir = Direction::None;
		std::string texture = "default_floor";
	};

public:
	MapTile(bool track, Direction dir, const std::string& textureName);

	const Data& getData() const { return m_data; }
private:
	Data m_data;
};