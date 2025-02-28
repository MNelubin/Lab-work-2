/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef DEFENCE_SPELL_CARD_H
#define DEFENCE_SPELL_CARD_H

#include "spell_card.h"

/**
 * @brief Specialized spell for defense
 * 
 * Inherits from Spell_Card and adds defense mechanics.
 */
class DefenceSpellCard : public Spell_Card {
private:
    int base_def; ///< Base defense value

public:
    /**
     * @brief Construct a new Defence Spell Card object
     * 
     * @param name Initial display name for the card
     * @param description Initial effect description text
     * @param rarity Starting rarity classification
     * @param mana_cost Base mana cost required to play
     * @param elem Associated element
     * @param base_def Base defense value
     */
    DefenceSpellCard(const std::string& name, const std::string& description,
                    Rarity rarity, int mana_cost, Element elem, 
                    int base_def);

    /**
     * @brief Get base defense value
     * @return Current base defense
     */
    int get_base_def() const;
    
    /**
     * @brief Update base defense value
     * @param new_def Must be positive
     * @pre new_def > 0
     * @throws std::invalid_argument if base_def <= 0
     * @post new_def == get_base_def()
     */
    void set_base_def(int new_def);
};

#endif