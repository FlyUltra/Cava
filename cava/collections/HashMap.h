#ifndef CAVA_HASHMAP_H
#define CAVA_HASHMAP_H

#include <unordered_map>
#include "../types/object/Object.h"

template <typename K = Object, typename V = Object>
class HashMap {
private:
    std::unordered_map<K, V> internalMap;

public:
    HashMap() = default;

    void put(K key, V value) {
        internalMap[key] = std::move(value);
    }

    V get(K key) {
        auto it = internalMap.find(key);
        if (it != internalMap.end()) {
            return it->second;
        }
        return V();
    }

    bool containsKey(K key) const {
        return internalMap.find(key) != internalMap.end();
    }

    int size() const {
        return static_cast<int>(internalMap.size());
    }

    void clear() {
        internalMap.clear();
    }
};

#endif