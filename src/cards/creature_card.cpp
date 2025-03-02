/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/creature_card.h"
#include <stdexcept>

Creature_Card::Creature_Card(const std::string& name, const std::string& description,
                             Rarity rarity, int mana_cost, int base_dmg, float weapon_multiplier)
    : Card(name, description, rarity, mana_cost), base_dmg(base_dmg), weapon_multiplier(weapon_multiplier) 
{
    if (base_dmg <= 0) {
        throw std::invalid_argument("Base damage must be positive");
    }
    if (weapon_multiplier <= 0) {
        throw std::invalid_argument("Weapon multiplier must be positive");
    }
}

int Creature_Card::get_base_dmg() const {
    return base_dmg;
}

void Creature_Card::set_base_dmg(int new_dmg) {
    if (new_dmg <= 0) {
        throw std::invalid_argument("Base damage must be positive");
    }
    base_dmg = new_dmg;
}

float Creature_Card::get_weapon_multiplier() const {
    return weapon_multiplier;
}

void Creature_Card::set_weapon_multiplier(float new_multiplier) {
    if (new_multiplier <= 0) {
        throw std::invalid_argument("Weapon multiplier must be positive");
    }
    weapon_multiplier = new_multiplier;
} 