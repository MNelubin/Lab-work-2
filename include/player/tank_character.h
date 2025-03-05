/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef TANK_CHARACTER_H
#define TANK_CHARACTER_H

#include "character.h"


/**
 * @brief Specialized character for tanking
 * 
 * Inherits from Character and adds tank-specific properties.
 */
class Tank_Character : public Character {
private:
    
    int shield_add; ///< Amount of shield provided by the ability
    bool was_ability_used; ///< Tracks if the ability has been used

public:
    /**
     * @brief Default constructor
     * 
     * Initializes tank with default values:
     * - shield_add: 2
     * - was_ability_used: false
     */
    Tank_Character();

    /**
     * @brief Parameterized constructor
     * @param xp_to_next_lvl Experience needed for next level
     * @param lvl Current character level
     * @param xp Initial experience points
     * @param name Character name
     * @param heal_mltpl Healing multiplier
     * @param dmg_mltpl Damage multiplier
     * @param armor_mltpl Armor multiplier
     * @param description Character description
     * @param ability_uses Number of ability uses possible
     * @param shiled_add Number of plus shields
     * 
     * @throws std::invalid_argument if shield_add <= 0
     */
    Tank_Character( int xp_to_next_lvl, int lvl, int xp, 
                   const std::string& name, float heal_mltpl, float dmg_mltpl,
                   float armor_mltpl, const std::string& description, 
                   int ability_uses,int shield_add);

    /**
     * @brief Get shield add
     * @return Current shield add
     */
    int get_shield_add() const;

    /**
     * @brief Set shield add
     * @param value New shield add
     * @throws std::invalid_argument if value <= 0
     */
    void set_shield_add(int value);

    /**
     * @brief Perform the special tanking action
     * @param player Player to apply the shield to
     * 
     * @throws std::runtime_error if ability_uses is 0
     */
    virtual void special_action(Player& player) override;
};

#endif // TANK_CHARACTER_H