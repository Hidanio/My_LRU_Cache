#include <iostream>
#include "LRU_Cache.h"

int main() {
    LRU_Cache cache(3);
    cache.put("item2", 100);
    cache.put("item1", 200);
    cache.put("item3", 300);

    std::cout << cache[4] << "\n";

    for (auto it = cache.begin(); it != cache.end(); ++it) {
        std::cout << "Key:" << it->key << ", Value:" << it->value << "\n";
    }

    cache.put("item1+1", 110);
    std::cout << "===================" << "\n";

    for (auto& it: cache) {
        std::cout << "Key:" << it.key << ", Value:" << it.value << "\n";
    }

    cache.get("item1");
    std::cout << "===================" << "\n";

    for (auto it = cache.begin(); it != cache.end(); ++it) {
        std::cout << "Key:" << it->key << ", Value:" << it->value << "\n";
    }
    return 0;
}
