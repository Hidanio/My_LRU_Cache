#include <iostream>
#include "LRU_Cache.h"

int main() {
    LRU_Cache cache(3);
    cache.put("item1", 100);
    cache.put("item2", 200);
    cache.put("item3", 300);

    for (auto it = cache.begin(); it != cache.end(); ++it) {
        std::cout << "Key:" << it->key << ", Value:" << it->value << "\n";
    }

    cache.put("item1+1", 110);

    for (auto & it : cache) {
        std::cout << "Key:" << it.key << ", Value:" << it.value << "\n";
    }

    return 0;
}
