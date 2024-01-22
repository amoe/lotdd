#ifndef BRANCH_HH
#define BRANCH_HH

#include "serializable.hh"

class Branch: public Serializable {
public:
    Branch(std::string id, std::string name): id(id), name(name) { }
    
    std::string getName() const {
        return name;
    }

    std::string getId() const {
        return id;
    }

private:
    std::string id;
    std::string name;
};



#endif /* BRANCH_HH */


