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
 * @brief Represents a player in the game with associated character and attributes
 * 
 * The Player class encapsulates all attributes and behaviors related to a game player,
 * including health points, mana, armor, and an associated character with special abilities.
 */
class Player {
private:
    std::unique_ptr<Character> character; ///< Unique pointer to the associated Character
    int hp; ///< Current health points of the player
    int mana; ///< Current mana points of the player
    int armor; ///< Current armor points of the player
    std::string name; ///< Name of the player
    Hand hand; ///< Player's hand of cards
    int shield_amount; ///< Number of shields available

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
     */
    Player();

    /**
     * @brief Parameterized constructor
     * @param hp Initial health points
     * @param mana Initial mana points
     * @param armor Initial armor points
     * @param name Player's name
     * @param character Initial Character (can be nullptr)
     * @param shield_amount Initial number of shields
     * 
     * @throws std::invalid_argument if hp, mana, or armor are negative
     */
    Player(int hp, int mana, int armor, const std::string& name, 
       std::unique_ptr<Character> character = nullptr, int shield_amount = 0);

    /**
     * @brief Copy constructor (deleted due to unique_ptr)
     */
    Player(const Player&) = delete;

    /**
     * @brief Move constructor
     */
    Player(Player&& other) noexcept;

    /**
     * @brief Copy assignment operator (deleted due to unique_ptr)
     */
    Player& operator=(const Player&) = delete;

    /**
     * @brief Move assignment operator
     */
    Player& operator=(Player&& other) noexcept;

    /**
     * @brief Destructor
     * 
     * Properly releases the owned Character
     */
    ~Player();

    /**
     * @brief Set the associated Character
     * @param new_character New Character to associate (can be nullptr)
     * 
     * @throws std::invalid_argument if new_character is invalid
     */
    void set_character(std::unique_ptr<Character> new_character);

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

    /**
     * @brief Show the player's hand
     */
    void show_hand();

    /**
     * @brief Eat a card from the hand
     * @param index Position of the card to eat
     * 
     * @throws std::out_of_range if index is invalid
     */
    void eat_card(int index);

    /**
     * @brief Use a card on a target player
     * @param target Player to use the card on
     * @param index Position of the card to use
     * 
     * @throws std::out_of_range if index is invalid
     */
    void use_card(Player& target, int index);

    /**
     * @brief Apply damage to the player
     * @param amount Damage to apply
     * 
     * @throws std::invalid_argument if amount is negative
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
};

#endif // PLAYER_H