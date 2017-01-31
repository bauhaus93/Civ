#include "SpriteManager.h"

using namespace std;

const string TERRAIN1{"terrain1"};
const string TERRAIN2{"terrain2"};

const string TERRAIN1PATH{"bmp/TERRAIN1.bmp"};
const string TERRAIN2PATH{"bmp/TERRAIN2.bmp"};

SpriteManager* SpriteManager::instance = nullptr;

void SpriteManager::Start(){
	if (instance == nullptr){
		instance = new SpriteManager();
		atexit([](){Stop(); });
	}
	else
		throw CivException("SpriteManager::Start", "SpriteManager already started!");
}

void SpriteManager::Stop(){
    if(instance != nullptr)
        delete instance;
    instance = nullptr;
}

SpriteManager::SpriteManager():
    factory{}{
    factory.AddSpriteSheet(TERRAIN1, TERRAIN1PATH);
    factory.AddSpriteSheet(TERRAIN2, TERRAIN2PATH);
    factory.MakeTransparent(RGBColor{ 0x87, 0x87, 0x87 });
    factory.MakeTransparent(RGBColor{ 0xFF, 0x00, 0xFF });

	dummy = factory.CreateSprite(TERRAIN1, Rect{1, 1, 64, 32});

    Logger::Write("Created sprite manager");
}

SpriteManager::~SpriteManager(){
    Logger::Write("Destroyed sprite manager");
}

int SpriteManager::ClearUnneeded(){
	int c = 0;

	auto iter = storage.begin();
	while(iter != storage.end()){
		if(iter->second.expired()){
			iter = storage.erase(iter);
			c++;
		}
	}
	return c;
}

shared_ptr<Sprite> SpriteManager::GetElement(uint32_t hash){
	auto found = storage.find(hash);

	if(found == storage.end())
		return nullptr;

	if(shared_ptr<Sprite> sprite = found->second.lock()){
		return sprite;
	}
	else{
		storage.erase(found);
		return nullptr;
	}
}

//For sprites which should always exists, such the ones
//saved in the terrain sets
shared_ptr<Sprite> SpriteManager::GetExistingElement(uint32_t hash){
	shared_ptr<Sprite> sprite = GetElement(hash);
	assert(sprite != nullptr);
	return sprite;
}

shared_ptr<Sprite> SpriteManager::CreateFromSpritesheet(const string& sheetname, const Rect& rect){
    auto sprite = factory.CreateSprite(sheetname, rect);
    uint32_t hash = sprite->GetHash();

    auto result = storage.emplace(hash, sprite);

    //if basic spritesheet sprites collide, hash functions should definitly be changed
	//EDIT: actually not, because eg extended terrain sets all want to add same basic floor
    //assert(result.second == true);

    return result.first->second.lock();
}

shared_ptr<Sprite> SpriteManager::CreateDiamondFromSpritesheet(const std::string& sheetname, const Point& pos){
	return CreateFromSpritesheet(sheetname, Rect{pos, 64, 32});
}


/*
The sprites retrieved here are sprites, where a shared_ptr in the
corresponding terrain set should exist, so they should always
exist
*/
shared_ptr<Sprite> SpriteManager::CreateBasicTerrainComposite(const vector<uint32_t>& spriteHashes){
    assert(spriteHashes.size() >= 2);

    auto sprite = make_shared<Sprite>(*GetExistingElement(spriteHashes[0]));	//basic

    if(spriteHashes.at(1) != 0)
        sprite->Add(*GetExistingElement(spriteHashes[1]));	//resource, if existing
    //TODO Other sprite hashes would indicate neighbours, which should be
    //used to create a dithered layer on the sprite

    return sprite;

}

shared_ptr<Sprite> SpriteManager::CreateExtendedTerrainComposite(const vector<uint32_t>& spriteHashes){
    assert(spriteHashes.size() >= 3);
	assert(spriteHashes[2] != 0);	//must have an extension sprite hash

	auto sprite = make_shared<Sprite>(*GetExistingElement(spriteHashes[0]));	//basic

    sprite->Add(*GetExistingElement(spriteHashes[2]));							//extension

	if(spriteHashes.at(1) != 0)
        sprite->Add(*GetExistingElement(spriteHashes[1]));	//resource, if existing

    //TODO Other sprite hashes would indicate neighbours, which should be
    //used to create a dithered layer on the sprite

    return sprite;

}

shared_ptr<Sprite> SpriteManager::CreateOceanTerrainComposite(const vector<uint32_t>& spriteHashes){
    assert(spriteHashes.size() >= 6);
    const static Point coastEdges[] = { Point{ 16, 0 },
                                        Point{ 16, 16},
                                        Point{ 0, 8},
                                        Point{ 32, 8}};

	auto sprite = make_shared<Sprite>(*GetExistingElement(spriteHashes[0]));	//basic

    for(int i = 0; i < 4; i++){
        if(spriteHashes[2 + i] != 0)
            sprite->Add(*GetExistingElement(spriteHashes[2 + i]), Point{0, 0}, coastEdges[i]);    //coastline, if existing
    }

	if(spriteHashes.at(1) != 0)
        sprite->Add(*GetExistingElement(spriteHashes[1]));	//resource, if existing
    return sprite;

}

shared_ptr<Sprite> SpriteManager::GetTerrainComposite(const std::vector<uint32_t>& spriteHashes, TilesetType type){
    uint32_t compositeHash = Hash(spriteHashes);

	shared_ptr<Sprite> sprite = GetElement(compositeHash);
	if(sprite != nullptr)
		return sprite;

	cout << "storage size: " << storage.size() << endl;

    //We use the composite hash for lookup, because it is easier to calculate
    //(we don't have to create the sprite first, to see if the created sprite hash is already existing)
    switch(type){
        case TilesetType::BASIC:
            sprite = CreateBasicTerrainComposite(spriteHashes);
            break;
        case TilesetType::EXTENDED:
            sprite = CreateExtendedTerrainComposite(spriteHashes);
            break;
        case TilesetType::OCEAN:
            sprite = CreateOceanTerrainComposite(spriteHashes);
            break;
        default:
            throw CivException("SpriteManager::GetTerrainComposite", "Unknown case of TilesetType: " + to_string(static_cast<int>(type)));
    }
    auto result = storage.emplace(compositeHash, sprite);

    return result.first->second.lock();
}

shared_ptr<Sprite> SpriteManager::GetDummy(){
	return dummy;
}
