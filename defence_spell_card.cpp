/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "defence_spell_card.h"
#include <stdexcept>

DefenceSpellCard::DefenceSpellCard(const std::string& name, const std::string& description,
                                  Rarity rarity, int mana_cost, Element elem,
                                  int base_def)
    : Spell_Card(name, description, rarity, mana_cost, elem),
      base_def(base_def) 
{
    if (base_def <= 0) {
        throw std::invalid_argument("Base defense must be positive");
    }
}

int DefenceSpellCard::get_base_def() const {
    return base_def;
}

void DefenceSpellCard::set_base_def(int new_def) {
    if (new_def <= 0) {
        throw std::invalid_argument("Base defense must be positive");
    }
    base_def = new_def;
}