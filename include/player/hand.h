/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef HAND_H
#define HAND_H

#include <vector>
#include <memory>
#include <algorithm>
#include "../cards/card.h"

/**
 * @brief Represents a player's hand containing various types of cards
 * 
 * The Hand class manages a collection of polymorphic Card objects,
 * allowing for various operations like adding, removing, and sorting cards.
 */
class Hand {
private:
    std::vector<std::unique_ptr<Card>> cards; ///< Collection of cards in hand
    int amount; ///< Current number of cards in hand

    // Predefined standard hands
    void create_standard_hand_1();
    void create_standard_hand_2();
    void create_standard_hand_3();

public:
    /**
     * @brief Construct a new Hand object
     */
    Hand();

    /**
     * @brief Add a card to the hand
     * @param card Unique pointer to the card to add
     */
    void add_card(std::unique_ptr<Card> card);

    /**
     * @brief Remove a card from the hand by index
     * @param index Position of the card to remove
     * @throws std::out_of_range if index is invalid
     */
    void remove_card(int index);

    /**
     * @brief Get a reference to a card by index
     * @param index Position of the card to retrieve
     * @return Reference to the card
     * @throws std::out_of_range if index is invalid
     */
    Card& get_card(int index) const;

    /**
     * @brief Sort cards in hand by mana cost (un ascending)
     */
    void sort_by_mana();

    /**
     * @brief Generate a predefined standard hand
     * @param id Identifier of the standard hand (1-3)
     * @throws std::invalid_argument if id is invalid
     */
    void generate(int id);

    /**
     * @brief Get the number of cards in hand
     * @return Current card count
     */
    int get_amount() const;

    /**
     * @brief Get all unique card types present in hand
     * @return Vector of unique card type names
     */
    std::vector<std::string> get_unique_card_types() const;

    /**
     * @brief Get all cards of a specific type
     * @param type_name Name of the card type to filter by
     * @return Vector of references to matching cards
     */
    std::vector<std::reference_wrapper<Card>> get_cards_by_type(const std::string& type_name) const;
};

#endif
