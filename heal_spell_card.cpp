/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "heal_spell_card.h"
#include <stdexcept> 

// Constructor realisation
Heal_Spell_Card::Heal_Spell_Card(
    const std::string& name, 
    const std::string& description,
    Rarity rarity, 
    int mana_cost, 
    Element elem, 
    int heal, 
    float eff
) : Spell_Card(name, description, rarity, mana_cost, elem), base_heal(heal), efficiency_deg(eff) 
{
    if(heal <= 0 || eff <= 0) {
        throw std::invalid_argument("Invalid heal/efficiency values");
    }
}

// Getter for base_heal
int Heal_Spell_Card::get_base_heal() const {
    return base_heal;
}

// Setter for base_heal
void Heal_Spell_Card::set_base_heal(int new_heal) {
    if (new_heal <= 0) {
        throw std::invalid_argument("Heal value must be positive");
    }
    base_heal = new_heal;
}

// Getter for efficiency_deg
float Heal_Spell_Card::get_eff() const {
    return efficiency_deg;
}

// Setter for efficiency_deg 
void Heal_Spell_Card::set_eff(float new_eff) {
    if (new_eff <= 0) {
        throw std::invalid_argument("Efficiency must be positive");
    }
    efficiency_deg = new_eff;
}