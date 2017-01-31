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

	dummy = move(factory.CreateSprite(TERRAIN1, Rect{1, 1, 64, 32}));

    Logger::Write("Created sprite manager");
}

SpriteManager::~SpriteManager(){
    Logger::Write("Destroyed sprite manager");
}

/*void SpriteManager::LoadSpritesheet(const string& sheetname, const string& filename){
    factory.AddSpriteSheet(sheetname, filename);
}

void SpriteManager::AddSpritesheetTransparency(RGBColor color){
    factory.MakeTransparent(color);
}*/

Sprite& SpriteManager::CreateFromSpritesheet(const string& sheetname, const Rect& rect){
    Sprite sprite = factory.CreateSprite(sheetname, rect);
    uint32_t hash = sprite.GetHash();

    auto result = storage.emplace(hash, move(sprite));

    //if basic spritesheet sprites collide, hash functions should definitly be changed
	//actually not, because eg extended terrain sets all want to add same basic floor
    //assert(result.second == true);

    return result.first->second;
}

Sprite& SpriteManager::CreateDiamondFromSpritesheet(const std::string& sheetname, const Point& pos){
	return CreateFromSpritesheet(sheetname, Rect{pos, 64, 32});
}

Sprite SpriteManager::CreateBasicTerrainComposite(const vector<uint32_t>& spriteHashes){
    assert(spriteHashes.size() >= 2);

    try{
        Sprite sprite { storage.at(spriteHashes[0]) };   //basic sprite

        if(spriteHashes.at(1) != 0)
            sprite.Add(storage.at(spriteHashes[1]));     //resource sprite, if existing
        //TODO Other sprite hashes would indicate neighbours, which should be
        //used to create a dithered layer on the sprite

        return sprite;
    }
    catch(const out_of_range& e){
        throw CivException("SpriteManager::CreateBasicTerrainComposite", string("Sprite hash, which should exist, not existing in storage: ") + e.what());
    }
}

Sprite SpriteManager::CreateExtendedTerrainComposite(const vector<uint32_t>& spriteHashes){
    assert(spriteHashes.size() >= 3);

    try{
        Sprite sprite { storage.at(spriteHashes[0]) };   //basic sprite

        sprite.Add(storage.at(spriteHashes[2]));         //extended sprite (eg forest)

        if(spriteHashes.at(1) != 0)
            sprite.Add(storage.at(spriteHashes[1]));    //resource sprite, if existing
        //TODO Other sprite hashes would indicate neighbours, which should be
        //used to create a dithered layer on the sprite

        return sprite;
    }
    catch(const out_of_range& e){
        throw CivException("SpriteManager::CreateExtendedTerrainComposite", string("Sprite hash, which should exist, not existing in storage: ") + e.what());
    }
}

Sprite SpriteManager::CreateOceanTerrainComposite(const vector<uint32_t>& spriteHashes){
    assert(spriteHashes.size() >= 6);
    const static Point coastEdges[] = { Point{ 16, 0 },
                                        Point{ 16, 16},
                                        Point{ 0, 8},
                                        Point{ 32, 8}};

    try{
        Sprite sprite { storage.at(spriteHashes[0]) };   //basic sprite

        for(int i = 0; i < 4; i++){
            if(spriteHashes[2 + i] != 0)
                sprite.Add(storage.at(spriteHashes[2 + i]), Point{0, 0}, coastEdges[i]);    //coastline, if existing
        }

        if(spriteHashes.at(1) != 0)
            sprite.Add(storage.at(spriteHashes[1]));    //resource sprite, if existing
        return sprite;
    }
    catch(const out_of_range& e){
        throw CivException("SpriteManager::CreateOceanTerrainComposite", string("Sprite hash, which should exist, not existing in storage: ") + e.what());
    }
}

Sprite& SpriteManager::GetTerrainComposite(const std::vector<uint32_t>& spriteHashes, TilesetType type){
    uint32_t compositeHash = Hash(spriteHashes);

    auto found = storage.find(compositeHash);

    if(found != storage.end()) //composite sprite already existing, so return it
        return found->second;

		cout << "storage size: " << storage.size() << endl;

    //We use the composite hash for lookup, because it is easier to calculate
    //(we don't have to create the sprite first, to see if the created sprite hash is already existing)
    Sprite sprite;
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
    assert(result.second == true);  //we checked it before

    return result.first->second;
}

Sprite& SpriteManager::GetDummy(){
	return dummy;
}
