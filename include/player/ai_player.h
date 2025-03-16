#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "player.h"
#include <utility> 

/**
 * @brief AI-controlled player with decision logic
 * 
 * Inherits from Player and implements AI-specific behavior,
 * such as automatic card selection and turn execution.
 */
class AI_Player : public Player {
public:
    /**
     * @brief Inherit constructors from Player
     */
    using Player::Player;

    // Player interface

    /**
     * @brief Check if the player is human
     * 
     * @return false (always, since this is an AI player)
     */
    bool is_human() const override { return false; }



    /**
     * @brief Find the best combination of cards to play
     * 
     * @return std::pair<int, int> Indices of the best main and secondary cards
     */
    std::pair<int, int> find_best_combination() const;

private:
    /**
     * @brief Structure for storing card information
     */
    struct CardScore {
        int index; ///< Index of the card in the hand
        int value; ///< Calculated value of the card
        int mana_cost; ///< Mana cost of the card
        CardType type; ///< Type of the card
    };

    /**
     * @brief Calculate the value of a card based on its type and effects
     * 
     * @param card The card to evaluate
     * @return int The calculated value
     */
    int calculate_card_value(const Card& card) const;

    
};

#endif // AI_PLAYER_H 