/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "artifact_card.h"
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