#ifndef KEYED_MEMORY_PERSISTENCE_HH
#define KEYED_MEMORY_PERSISTENCE_HH

#include <string>
#include <unordered_map>
#include <memory>


template <typename T>
class KeyedMemoryPersistence: public Persistence<T> {
public:
    KeyedMemoryPersistence(const std::string& table): Persistence<T>(table) { }
    ~KeyedMemoryPersistence(void) { }

    virtual void add(T& item) {
        contents.insert({item.getId(), item});
    }

    virtual std::unique_ptr<T> get(const std::string& id) const {
        auto it = contents.find(id);

        if (it == contents.end()) {
            return nullptr;
        } else {
            return std::make_unique<T>(contents.at(id));
        }
    }

    virtual bool matches(MatcherFunction matches, const std::string& name) const {
        for (const auto& pair: contents) {
            if (matches(pair.second, name))
                return true;
        }
        return false;
    }

private:
    std::unordered_map<std::string, T> contents;
};


#endif /* KEYED_MEMORY_PERSISTENCE_HH */
