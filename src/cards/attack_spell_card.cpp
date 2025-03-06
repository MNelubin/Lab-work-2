/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/attack_spell_card.h"
#include "../../include/player/player.h"

#include <stdexcept>

Attack_Spell_Card::Attack_Spell_Card(const std::string& name, const std::string& description,
                                    Rarity rarity, int mana_cost, Element elem, int dmg)
    : Spell_Card(name, description, rarity, mana_cost, elem), base_damage(dmg) 
{
    if(dmg <= 0) {
        throw std::invalid_argument("Damage must be positive");
    }
}

int Attack_Spell_Card::get_base_damage() const {
    return base_damage;
}

void Attack_Spell_Card::set_base_damage(int new_damage) {
    if(new_damage <= 0) {
        throw std::invalid_argument("Damage value must be positive");
    }
    base_damage = new_damage;
} 

void Attack_Spell_Card::use(Player& user, Player& target) {
    /**
     * @brief Deal spell damage
     */
    target.take_damage(get_base_damage() * user.get_cumulative_attack_multiplier());
    user.end_turn();
}

CardType Attack_Spell_Card::get_type() const {
    return CardType::AttackSpell;
}
