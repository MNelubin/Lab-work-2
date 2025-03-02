/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/card.h"

// Card class constructor
Card::Card(const std::string& name, const std::string& description, 
         Rarity rarity, int mana_cost)
    : name(name), description(description), 
      rarity(rarity), mana_cost(mana_cost) 
{
}

// Getters methods implementation
std::string Card::get_name() const {
    return name;
}

std::string Card::get_description() const {
    return description;
}

Rarity Card::get_rarity() const {
    return rarity;
}

int Card::get_mana_cost() const {
    return mana_cost;
}

// Setters methods implementation
void Card::set_name(const std::string& new_name) {
    name = new_name;
}

void Card::set_description(const std::string& new_desc) {
    description = new_desc;
}

void Card::set_rarity(Rarity new_rarity) {
    rarity = new_rarity;
}

void Card::set_mana_cost(int new_cost) {
    mana_cost = new_cost;
} 