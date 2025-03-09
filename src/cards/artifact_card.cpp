/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/artifact_card.h"
#include "../../include/player/player.h"

#include <stdexcept>
#include <iostream>

Artifact_Card::Artifact_Card(const std::string& name, const std::string& description,
                             Rarity rarity, int mana_cost, float multiplier)
    : Card(name, description, rarity, mana_cost), multiplier(multiplier) 
{
    if (multiplier <= 0) {
        throw std::invalid_argument("Multiplier must be positive");
    }
}

float Artifact_Card::get_multiplier() const {
    return multiplier;
}

void Artifact_Card::set_multiplier(float new_multiplier) {
    if (new_multiplier <= 0) {
        throw std::invalid_argument("Multiplier must be positive");
    }
    multiplier = new_multiplier;
} 

void Artifact_Card::use(Player& user, Player& target) {
    /**
     * @brief Apply artifact's multiplier to player's attack and defense
     * 
     * Modifies all attack heal and weapon multipliers,
     * makes effects persistent until reset
     */
    user.apply_attack_multiplier(user.get_cumulative_attack_multiplier() * get_multiplier());
    user.apply_heal_multiplier(user.get_cumulative_heal_multiplier() * get_multiplier());
    user.set_cumulative_weapon_bonus(user.get_cumulative_weapon_bonus() * get_multiplier());
    
}

CardType Artifact_Card::get_type() const {
    return CardType::Artifact;
}



/**
* @brief Generate random properties for Artifact card
*/
void Artifact_Card::generate_properties() {
        // Generate random rarity first
        Rarity random_rarity = generate_random_rarity();
        set_rarity(random_rarity);
        std::uniform_int_distribution<int> name_dist(0, artifact_names.size() - 1);
        std::uniform_int_distribution<int> desc_dist(0, artifact_descriptions.size() - 1);
        
        set_name(artifact_names[name_dist(rng)]);
        set_description(artifact_descriptions[desc_dist(rng)]);
        
        switch (get_rarity()) {
            case Rarity::Common:
                multiplier = 1.1f + static_cast<float>(rng() % 5) * 0.1f;
                mana_cost = 1 + static_cast<int>(rng() % 2);
                break;
            case Rarity::Uncommon:
                multiplier = 1.3f + static_cast<float>(rng() % 8) * 0.1f;
                mana_cost = 1 + static_cast<int>(rng() % 3);
                break;
            case Rarity::Rare:
                multiplier = 1.6f + static_cast<float>(rng() % 11) * 0.1f;
                mana_cost = 2 + static_cast<int>(rng() % 3);
                break;
            case Rarity::Epic:
                multiplier = 2.0f + static_cast<float>(rng() % 16) * 0.1f;
                mana_cost = 2 + static_cast<int>(rng() % 5);
                break;
        }
    }

void Artifact_Card::print_key_info() const {
    std::cout << "Multiplier: " << multiplier;
}