#include "../include/Animal.h"

namespace creatures {

void Animal::attack(const std::string& toWho) {
        std::cout << this->name << " attacks to " << toWho << '\n' ;
}

}