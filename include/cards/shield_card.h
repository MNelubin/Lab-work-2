/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef SHIELD_CARD_H
#define SHIELD_CARD_H

#include "card.h"

/**
 * @brief Specialized card for shields
 * 
 * Inherits from Card and adds shield-specific properties.
 */
class Shield_Card : public Card {
private:
    int usage; ///< Number of uses for the shield

public:
    /**
     * @brief Construct a new Shield Card object
     * 
     * @param name Initial display name for the card
     * @param description Initial effect description text
     * @param rarity Starting rarity classification
     * @param mana_cost Base mana cost required to play
     * @param usage Number of uses for the shield
     */
    Shield_Card(const std::string& name, const std::string& description,
                Rarity rarity, int mana_cost, int usage);

    /**
     * @brief Get number of uses
     * @return Current number of uses
     */
    int get_usage() const;
    
    /**
     * @brief Update number of uses
     * @param new_usage Must be positive
     * @pre new_usage > 0
     * @throws std::invalid_argument if usage <= 0
     * @post new_usage == get_usage()
     */
    void set_usage(int new_usage);

    void use(Player& user, Player& target) override;
    CardType get_type() const override;
};


#endif