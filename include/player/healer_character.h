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


    /**
     * @brief Display information about the special action
     * 
     * This method prints the current heal amount that the healer can restore
     * to the player's health when the special action is used.
     */
    virtual void special_action_info() override;

    /**
     * @brief Serialize the Healer_Character object to an output stream
     * 
     * This method writes the Healer_Character's data (including inherited
     * data from Character) to the provided output stream in binary format.
     * 
     * @param os The output stream to write to
     */
    void serialize(std::ostream& os) const override;

    /**
     * @brief Deserialize the Healer_Character object from an input stream
     * 
     * This method reads the Healer_Character's data (including inherited
     * data from Character) from the provided input stream in binary format.
     * 
     * @param is The input stream to read from
     */
    void deserialize(std::istream& is) override;

    /**
     * @brief Get the class name of the character
     * @return std::string The name of the character's class ("Healer")
     */
    std::string get_class_name() const override { return "Healer"; }
};

#endif // HEALER_CHARACTER_H