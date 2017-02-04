#pragma once

//Src: https://en.wikipedia.org/wiki/Jenkins_hash_function

template<typename T>
T Hash(T hash){
    return hash;
}

template<typename T, typename... Args>
T Hash(T hash, T first, Args... args){
    hash += first;
    hash += hash << 10;
    hash ^= hash >> 6;

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return Hash(hash, args...);
}
