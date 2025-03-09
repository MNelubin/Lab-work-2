/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/attack_spell_card.h"
#include "../../include/player/player.h"

#include <stdexcept>
#include <iostream>

Attack_Spell_Card::Attack_Spell_Card(const std::string& name, const std::string& description,
                                    Rarity rarity, int mana_cost, Element elem, int dmg)
    : Spell_Card(name, description, rarity, mana_cost, elem), base_damage(dmg) 
{
    if(dmg <= 0) {
        throw std::invalid_argument("Damage must be positive");
    }
}

// Default constructor implementation
Attack_Spell_Card::Attack_Spell_Card()
    : Spell_Card("Unnamed Attack Spell", "No description", Rarity::Common, 0, Element::Fire), 
      base_damage(3) 
{
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

/**
* @brief Generate random properties for Attack Spell card
*/
void Attack_Spell_Card::generate_properties() {
    // Generate random rarity first
    Rarity random_rarity = generate_random_rarity();
    set_rarity(random_rarity);

    // Randomly select name, description, and element
    std::uniform_int_distribution<int> name_dist(0, spell_names.size() - 1);
    std::uniform_int_distribution<int> desc_dist(0, spell_descriptions.size() - 1);
    
    set_name(spell_names[name_dist(rng)]);
    set_description(spell_descriptions[desc_dist(rng)]);
    set_element(static_cast<Element>(rng() % 4));
    
    // Generate damage based on rarity
    switch (get_rarity()) {
        case Rarity::Common:
            base_damage = 3 + static_cast<int>(rng() % 4);
            mana_cost = 1 + static_cast<int>(rng() % 2);
            break;
        case Rarity::Uncommon:
            base_damage = 5 + static_cast<int>(rng() % 6);
            mana_cost = 1 + static_cast<int>(rng() % 3);
            break;
        case Rarity::Rare:
            base_damage = 8 + static_cast<int>(rng() % 8);
            mana_cost = 2 + static_cast<int>(rng() % 3);
            break;
        case Rarity::Epic:
            base_damage = 12 + static_cast<int>(rng() % 12);
            mana_cost = 2 + static_cast<int>(rng() % 5);
            break;
    }
}

void Attack_Spell_Card::print_key_info() const {
    std::cout << "Base Damage: " << base_damage;
}


