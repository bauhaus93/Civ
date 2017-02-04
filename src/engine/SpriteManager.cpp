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

    ditherMask = CreateDiamondFromSpritesheet(TERRAIN1, Point{ 1, 447 });
    ditherMask->ReplaceColor(RGBAColor{ 0, 0, 0, 0xFF }, RGBAColor{ 0xFF, 0xFF, 0xFF, 0xFF});
    ditherMask->ReplaceColor(RGBAColor{ 0x87, 0x87, 0x87, 0xFF }, RGBAColor{ 0, 0, 0, 0});
    ditherMask->ReplaceColor(RGBAColor{ 0xFF, 0, 0xFF, 0xFF }, RGBAColor{ 0, 0, 0, 0});

    factory.MakeTransparent(RGBColor{ 0x87, 0x87, 0x87 });
    factory.MakeTransparent(RGBColor{ 0xFF, 0x00, 0xFF });

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
		else
			++iter;
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

bool SpriteManager::RegisterSprite(shared_ptr<Sprite> sprite, uint32_t hash){
    auto result = storage.emplace(hash, sprite);
    return result.second;
}

shared_ptr<Sprite> SpriteManager::CreateFromSpritesheet(const string& sheetname, const Rect& rect){
    auto sprite = factory.CreateSprite(sheetname, rect);
	sprite->CalculateHash();			//sprite hashes only calculate for direct spritesheet descendents, not composite ones
    uint32_t hash = sprite->GetHash();

    auto result = storage.emplace(hash, sprite);

    return shared_ptr<Sprite>(result.first->second);
}

shared_ptr<Sprite> SpriteManager::CreateDiamondFromSpritesheet(const std::string& sheetname, const Point& pos){
	return CreateFromSpritesheet(sheetname, Rect{pos, 64, 32});
}


int SpriteManager::GetStorageSize() const{
	return storage.size();
}

void SpriteManager::PrintStatistics() const{
    vector<pair<uint32_t, int>> usecounts;

    for(auto pair : storage){
        if(pair.second.expired())
            usecounts.push_back(make_pair(pair.first, 0));
        else{
            auto e = pair.second.lock();
            usecounts.push_back(make_pair(pair.first, e.use_count()));
        }
    }
    sort(usecounts.begin(), usecounts.end(), [](const pair<uint32_t, int>& a, const pair<uint32_t, int>& b){ return a.second > b.second;});

    size_t i = 0;
    int sum = 0;
    int median = 0;
    for(auto e : usecounts){
        if(++i == usecounts.size() / 2)   //don't care about the exact value
            median = e.second;
        sum += e.second;
    }

    cout << "####################################" << endl;
    cout << "SpriteManager storage use count info" << endl;
    cout << "size:\t\t" << usecounts.size() << endl;
    cout << "avg:\t\t" << (double) sum / usecounts.size() << endl;
    cout << "median:\t\t" << median << endl;
    cout << "top 5 sprites" << endl;
    for(auto iter = usecounts.begin(); iter != usecounts.end() && iter < usecounts.begin() + 5; ++iter)
        cout << iter->first << ":\t" << iter->second << endl;
    cout << "####################################" << endl;
}
