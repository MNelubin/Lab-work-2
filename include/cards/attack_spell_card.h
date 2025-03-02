/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef ATTACK_SPELL_CARD_H
#define ATTACK_SPELL_CARD_H

#include "spell_card.h"

/**
 * @brief Specialized spell for direct damage
 * 
 * Inherits from Spell_Card and adds damage mechanics.
 */
class Attack_Spell_Card : public Spell_Card {
private:
    int base_damage; ///< Base damage value without modifiers

public:
    /**
     * @brief Construct a new Attack Spell Card object
     * 
     * @param[in] name Initial display name for the card
     * @param[in] description Initial effect description text
     * @param[in] rarity Starting rarity classification
     * @param[in] mana_cost Base mana cost required to play
     * @param[in] elem Associated element
     * @param[in] dmg Base damage value
     */
    Attack_Spell_Card(const std::string& name, const std::string& description,
                     Rarity rarity, int mana_cost, Element elem, int dmg);
    
    /**
     * @brief Get base damage value
     * @return Current base damage
     */
    int get_base_damage() const;
    
    /**
     * @brief Update damage value
     * @param[in] new_damage Must be positive
     * @pre new_damage > 0
     * @post get_base_damage()==new_damage
     * @throws std::invalid_argument if damage <=0
     */
    void set_base_damage(int new_damage);
};

#endif 