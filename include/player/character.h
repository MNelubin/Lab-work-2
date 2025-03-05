/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <stdexcept>
class Player;

/**
 * @brief Represents a game character with progression system
 * 
 * The Character class encapsulates all attributes and behaviors related to 
 * character progression, including experience points, leveling, and 
 * combat multipliers.
 */
class Character {
private:
    int xp_to_next_lvl;   ///< Experience needed for next level. Must be > 0
    int lvl;              ///< Current character level. Must be > 0
    int xp;                ///< Current experience points. Must be >= 0
    std::string name;      ///< Character's name. Max length 50 characters
    float heal_mltpl;     ///< Healing multiplier. Must be > 0
    float dmg_mltpl;      ///< Damage multiplier. Must be > 0
    float armor_mltpl;    ///< Armor multiplier. Must be > 0
    std::string description; ///< Character description. Max length 200 characters
    int ability_uses; ///< Number of times the special ability can be used. Must be >0


public:
    /**
     * @brief Default constructor
     * 
     * Initializes character with default values:
     * - xp_to_next_lvl: 100
     * - lvl: 1
     * * - xp: 0
     * - name: ""
     * - heal_mltpl: 1.0
     * - dmg_mltpl: 1.0
     * - armor_mltpl: 1.0
     * - description: ""
     * - ability_uses: 3
     */
    Character();

    /**
     * @brief Parameterized constructor
     * @param name Character name
     * @param description Character description
     * @throws std::invalid_argument if name length > 50 or description length > 200
     */
    Character(const std::string& name, const std::string& description);

    /**
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

     * @throws std::invalid_argument if any parameter is invalid
     */
    Character(int xp_to_next_lvl, int lvl,int xp, const std::string& name, float heal_mltpl, float dmg_mltpl,
              float armor_mltpl, const std::string& description, int ability_uses
              );

    /**
     * @brief Levels up the character
     * 
     * Increases level by 1, reduces xp by xp_to_next_lvl, increases all multipliers
     * by 0.05, and multiplies xp_to_next_lvl by 1.2. If xp >= new xp_to_next_lvl,
     * recursively calls itself again.
     */
    void lvl_up();

    /**
     * @brief Get current experience points
     * @return Current xp value
     */
    int get_xp() const;

    /**
     * @brief Set experience points
     * @param value New xp value
     * @throws std::invalid_argument if value < 0
     * @post If xp >= xp_to_next_lvl, triggers lvl_up()
     */
    void set_xp(int value);

    /**
     * @brief Get character name
     * @return Current name
     */
    std::string get_name() const;

    /**
     * @brief Set character name
     * @param name New name
     * @throws std::invalid_argument if name length > 50
     */
    void set_name(const std::string& name);

    /**
     * @brief Get healing multiplier
     * @return Current healing multiplier
     */
    float get_heal_multiplier() const;

    /**
     * @brief Set healing multiplier
     * @param value New healing multiplier
     * @throws std::invalid_argument if value <= 0
     */
    void set_heal_multiplier(float value);

    /**
     * @brief Get damage multiplier
     * @return Current damage multiplier
     */
    float get_dmg_multiplier() const;

    /**
     * @brief Set damage multiplier
     * @param value New damage multiplier
     * @throws std::invalid_argument if value <= 0
     */
    void set_dmg_multiplier(float value);

    /**
     * @brief Get armor multiplier
     * @return Current armor multiplier
     */
    float get_armor_multiplier() const;

    /**
     * @brief Set armor multiplier
     * @param value New armor multiplier
     * @throws std::invalid_argument if value <= 0
     */
    void set_armor_multiplier(float value);

    /**
     * @brief Get character description
     * @return Current description
     */
    std::string get_description() const;

    /**
     * @brief Set character description
     * @param description New description
     * @throws std::invalid_argument if description length > 200
     */
    void set_description(const std::string& description);

    /**
     * @brief Get experience needed for next level
     * @return Current xp_to_next_lvl value
     */
    int get_xp_to_next_lvl() const;

    /**
     * @brief Set experience needed for next level
     * @param value New xp_to_next_lvl value
     * @throws std::invalid_argument if value <= 0
     */
    void set_xp_to_next_lvl(int value);

    /**
     * @brief Get current character level
     * @return Current level
     */
    int get_level() const;

    /**
     * @brief Set character level
     * @param value New level
     * @throws std::invalid_argument if value <= 0
     */
    void set_level(int value);

    /**
     * @brief Add experience points
     * @param amount Amount of xp to add
     * @throws std::invalid_argument if amount < 0
     * @post If xp >= xp_to_next_lvl, triggers lvl_up()
     */
    void add_xp(int amount);


    /**
     * @brief Get ability uses
     * @return Current number of ability uses
     */
    int get_ability_uses() const;

    /**
     * @brief Set ability uses
     * @param value New number of ability uses
     * @throws std::invalid_argument if value < 0
     */
    void set_ability_uses(int value);

    virtual ~Character() = default; // A virtual destructor for correctly deleting subclasses

    virtual void special_action(Player& player) = 0; // A virtual method for special actions

};

#endif // CHARACTER_H
