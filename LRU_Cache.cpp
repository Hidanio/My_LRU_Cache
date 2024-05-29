#include "LRU_Cache.h"

LRU_Cache::LRU_Cache(size_t capacity) : capacity_(capacity) {
    accessStorage_.reserve(capacity);
}

void LRU_Cache::put(std::string key, int value) {
    auto it = accessStorage_.find(key);
    if (it != accessStorage_.end()) {
        it->second->value = value;
        itemList_.splice(itemList_.begin(), itemList_, it->second);
    } else {
        if (size_ >= capacity_) {
            accessStorage_.erase(itemList_.back().key);
            itemList_.pop_back();
            --size_;
        }
    }

    itemList_.emplace_front(key, value);
    accessStorage_[std::move(key)] = itemList_.begin();
    ++size_;
}

void LRU_Cache::remove(const std::string &key) {
    auto it = accessStorage_.find(key);
    if (it != accessStorage_.end()) {
        itemList_.erase(it->second);
        accessStorage_.erase(key);
    }
}

int LRU_Cache::get(std::string_view key) {
    auto el = accessStorage_.find(key.data());
    if (el == accessStorage_.end()) {
        return -1;
    }

    itemList_.splice(itemList_.begin(), itemList_, el->second);
    accessStorage_[key.data()] = itemList_.begin();

    return accessStorage_[key.data()]->value;
}

LRU_Cache::LRU_Cache(const LRU_Cache &other) : size_(other.size_), capacity_(other.capacity_) {
    itemList_ = other.itemList_;

    for (auto it = itemList_.begin(); it != itemList_.end(); ++it) {
        accessStorage_[it->key] = it;
    }
}

LRU_Cache &LRU_Cache::operator=(const LRU_Cache &other) {
    if (this != &other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        itemList_.clear();
        accessStorage_.clear();
        itemList_ = other.itemList_;

        for (auto it = itemList_.begin(); it != itemList_.end(); ++it) {
            accessStorage_[it->key] = it;
        }
    }
    return *this;
}

int LRU_Cache::operator[](size_t index) const {
    auto it = itemList_.begin();
    for (auto i = 0; i < index; ++i) {
        it++;
    }

    return it->value;
}

LRU_Cache::LRU_Cache(LRU_Cache &&other) noexcept: size_(other.size_), capacity_(other.capacity_),
                                                  itemList_(std::move(other.itemList_)),
                                                  accessStorage_(std::move(other.accessStorage_)) {
    other.size_ = 0;
}

LRU_Cache &LRU_Cache::operator=(LRU_Cache &&other) noexcept {
    if (this != &other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        itemList_ = std::move(other.itemList_);
        accessStorage_ = std::move(other.accessStorage_);
        other.size_ = 0;
    }
    return *this;
}
