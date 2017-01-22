#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

class Tileset{
	std::string		name;

public:
					Tileset(const std::string& name_);
	virtual			~Tileset();

	std::string		GetName() const;

	bool 			operator==(const Tileset& other) const;
	bool 			operator!=(const Tileset& other) const;
};

inline Tileset::GetName() const{
	return name;
}

inline bool Tileset::operator==(const Tileset& other) const{
	return this == &other;
}

inline bool Tileset::operator!=(const Tileset& other) const {
	return this != &other;
}

/*class Tileset{

private:
	std::string			name;
	unsigned int		resourceChance;
	const bool 			simple;


	std::vector<Sprite>			floor;
	std::vector<Resource>		resource;
	std::map<uint8_t, Sprite>	extension;

public:
	Tileset(const std::string& name_, unsigned int resourceChance_, bool simple_);
	Tileset(Tileset&& other) noexcept;
	~Tileset() = default;

	bool IsSimple() const{ return simple; }

	void AddFloor(Sprite&& sprite);
	void AddResource(Resource&& res);
	void AddExtension(Sprite&& sprite, uint8_t neighbourMask);

	const Sprite& GetRandomFloor() const;
	const Resource& GetResource(int id) const;
	const Sprite& GetExtension(uint8_t neighbourMask) const;

	int GetRandomResource() const ;

	bool operator==(const Tileset& other) const { return this == &other; };
	bool operator!=(const Tileset& other) const { return this != &other; };
};*/
