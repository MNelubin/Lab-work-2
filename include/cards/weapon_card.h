/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef WEAPON_CARD_H
#define WEAPON_CARD_H

#include "card.h"

/**
 * @brief Specialized card for weapons
 * 
 * Inherits from Card and adds weapon-specific properties.
 */
class Weapon_Card : public Card {
private:
    int dmg_up; ///< Damage increase value

public:
    /**
     * @brief Construct a new Weapon Card object
     * 
     * @param name Display name of the card
     * @param description Flavor text and effect description
     * @param rarity Rarity category from enum
     * @param mana_cost Required mana to play
     */
    Weapon_Card(const std::string& name, const std::string& description,
                         Rarity rarity, int mana_cost);

    /**
     * @brief Construct a new Weapon Card object
     * 
     * @param name Initial display name for the card
     * @param description Initial effect description text
     * @param rarity Starting rarity classification
     * @param mana_cost Base mana cost required to play
     * @param dmg_up Damage increase value
     */
    Weapon_Card(const std::string& name, const std::string& description,
                Rarity rarity, int mana_cost, int dmg_up);

    /**
     * @brief Default constructor
     * 
     * Initializes card with default values:
     * - name: "Unnamed Weapon"
     * - description: "No description"
     * - rarity: Rarity::Common
     * - mana_cost: 0
     * - dmg_up: 2
     */
    Weapon_Card();

    /**
     * @brief Get damage increase value
     * @return Current damage increase
     */
    int get_dmg_up() const;
    
    /**
     * @brief Update damage increase value
     * @param new_dmg_up Must be positive
     * @pre new_dmg_up > 0
     * @throws std::invalid_argument if dmg_up <= 0
     * @post new_dmg_up == get_dmg_up()
     */
    void set_dmg_up(int new_dmg_up);

    void use(Player& user, Player& target) override;

    CardType get_type() const override;

    void generate_properties() override;

    void print_key_info() const override;
};

#endif 