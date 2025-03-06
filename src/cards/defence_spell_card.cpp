/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/defence_spell_card.h"
#include "../../include/player/player.h"
#include "../../include/player/character.h"

#include <stdexcept>

Defence_Spell_Card::Defence_Spell_Card(const std::string& name, const std::string& description,
                                  Rarity rarity, int mana_cost, Element elem,
                                  int base_def)
    : Spell_Card(name, description, rarity, mana_cost, elem),
      base_def(base_def) 
{
    if (base_def <= 0) {
        throw std::invalid_argument("Base defense must be positive");
    }
}
Defence_Spell_Card::Defence_Spell_Card(const std::string& name, const std::string& description,
                                  Rarity rarity, int mana_cost, Element elem)
    : Spell_Card(name, description, rarity, mana_cost, elem),
      base_def(0) {}

int Defence_Spell_Card::get_base_def() const {
    return base_def;
}

void Defence_Spell_Card::set_base_def(int new_def) {
    if (new_def <= 0) {
        throw std::invalid_argument("Base defense must be positive");
    }
    base_def = new_def;
}

void Defence_Spell_Card::use(Player& user, Player& target) {
    /**
     * @brief Increase defense
     */
    int armor_amount=static_cast<int>(get_base_def() * user.get_character().get_armor_multiplier());
    user.set_armor(armor_amount + user.get_armor());
}

CardType Defence_Spell_Card::get_type() const {
    return CardType::DefenceSpell;
}