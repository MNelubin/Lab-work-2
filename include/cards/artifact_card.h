/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef ARTIFACT_CARD_H
#define ARTIFACT_CARD_H

#include "card.h"

/**
 * @brief Specialized card for artifacts
 * 
 * Inherits from Card and adds artifact-specific properties.
 */
class Artifact_Card : public Card {
private:
    float multiplier; ///< Multiplier value for the artifact
    

public:
    /**
     * @brief Construct a new Artifact Card object
     * 
     * @param name Initial display name for the card
     * @param description Initial effect description text
     * @param rarity Starting rarity classification
     * @param mana_cost Base mana cost required to play
     * @param multiplier Multiplier value for the artifact
     */
    Artifact_Card(const std::string& name, const std::string& description,
                  Rarity rarity, int mana_cost, float multiplier);

    /**
     * @brief Get multiplier value
     * @return Current multiplier
     */
    float get_multiplier() const;
    
    /**
     * @brief Update multiplier value
     * @param new_multiplier Must be positive
     * @pre new_multiplier > 0
     * @throws std::invalid_argument if multiplier <= 0
     * @post new_multiplier == get_multiplier()
     */
    void set_multiplier(float new_multiplier);

    void use(Player& user, Player& target) override;
    CardType get_type() const override;
};

#endif 