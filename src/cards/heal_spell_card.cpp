/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/heal_spell_card.h"
#include "../../include/player/player.h"
#include "../../include/player/character.h"

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

// Default constructor implementation
Heal_Spell_Card::Heal_Spell_Card()
    : Spell_Card("Unnamed Heal Spell", "No description", Rarity::Common, 0, Element::Water), 
      base_heal(5), efficiency_deg(1.0f) 
{
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

void Heal_Spell_Card::use(Player& user, Player& target) {
    /**
     * @brief Heal target player
     */

    int heal_amount=static_cast<int>(
    get_base_heal() * user.get_character().get_heal_multiplier() 
    * user.get_cumulative_heal_multiplier() * get_eff());
    user.set_hp(heal_amount + user.get_hp());

    user.end_turn();
}

CardType Heal_Spell_Card::get_type() const {
    return CardType::HealSpell;
}


/**
* @brief Generate random properties for Heal Spell card
*/
void Heal_Spell_Card::generate_properties() {
    // Generate random rarity first
    Rarity random_rarity = generate_random_rarity();
    set_rarity(random_rarity);

    std::uniform_int_distribution<int> name_dist(0, heal_names.size() - 1);
    std::uniform_int_distribution<int> desc_dist(0, heal_descriptions.size() - 1);
    
    set_name(heal_names[name_dist(rng)]);
    set_description(heal_descriptions[desc_dist(rng)]);
    set_element(static_cast<Element>(rng() % 4));
    
    switch (get_rarity()) {
        case Rarity::Common:
            base_heal = 3 + static_cast<int>(rng() % 6);
            efficiency_deg = 1.0f + static_cast<float>(rng() % 3) * 0.1f;
            mana_cost = 1 + static_cast<int>(rng() % 2);
            break;
        case Rarity::Uncommon:
            base_heal = 3 + static_cast<int>(rng() % 10);
            efficiency_deg = 1.2f + static_cast<float>(rng() % 5) * 0.1f;
            mana_cost = 1 + static_cast<int>(rng() % 3);
            break;
        case Rarity::Rare:
            base_heal = 6 + static_cast<int>(rng() % 15);
            efficiency_deg = 1.4f + static_cast<float>(rng() % 8) * 0.1f;
            mana_cost = 2 + static_cast<int>(rng() % 3);
            break;
        case Rarity::Epic:
            base_heal = 10 + static_cast<int>(rng() % 25);
            efficiency_deg = 1.7f + static_cast<float>(rng() % 12) * 0.1f;
            mana_cost = 2 + static_cast<int>(rng() % 5);
            break;
    }
}

void Heal_Spell_Card::print_key_info() const {
    std::cout << "Base Heal: " << base_heal << ", Efficiency: " << efficiency_deg;
}