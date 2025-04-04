#include <iostream>

namespace creatures {

class Animal {
public:
    void attack(const std::string& toWho);
private:
    std::string name{};
};

}