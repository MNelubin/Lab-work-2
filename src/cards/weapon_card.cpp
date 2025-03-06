/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/weapon_card.h"
#include "../../include/player/player.h"

#include <stdexcept>

Weapon_Card::Weapon_Card(const std::string& name, const std::string& description,
                         Rarity rarity, int mana_cost, int dmg_up)
    : Card(name, description, rarity, mana_cost), dmg_up(dmg_up) 
{
    if (dmg_up <= 0) {
        throw std::invalid_argument("Damage increase must be positive");
    }
}

Weapon_Card::Weapon_Card(const std::string& name, const std::string& description,
                         Rarity rarity, int mana_cost)
    : Card(name, description, rarity, mana_cost), dmg_up(0){}


int Weapon_Card::get_dmg_up() const {
    return dmg_up;
}

void Weapon_Card::set_dmg_up(int new_dmg_up) {
    if (new_dmg_up <= 0) {
        throw std::invalid_argument("Damage increase must be positive");
    }
    dmg_up = new_dmg_up;
} 

void Weapon_Card::use(Player& user, Player& target) {
    /**
     * @brief Deal enhanced damage
     */
    user.add_weapon_bonus(get_dmg_up());
}

CardType Weapon_Card::get_type() const {
    return CardType::Weapon;
}