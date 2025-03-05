/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef HEALER_CHARACTER_H
#define HEALER_CHARACTER_H

#include "character.h"


/**
 * @brief Specialized character for healing
 * 
 * Inherits from Character and adds healing-specific properties.
 */
class Healer_Character : public Character {
private:
    int heal_amount; ///< Amount of HP restored per heal
    

public:
    /**
     * @brief Default constructor
     * 
     * Initializes healer with default values:
     * - heal_amount: 10
     */
    Healer_Character();




    Healer_Character(const std::string& name, const std::string& description);

    /**
     * @brief Parameterized constructor
     * @brief Constructor with all fields
     * @param xp_to_next_lvl Experience needed for next level
     * @param lvl Current character level
     * @param xp Initial experience points
     * @param name Character name
     * @param heal_mltpl Healing multiplier
     * @param dmg_mltpl Damage multiplier
     * @param armor_mltpl Armor multiplier
     * @param description Character description
     * @param ability_uses Number of ability uses possible
     * @param heal_amount Initial heal amount
     * 
     * @throws std::invalid_argument if heal_amount <= 0 
     */
    Healer_Character(int heal_amount,int xp_to_next_lvl, int lvl, int xp, const std::string& name, float heal_mltpl, float dmg_mltpl,
                     float armor_mltpl, const std::string& description, int ability_uses
                     );
    
    Healer_Character(int xp_to_next_lvl, int lvl, int xp, const std::string& name, float heal_mltpl, float dmg_mltpl,
                     float armor_mltpl, const std::string& description, int ability_uses
                     );

    /**
     * @brief Get heal amount
     * @return Current heal amount
     */
    int get_heal_amount() const;

    /**
     * @brief Set heal amount
     * @param value New heal amount
     * @throws std::invalid_argument if value <= 0
     */
    void set_heal_amount(int value);

    /**
     * @brief Perform the special healing action
     * @param player Player to heal
     * 
     * @throws std::runtime_error if ability_uses is 0
     */
    virtual void special_action(Player& player) override;
};

#endif // HEALER_CHARACTER_H