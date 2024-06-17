#ifndef LRU_CACHE_LRU_CACHE_H
#define LRU_CACHE_LRU_CACHE_H

#include <unordered_map>
#include <string>
#include <list>
#include <iterator>
#include <utility>

class LRU_Cache {

private:
    struct CacheItemNode {
    public:
        std::string key;
        int value;

        CacheItemNode(std::string key, int value) noexcept: key(std::move(key)), value(value) {}
    };

    std::unordered_map<std::string_view , std::list<CacheItemNode>::iterator> accessStorage_;
    std::list<CacheItemNode> itemList_;
    size_t capacity_ = 0;
    size_t size_ = 0;
    using const_iterator = typename std::list<CacheItemNode>::const_iterator;

public:
    LRU_Cache() = delete;

    ~LRU_Cache() = default;

    explicit LRU_Cache(size_t capacity);

    LRU_Cache(const LRU_Cache &other);

    LRU_Cache &operator=(const LRU_Cache &other);

    LRU_Cache(LRU_Cache &&other) noexcept;

    LRU_Cache &operator=(LRU_Cache &&other) noexcept;

    int operator[](const std::string& key);

    bool empty() const noexcept {
        return size_ == 0;
    }

    size_t size() const noexcept {
        return size_;
    }

    void clear() noexcept {
        itemList_.clear();
        accessStorage_.clear();
        size_ = 0;
    }


    void put(std::string key, int value);

    std::optional<int> get(std::string_view key);

    void remove(const std::string &key);

    const_iterator begin() const { return std::begin(itemList_); }

    const_iterator end() const { return std::end(itemList_); }

    const_iterator cbegin() const { return std::cbegin(itemList_); }

    const_iterator cend() const { return std::cend(itemList_); }
};


#endif //LRU_CACHE_LRU_CACHE_H
