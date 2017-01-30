#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "TilesetType.h"

class Tileset{
	std::string			name;

public:
	explicit			Tileset(const std::string& name_);
	virtual				~Tileset() = default;

	std::string			GetName() const;

	bool 				operator==(const Tileset& other) const;
	bool 				operator!=(const Tileset& other) const;
	virtual	TilesetType GetType() const = 0;
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
