/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <stdexcept>

#include "hand.h"

class Character;


/**
 * @brief Base class representing a game player
 * 
 * Provides common interface and data for all player types
 */
class Player {
protected:
    std::unique_ptr<Character> character; ///< The player's character
    int hp; ///< Health points
    int mana; ///< Mana points
    int armor; ///< Armor value
    std::string name; ///< Player's name
    Hand hand; ///< Player's hand of cards
    int shield_amount; ///< Shield value
    float cumulative_attack_multiplier; ///< Cumulative attack multiplier
    float cumulative_heal_multiplier; ///< Cumulative heal multiplier
    int cumulative_weapon_adder; ///< Cumulative weapon bonus
    bool turn_active; ///< Indicates if it's the player's turn

public:

     /**
     * @brief Default constructor
     * 
     * Initializes player with default values:
     * - hp: 100
     * - mana: 50
     * - armor: 0
     * - name: "Player"
     * - character: nullptr
     * - shield_amount: 0
     * - cumulative_attack_multiplier: 1.0f
     * - cumulative_heal_multiplier: 1.0f
     * - cumulative_weapon_adder: 0
     * - turn_active: true
     */
    Player();


    /**
     * @brief Construct a new Player object
     * 
     * @param hp Initial health points
     * @param mana Initial mana points
     * @param armor Initial armor value
     * @param name Player's name
     * @param character Player's character (optional)
     * @param shield_amount Initial shield value (optional)
     */
    Player(int hp, int mana, int armor, const std::string& name,
          std::unique_ptr<Character> character = nullptr,
          int shield_amount = 0);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Player() = default;


    /**
     * @brief Check if the player is human
     * 
     * @return true if the player is human, false otherwise
     */
    virtual bool is_human() const = 0;


   

    /**
     * @brief Set the associated Character
     * @param new_character New Character to associate (can be nullptr)
     * 
     * @throws std::invalid_argument if new_character is invalid
     */
    void set_character(std::unique_ptr<Character>&& new_character);

    /**
     * @brief Get the associated Character
     * @return Reference to the owned Character
     * 
     * @throws std::runtime_error if Character is not set
     */
    Character& get_character() const;

    /**
     * @brief Perform the special action of the associated Character
     * 
     * Calls the SpecialAction method of the associated Character
     * 
     * @throws std::runtime_error if Character is not set
     */
    void perform_special_action();



    void get_special_action_info();

    /**
     * @brief Displays the player's hand with detailed information and special ability status
     * 
     * This enhanced method:
     * 1. Shows a colored header for the hand section
     * 2. Displays information about the character's special ability including remaining uses
     * 3. Lists all cards in hand with:
     *    - Index
     *    - Colored name based on rarity
     *    - Mana cost
     *    - Type (colored red for combat cards)
     *    - Key card-specific information
     * 4. Adds a colored footer for visual separation
     * 
     * The display uses ANSI color codes for better visual distinction:
     * - Hand header: Cyan (\033[36m)
     * - Ability info: Yellow (\033[33m)
     * - Combat card types: Red (\033[31m)
     * - Normal card types: White (\033[37m)
     *
     * @see get_color_code()
     * @see cardTypeToString()
     * @see print_key_info()
     */
    void show_hand();

    /**
     * @brief Eats a card from the hand, increasing player's HP based on card's rarity and character's HP multiplier.
     * 
     * This method:
     * 1. Validates the card index
     * 2. Gets the card's rarity and converts it to a numerical value (Common=1, Uncommon=2, Rare=3, Epic=4)
     * 3. Retrieves the character's HP multiplier
     * 4. Calculates the HP increase as (rarity value * 10) multiplied by the HP multiplier
     * 5. Converts the result to integer and adds it to player's HP
     * 6. Removes the card from the hand
     * 
     * @param index Position of the card to eat
     * 
     * @throws std::out_of_range If the card index is invalid
     * @throws std::runtime_error If the character is not set
     */
    void eat_card(int index);

    /**
     * @brief Uses a card from the player's hand on a target player with mana cost deduction.
     * 
     * This method performs the following actions:
     * 1. Validates the card index
     * 2. Checks if the player has sufficient mana
     * 3. Deducts mana from the player
     * 4. Retrieves the card's type
     * 5. Applies the card's effect to the target player
     * 6. Removes the card from the player's hand
     * 7. Checks if the card type ends the player's turn (Combat cards)
     * 
     * @param target Player to apply the card effect to
     * @param index Index of the card in the player's hand
     * 
     * @throws std::out_of_range If the card index is invalid
     * @throws std::runtime_error If the player doesn't have enough mana
     */
    void use_card( int index, Player& target);

    /**
     * @brief Applies damage to the player, reducing shields, armor, and HP in that order.
     * 
     * This method processes damage in the following order:
     * 1. Shields absorb damage up to their maximum capacity (each shield can absorb up to 10 damage)
     * 2. Remaining damage is absorbed by armor (1 damage reduces armor by 1)
     * 3. Any remaining damage is subtracted from HP
     * 
     * @param damage Amount of damage to apply
     * 
     * @throws std::invalid_argument If damage is negative
     */
    void take_damage(int amount);

