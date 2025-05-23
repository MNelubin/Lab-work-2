/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef KNIGHT_CHARACTER_H
#define KNIGHT_CHARACTER_H

#include "character.h"


/**
 * @brief Specialized character for knight abilities
 *
 * Inherits from Character and adds knight-specific properties.
 */
class Knight_Character : public Character
{
private:
    int armor_up; ///< Base armor amount provided by the ability
    int armored_amount; ///< Amount of armor already applied

public:
    /**
     * @brief Default constructor
     *
     * Initializes knight with default values:
     * - armor_up: 5
     * - armored_amount: 0
     */
    Knight_Character();

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
     * @param armor_up Base armor amount provided by the ability
     * @param armored_amount Amount of uses already applied
     *
     * @throws std::invalid_argument if armor_up < 0 or armored_amount < 0
     */
    Knight_Character(int xp_to_next_lvl, int lvl, int xp,
                     const std::string& name, float heal_mltpl, float dmg_mltpl,
                     float armor_mltpl, const std::string& description,
                     int ability_uses, int armor_up, int armored_amount);

    /**
     * @brief Get armor up amount
     * @return Current armor up amount
     */
    int get_armor_up() const;

    /**
     * @brief Set armor up amount
     * @param value New armor up amount
     * @throws std::invalid_argument if value < 0
     */
    void set_armor_up(int value);

    /**
     * @brief Get armored amount
     * @return Current armored amount
     */
    int get_armored_amount() const;

    /**
     * @brief Set armored amount
     * @param value New armored amount
     * @throws std::invalid_argument if value < 0
     */
    void set_armored_amount(int value);

    /**
     * @brief Perform the special knight action
     * @param player Player to apply the armor to
     *
     * @throws std::runtime_error if ability_uses is 0
     */
    virtual void special_action(Player& player) override;

    /**
     * @brief Display information about the special action
     *
     * This method prints the current armor up amount, taking into account
     * the already applied armor (armored_amount).
     */
    virtual void special_action_info() override;

    /**
     * @brief Serialize the Knight_Character object to an output stream
     *
     * This method writes the Knight_Character's data (including inherited
     * data from Character) to the provided output stream in binary format.
     *
     * @param os The output stream to write to
     */
    void serialize(std::ostream& os) const override;

    /**
     * @brief Deserialize the Knight_Character object from an input stream
     *
     * This method reads the Knight_Character's data (including inherited
     * data from Character) from the provided input stream in binary format.
     *
     * @param is The input stream to read from
     */
    void deserialize(std::istream& is) override;

    /**
     * @brief Get the class name of the character
     * @return std::string The name of the character's class ("Knight")
     */
    std::string get_class_name() const override
    {
        return "Knight";
    }
};

#endif // KNIGHT_CHARACTER_H