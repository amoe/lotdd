#ifndef BRANCH_HH
#define BRANCH_HH

class Branch {
public:
    Branch(std::string id, std::string name): id(id), name(name) { }
    
    std::string getName() const {
        return name;
    }

private:
    std::string id;
    std::string name;
};



#endif /* BRANCH_HH */