    /**
     * @brief Throw out a card from the hand
     * @param index Position of the card to throw out
     * 
     * @throws std::out_of_range if index is invalid
     */
    void throw_out(int index);

    /**
     * @brief Get current health points
     * @return Current hp value
     */
    int get_hp() const;

    /**
     * @brief Set health points
     * @param value New hp value
     * @throws std::invalid_argument if value < 0
     */
    void set_hp(int value);

    /**
     * @brief Get current mana points
     * @return Current mana value
     */
    int get_mana() const;

    /**
     * @brief Set mana points
     * @param value New mana value
     * @throws std::invalid_argument if value < 0
     */
    void set_mana(int value);

    /**
     * @brief Get current armor points
     * @return Current armor value
     */
    int get_armor() const;

    /**
     * @brief Set armor points
     * @param value New armor value
     * @throws std::invalid_argument if value < 0
     */
    void set_armor(int value);

    /**
     * @brief Get player's name
     * @return Current name
     */
    std::string get_name() const;

    /**
     * @brief Set player's name
     * @param name New name
     * @throws std::invalid_argument if name is empty
     */
    void set_name(const std::string& name);

    /**
     * @brief Get the number of shields
     * @return Current shield amount
     */
    int get_shield_amount() const;

    /**
     * @brief Set the number of shields
     * @param value New shield amount
     * @throws std::invalid_argument if value < 0
     */
    void set_shield_amount(int value);

    /**
     * @brief Get all character statistics as a string
     * @return String containing all character fields
     * 
     * @throws std::runtime_error if Character is not set
     */
    std::string get_character_statistics() const;

    /**
     * @brief Resets the stroke parameters to their initial values
     * @details Initializes attack and healing multipliers, activates the turn.
     * @post 
     * - cumulative_attack_multiplier = 1.0f
     * - cumulative_heal_multiplier = 1.0f
     * - cumulative_weapon_adder = 0
     * - turn_active = true
     */
    void reset_turn();

    /**
     * @brief Applies multiplier to total attack power
     * @param effect Effect multiplier (must be > 0)
     * @note Multipliers are combined multiplicatively with each other
     * @warning Incorrect values (<=0) may lead to unexpected behavior
     */
    void apply_attack_multiplier(float effect);

    /**
     * @brief Applies a multiplier to treatment effectiveness
     * @param effect Effect multiplier (must be > 0)
     * @note Multipliers are combined multiplicatively with each other
     * @warning Incorrect values (<=0) may lead to calculation errors
     */
    void apply_heal_multiplier(float effect);

    /**
     * @brief Adds a bonus to weapon damage effectiveness
     * @param effect Bonus value to add
     * @note Bonuses are combined additively with each other
     */
    void add_weapon_bonus(int effect);

    /**
     * @brief Completes the current turn and resets the temporary modifiers
     * @details Performs the same actions as reset_turn()
     * @see reset_turn()
     */
    void end_turn();

    /**
     * @brief Get the cumulative attack multiplier
     * @return Current attack multiplier value
     */
    float get_cumulative_attack_multiplier() const;

    /**
     * @brief Set the cumulative attack multiplier
     * @param value New attack multiplier value
     * @throws std::invalid_argument if value <= 0
     */
    void set_cumulative_attack_multiplier(float value);

    /**
     * @brief Get the cumulative heal multiplier
     * @return Current heal multiplier value
     */
    float get_cumulative_heal_multiplier() const;

    /**
     * @brief Set the cumulative heal multiplier
     * @param value New heal multiplier value
     * @throws std::invalid_argument if value <= 0
     */
    void set_cumulative_heal_multiplier(float value);

    /**
     * @brief Get the cumulative weapon bonus
     * @return Current weapon bonus value
     */
    int get_cumulative_weapon_bonus() const;

    /**
     * @brief Set the cumulative weapon bonus
     * @param value New weapon bonus value
     */
    void set_cumulative_weapon_bonus(int value);

    /**
     * @brief Check if the turn is active
     * @return true if turn is active, false otherwise
     */
    bool is_turn_active() const;

    /**
     * @brief Set the turn active state
     * @param value New turn active state
     */
    void set_turn_active(bool value);

    /**
     * @brief Get the player's hand
     * @return Reference to the player's hand
     */
    Hand& get_hand();

    /**
     * @brief Get the player's hand (const version)
     * @return Const reference to the player's hand
     */
    const Hand& get_hand() const;

    /**
     * @brief Set the player's hand
     * @param new_hand New hand to set
     */
    void set_hand(Hand new_hand);

    /**
     * @brief Check if the hand contains any Beast, Creature, or AttackSpell cards
     * @return true if any of the specified card types are found, false otherwise
     */
    bool has_combat_cards() const;

    /**
     * @brief Get the ANSI color code for a given rarity
     * 
     * This method returns the ANSI escape code for the color associated with the card's rarity.
     * The color codes are as follows:
     * - Common: White (\033[37m)
     * - Uncommon: Green (\033[32m)
     * - Rare: Blue (\033[34m)
     * - Epic: Magenta (\033[35m)
     * 
     * @param rarity The rarity of the card
     * @return ANSI color code as a string
     */
    std::string get_color_code(Rarity rarity);



};

#endif // PLAYER_H