/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "beast_card.h"
#include <stdexcept>

Beast_Card::Beast_Card(const std::string& name, const std::string& description,
                       Rarity rarity, int mana_cost, int base_dmg, Tribe tribe)
    : Card(name, description, rarity, mana_cost), base_dmg(base_dmg), tribe(tribe) 
{
    if (base_dmg <= 0) {
        throw std::invalid_argument("Base damage must be positive");
    }
}

int Beast_Card::get_base_dmg() const {
    return base_dmg;
}

void Beast_Card::set_base_dmg(int new_dmg) {
    if (new_dmg <= 0) {
        throw std::invalid_argument("Base damage must be positive");
    }
    base_dmg = new_dmg;
}

Tribe Beast_Card::get_tribe() const {
    return tribe;
}

void Beast_Card::set_tribe(Tribe new_tribe) {
    tribe = new_tribe;
} 