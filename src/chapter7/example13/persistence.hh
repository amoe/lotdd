#ifndef PERSISTENCE_HH
#define PERSISTENCE_HH

#include <string>
#include <memory>
#include "serializable.hh"

using MatcherFunction = bool(*)(const Serializable&, const std::string&);

template <typename T>
class Persistence {
public:
    Persistence(const std::string& table): table(table) { }
    virtual ~Persistence(void) { }
    
    virtual void add(T&) = 0;
    virtual std::unique_ptr<T> get(const std::string& id) const = 0;
    virtual bool matches(MatcherFunction, const std::string&) const = 0;

protected:
    std::string table;
};

#endif /* PERSISTENCE_HH */


