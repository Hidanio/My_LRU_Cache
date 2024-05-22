#ifndef LRU_CACHE_LRU_CACHE_H
#define LRU_CACHE_LRU_CACHE_H

#include <unordered_map>
#include <string>
#include <list>
#include <iterator>
#include <utility>

class LRU_Cache {
public:
    // TODO: don't need this
    LRU_Cache() = delete;

    explicit LRU_Cache(size_t capacity);

    LRU_Cache(const LRU_Cache &other);

    LRU_Cache &operator=(const LRU_Cache &other);

    LRU_Cache(LRU_Cache &&other) noexcept;

    LRU_Cache &operator=(LRU_Cache &&other) noexcept;

    ~LRU_Cache();

    // TODO: consider adding noexcept here and below
    bool isEmpty() const;

    // TODO: consider better name consistency, i.e. getSize/isEmpty or size/empty (STL style)
    size_t size() const;

    void clear();

    // TODO: take key by value to allow cache.put(std::move(key), value)
    void put(const std::string &key, int value);

    // TODO: where's get? :)

    // TODO: take a look at std::string_view, no memory allocation for cache.removeElement("my static string")
    void removeElement(const std::string &key);


private:
    struct CacheItemNode {
    // TODO: you can get rid of public for struct
    public:
        std::string key;
        // TODO: default value doesn't seem to make sense as the only constructor sets it anyway
        int value = 0;

        // TODO: explicit is not needed here
        // TODO: also might mark the constructor noexcept
        explicit CacheItemNode(std::string key, int value) : key(std::move(key)), value(value) {}
    };

    std::unordered_map<std::string, std::list<CacheItemNode>::iterator> accessStorage_;
    std::list<CacheItemNode> itemList_;
    size_t capacity_ = 0;
    size_t size_ = 0;


    // TODO: do we actually need our own implementation? we could've just defined
    //       using Iterator = typename std::list<CacheItemNode>::iterator instead
    //       and get rid of this class completely
    class Iterator {
    private:
        using list_iterator = std::list<CacheItemNode>::iterator;
        using ptrItemNode = CacheItemNode *;
        using refItemNode = CacheItemNode &;

        list_iterator it;

    public:
        explicit Iterator(list_iterator newIt) : it(newIt) {}

        refItemNode operator*() const {
            return *it;
        }

        ptrItemNode operator->() const {
            return &(*it);
        }

        Iterator &operator++() {
            ++it;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator operator--() {
            --it;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const Iterator &other) const {
            return it == other.it;
        }

        bool operator!=(const Iterator &other) const {
            return it != other.it;
        }
    };

public:
    // TODO: I'd move these methods to the first public section
    //       for ease of reading public interface
    Iterator begin();

    Iterator end();

    // TODO: better also define const versions of your iterator, i.e. cbegin/cend
    //       and const versions of begin/end also returning const_iterator
};


#endif //LRU_CACHE_LRU_CACHE_H
