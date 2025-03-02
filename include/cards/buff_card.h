/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef BUFF_CARD_H
#define BUFF_CARD_H

#include "card.h"

/**
 * @brief Specialized card for buffs
 * 
 * Inherits from Card and adds buff-specific properties.
 */
class Buff_Card : public Card {
private:
    float buff_amount; ///< Amount of buff

public:
    /**
     * @brief Construct a new Buff Card object
     * 
     * @param name Initial display name for the card
     * @param description Initial effect description text
     * @param rarity Starting rarity classification
     * @param mana_cost Base mana cost required to play
     * @param buff_amount Amount of buff
     */
    Buff_Card(const std::string& name, const std::string& description,
              Rarity rarity, int mana_cost, float buff_amount);

    /**
     * @brief Get buff amount
     * @return Current buff amount
     */
    float get_buff_amount() const;
    
    /**
     * @brief Update buff amount
     * @param new_buff_amount Must be positive
     * @pre new_buff_amount > 0
     * @throws std::invalid_argument if buff_amount <= 0
     * @post new_buff_amount == get_buff_amount()
     */
    void set_buff_amount(float new_buff_amount);
};

#endif