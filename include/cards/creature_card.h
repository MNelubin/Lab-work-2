/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef CREATURE_CARD_H
#define CREATURE_CARD_H

#include "card.h"

/**
 * @brief Specialized card for creatures
 * 
 * Inherits from Card and adds creature-specific properties.
 */
class Creature_Card : public Card {
private:
    int base_dmg; ///< Base damage value
    float weapon_multiplier; ///< Multiplier for weapon damage

public:
    /**
     * @brief Construct a new Creature Card object
     * 
     * @param name Initial display name for the card
     * @param description Initial effect description text
     * @param rarity Starting rarity classification
     * @param mana_cost Base mana cost required to play
     * @param base_dmg Base damage value
     * @param weapon_multiplier Multiplier for weapon damage
     */
    Creature_Card(const std::string& name, const std::string& description,
                  Rarity rarity, int mana_cost, int base_dmg, float weapon_multiplier);

    /**
     * @brief Get base damage value
     * @return Current base damage
     */
    int get_base_dmg() const;
    
    /**
     * @brief Update base damage value
     * @param new_dmg Must be positive
     * @pre new_dmg > 0
     * @throws std::invalid_argument if base_dmg <= 0
     * @post new_dmg == get_base_dmg()
     */
    void set_base_dmg(int new_dmg);

    /**
     * @brief Get weapon multiplier value
     * @return Current weapon multiplier
     */
    float get_weapon_multiplier() const;
    
    /**
     * @brief Update weapon multiplier value
     * @param new_multiplier Must be positive
     * @pre new_multiplier > 0
     * @throws std::invalid_argument if weapon_multiplier <= 0
     * @post new_multiplier == get_weapon_multiplier()
     */
    void set_weapon_multiplier(float new_multiplier);
};

#endif 