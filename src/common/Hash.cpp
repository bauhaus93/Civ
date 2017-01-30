#include "Hash.h"

//Src: https://en.wikipedia.org/wiki/Jenkins_hash_function
uint32_t Hash(const std::vector<uint32_t>& data){
    uint32_t hash = 0;
    for(auto e : data){
        hash += e;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}
