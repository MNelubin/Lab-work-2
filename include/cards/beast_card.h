/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef BEAST_CARD_H
#define BEAST_CARD_H

#include "card.h"
#include "enums.h"

/**
 * @brief Specialized card for beast creatures
 * 
 * Inherits from Card and adds beast-specific properties.
 */
class Beast_Card : public Card {
private:
    int base_dmg; ///< Base damage value
    Tribe tribe; ///< Tribe type of the beast

public:
    /**
     * @brief Construct a new Beast Card object
     * 
     * @param name Initial display name for the card
     * @param description Initial effect description text
     * @param rarity Starting rarity classification
     * @param mana_cost Base mana cost required to play
     * @param base_dmg Base damage value
     * @param tribe Tribe type of the beast
     */
    Beast_Card(const std::string& name, const std::string& description,
               Rarity rarity, int mana_cost, int base_dmg, Tribe tribe);

    /**
     * @brief Default constructor
     * 
     * Initializes card with default values:
     * - name: "Unnamed Beast"
     * - description: "No description"
     * - rarity: Rarity::Common
     * - mana_cost: 0
     * - base_dmg: 3
     * - tribe: Tribe::North
     */
    Beast_Card();

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
     * @brief Get tribe type
     * @return Current tribe type
     */
    Tribe get_tribe() const;

    /**
     * @brief Update tribe type
     * @param new_tribe New tribe type to assign
     * @post new_tribe == get_tribe()
     */
    void set_tribe(Tribe new_tribe);

    void use(Player& user, Player& target) override;
    
    CardType get_type() const override;

    void generate_properties() override;

    void print_key_info() const override;
};

#endif 