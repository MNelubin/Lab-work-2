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

    /**
     * @brief Display information about the special action
     * 
     * This method prints the current shield amount that the tank can add
     * to the player's shield when the special action is used.
     */
    virtual void special_action_info() override;

    /**
     * @brief Serialize the Tank_Character object to an output stream
     * 
     * This method writes the Tank_Character's data (including inherited
     * data from Character) to the provided output stream in binary format.
     * 
     * @param os The output stream to write to
     */
    void serialize(std::ostream& os) const override;

    /**
     * @brief Deserialize the Tank_Character object from an input stream
     * 
     * This method reads the Tank_Character's data (including inherited
     * data from Character) from the provided input stream in binary format.
     * 
     * @param is The input stream to read from
     */
    void deserialize(std::istream& is) override;

    /**
     * @brief Get the class name of the character
     * @return std::string The name of the character's class ("Tank")
     */
    std::string get_class_name() const override { return "Tank"; }
};

#endif // TANK_CHARACTER_H