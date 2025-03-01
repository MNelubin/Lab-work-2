/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "weapon_card.h"
#include <stdexcept>

Weapon_Card::Weapon_Card(const std::string& name, const std::string& description,
                         Rarity rarity, int mana_cost, int dmg_up)
    : Card(name, description, rarity, mana_cost), dmg_up(dmg_up) 
{
    if (dmg_up <= 0) {
        throw std::invalid_argument("Damage increase must be positive");
    }
}

int Weapon_Card::get_dmg_up() const {
    return dmg_up;
}

void Weapon_Card::set_dmg_up(int new_dmg_up) {
    if (new_dmg_up <= 0) {
        throw std::invalid_argument("Damage increase must be positive");
    }
    dmg_up = new_dmg_up;
} 