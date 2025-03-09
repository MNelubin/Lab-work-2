/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef HEAL_SPELL_CARD_H
#define HEAL_SPELL_CARD_H

#include "spell_card.h"
#include <iostream>

/**
 * @brief Specialized spell for heal
 * 
 * Inherits from Spell_Card and adds heal mechanics.
 */
class Heal_Spell_Card : public Spell_Card {
private:
    int base_heal; ///< Base heal value without modifiers
    float efficiency_deg; ///< Modifier of healing, corr. with rarity

public:
    /**
     * @brief Construct a new Heal Spell Card object
     * 
     * @param[in] name Initial display name for the card
     * @param[in] description Initial effect description text
     * @param[in] rarity Starting rarity classification
     * @param[in] mana_cost Base mana cost required to play
     * @param[in] elem Associated element
     * @param[in] heal Base heal value
     * @param[in] eff Efficiency of heal
     */
    Heal_Spell_Card(const std::string& name, const std::string& description,
                     Rarity rarity, int mana_cost, Element elem, int heal, float eff);
    
    /**
     * @brief Default constructor
     * 
     * Initializes card with default values:
     * - name: "Unnamed Heal Spell"
     * - description: "No description"
     * - rarity: Rarity::Common
     * - mana_cost: 0
     * - element: Element::Water
     * - base_heal: 5
     * - efficiency_deg: 1.0f
     */
    Heal_Spell_Card();
    
    /**
     * @brief Get base heal value
     * @return Current base heal
     */
    int get_base_heal() const;
    
    /**
     * @brief Update heal value
     * @param[in] new_heal Must be positive
     * @pre new_heal > 0
     * @post get_base_heal()==new_heal
     * @throws std::invalid_argument if heal <=0
     */
    void set_base_heal(int new_heal);

        /**
     * @brief Get efficiency value
     * @return Current efficiency
     */
    float get_eff() const;
    
    /**
     * @brief Update efficiency value
     * @param[in] new_eff Must be positive
     * @pre new_eff > 0
     * @post get_eff()==new_eff
     * @throws std::invalid_argument if eff <=0
     */
    void set_eff(float new_eff);

    void use(Player& user, Player& target) override;

    CardType get_type() const override;

    void generate_properties() override;

    void print_key_info() const override;

};

#endif 