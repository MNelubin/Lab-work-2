/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"
#include <vector>
#include <memory>

/**
 * @brief Human-controlled player with save/load capabilities
 *
 * Inherits from Player and adds functionality specific to human players,
 * such as managing multiple characters and saving/loading game state.
 */
class Human_Player : public Player
{
    std::vector<std::unique_ptr<Character>> characters; ///< Collection of available characters

public:


    /**
     * @brief Default constructor for HumanPlayer
     *
     * Initializes the player with default values:
     * - hp: 100
     * - mana: 50
     * - armor: 0
     * - name: "Player"
     * - character: nullptr
     * - shield_amount: 0
     */
    Human_Player();


    /**
     * @brief Construct a new HumanPlayer object
     *
     * @param hp Initial health points
     * @param mana Initial mana points
     * @param armor Initial armor value
     * @param name Player's name
     * @param character Player's character (optional)
     * @param shield_amount Initial shield value (optional)
     */
    Human_Player(int hp, int mana, int armor, const std::string& name,
                 std::unique_ptr<Character> character = nullptr,
                 int shield_amount = 0);


    /**
     * @brief Check if the player is human
     *
     * @return true (always, since this is a human player)
     */
    bool is_human() const override
    {
        return true;
    }


    /**
     * @brief Add a character to the player's collection
     *
     * @param character Character to add
     */
    void add_character(std::unique_ptr<Character> character);

    /**
     * @brief Save the player's characters to a file
     *
     * @param filename Name of the file to save to
     */
    void save_characters(const std::string& filename) const;

    /**
     * @brief Load the player's characters from a file
     *
     * @param filename Name of the file to load from
     */
    void load_characters(const std::string& filename);

    /**
     * @brief Customize a character's properties
     *
     * @param character Character to customize
     */
    void customize_character(Character& character);

    /**
     * @brief Get the player's characters
     *
     * @return const std::vector<std::unique_ptr<Character>>& The player's characters
     */
    std::vector<std::unique_ptr<Character>>& get_characters();



    void show_characters() const;

    std::unique_ptr<Character> release_character();
};

#endif // HUMAN_PLAYER_H
