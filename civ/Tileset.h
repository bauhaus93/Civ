#pragma once

#include <vector>
#include <string>
#include <memory>


#include "Sprite.h"

class Tileset{
	
	std::string			name;
	std::vector<std::unique_ptr<Sprite>> floor;
	std::vector<std::unique_ptr<Sprite>> onFloor;
	std::vector<std::unique_ptr<Sprite>> resource;

public:
	Tileset(const std::string& name_);

	void				AddFloor(std::unique_ptr<Sprite> sprite);
	void				AddOnFloor(std::unique_ptr<Sprite> sprite);
	void				AddResource(std::unique_ptr<Sprite> sprite);

	Sprite&				GetRandomFloor();

	const std::string&	GetName() const { return name; };
};

inline void Tileset::AddFloor(std::unique_ptr<Sprite> sprite){
	floor.push_back(std::move(sprite));
}


inline void Tileset::AddOnFloor(std::unique_ptr<Sprite> sprite){
	onFloor.push_back(std::move(sprite));
}

inline void Tileset::AddResource(std::unique_ptr<Sprite> sprite){
	resource.push_back(std::move(sprite));
}

inline Sprite& Tileset::GetRandomFloor(){
	return *floor.at(0);
}

