/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "shield_card.h"
#include <stdexcept>

Shield_Card::Shield_Card(const std::string& name, const std::string& description,
                         Rarity rarity, int mana_cost, int usage)
    : Card(name, description, rarity, mana_cost), usage(usage) 
{
    if (usage <= 0) {
        throw std::invalid_argument("Usage must be positive");
    }
}

int Shield_Card::get_usage() const {
    return usage;
}

void Shield_Card::set_usage(int new_usage) {
    if (new_usage <= 0) {
        throw std::invalid_argument("Usage must be positive");
    }
    usage = new_usage;
} 