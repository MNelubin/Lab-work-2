/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/spell_card.h"

Spell_Card::Spell_Card(const std::string& name, const std::string& description,
                       Rarity rarity, int mana_cost, Element element)
    : Card(name, description, rarity, mana_cost), element(element) {}

Element Spell_Card::get_element() const {
    return element;
}

void Spell_Card::set_element(Element new_element) {
    element = new_element;
} 