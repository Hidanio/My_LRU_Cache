#ifndef LRU_CACHE_LRU_CACHE_H
#define LRU_CACHE_LRU_CACHE_H

#include <unordered_map>
#include <string>
#include <list>
#include <iterator>
#include <utility>

class LRU_Cache {
public:
    LRU_Cache() = delete;

    explicit LRU_Cache(size_t capacity);

    LRU_Cache(const LRU_Cache &other);

    LRU_Cache& operator=(const LRU_Cache &other);

    LRU_Cache(LRU_Cache &&other) noexcept;

    LRU_Cache& operator=(LRU_Cache &&other) noexcept;

    ~LRU_Cache();

    bool isEmpty() const;

    size_t size() const;

    void clear();

    void put(std::string &key, int value);

    void removeElement(const std::string &key);

private:
    struct CacheItemNode {
    public:
        std::string key;
        int value = 0;

       explicit CacheItemNode(std::string key, int value) : key(std::move(key)), value(value) {}
    };

    std::unordered_map<std::string, std::list<CacheItemNode>::iterator> accessStorage_;
    std::list<CacheItemNode> itemList_;
    size_t capacity_ = 0;
    size_t size_ = 0;


    class Iterator {
    public:

    private:
        using list_iterator = std::list<CacheItemNode>::iterator;
        list_iterator it;
    };
};


#endif //LRU_CACHE_LRU_CACHE_H
