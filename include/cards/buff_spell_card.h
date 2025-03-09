/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef BUFF_SPELL_CARD_H
#define BUFF_SPELL_CARD_H

#include "spell_card.h"

/**
 * @brief Specialized spell for buffing characters
 * 
 * Inherits from Spell_Card and adds a multiplier mechanic.
 */
class Buff_Spell_Card : public Spell_Card {
private:
    float multiplier; ///< Multiplier value for the buff

public:
    /**
     * @brief Construct a new Buff Spell Card object
     * 
     * @param name Initial display name for the card
     * @param description Initial effect description text
     * @param rarity Starting rarity classification
     * @param mana_cost Base mana cost required to play
     * @param elem Associated element
     * @param multiplier Buff multiplier value
     */
    Buff_Spell_Card(const std::string& name, const std::string& description,
                 Rarity rarity, int mana_cost, Element elem, 
                 float multiplier);

    /**
     * @brief Get buff multiplier value
     * @return Current buff multiplier
     */
    float get_multiplier() const;
    
    /**
     * @brief Update buff multiplier value
     * @param new_multiplier Must be positive
     * @pre new_multiplier>0 
     * @throws std::invalid_argument if multiplier <= 0
     * @post new_multipier==get_multiplier()
     */
    void set_multiplier(float new_multiplier);

    void use(Player& user, Player& target) override;

    CardType get_type() const override;

    void generate_properties() override;

    void print_key_info() const override;
};

#endif
