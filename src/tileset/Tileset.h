#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

enum class TilesetType{
	BASIC 		= (1 << 0),
	EXTENDED 	= (1 << 1),
	OCEAN 		= (1 << 2)
};

class Tileset{
	std::string			name;

public:
						Tileset(const std::string& name_);
	virtual				~Tileset() = default;

	std::string			GetName() const;

	bool 				operator==(const Tileset& other) const;
	bool 				operator!=(const Tileset& other) const;
	virtual	int 		GetType() const = 0;
};

inline std::string Tileset::GetName() const{
	return name;
}

inline bool Tileset::operator==(const Tileset& other) const{
	return this == &other;
}

inline bool Tileset::operator!=(const Tileset& other) const {
	return this != &other;
}
