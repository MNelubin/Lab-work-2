/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/artifact_card.h"
#include "../../include/player/player.h"

#include <stdexcept>

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