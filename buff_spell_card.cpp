/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "buff_spell_card.h"
#include <stdexcept>

Buff_Spell_Card::Buff_Spell_Card(const std::string& name, const std::string& description,
                            Rarity rarity, int mana_cost, Element elem,
                            float multiplier)
    : Spell_Card(name, description, rarity, mana_cost, elem),
      multiplier(multiplier) 
{
    if (multiplier <= 0) {
        throw std::invalid_argument("Multiplier must be positive");
    }
}

float Buff_Spell_Card::get_multiplier() const {
    return multiplier;
}

void Buff_Spell_Card::set_multiplier(float new_multiplier) {
    if (new_multiplier <= 0) {
        throw std::invalid_argument("Multiplier must be positive");
    }
    multiplier = new_multiplier;
}
