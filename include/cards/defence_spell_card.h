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
class Defence_Spell_Card : public Spell_Card
{
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
    Defence_Spell_Card(const std::string& name, const std::string& description,
                       Rarity rarity, int mana_cost, Element elem,
                       int base_def);

    /**
     * @brief Construct a new Defence Spell Card object
     *
     * @param name Display name of the card
     * @param description Flavor text and effect description
     * @param rarity Rarity category from enum
     * @param mana_cost Required mana to play
     * @param elem Element type of the spell (from enum ElementType)
     */
    Defence_Spell_Card(const std::string& name, const std::string& description,
                       Rarity rarity, int mana_cost, Element elem);

    /**
     * @brief Default constructor
     *
     * Initializes card with default values:
     * - name: "Unnamed Defence Spell"
     * - description: "No description"
     * - rarity: Rarity::Common
     * - mana_cost: 0
     * - element: Element::Earth
     * - base_def: 2
     */
    Defence_Spell_Card();

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

    void use(Player& user, Player& target) override;

    CardType get_type() const override;

    void generate_properties() override;

    void print_key_info() const override;
};

#endif