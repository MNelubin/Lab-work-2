/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef CARD_CLASS
#define CARD_CLASS

#include <string>
/// @file enums.h
#include "enums.h"

/**
 * @brief Base class representing a game card
 * 
 * Provides basic card properties and manipulation methods.
 * All specific card types should inherit from this class.
 */
class Card {
protected:
    std::string name;        ///< Display name of the card
    std::string description; ///< Flavor text and effect description
    Rarity rarity;           ///< Rarity category from enum
    int mana_cost;           ///< Required mana to play

public:
    /**
     * @brief Construct a new Card object with specified parameters
     * 
     * @param[in] name Initial display name for the card
     * @param[in] description Initial effect description text
     * @param[in] rarity Starting rarity classification
     * @param[in] mana_cost Base mana cost required to play
     */
    Card(const std::string& name, const std::string& description, 
         Rarity rarity, int mana_cost);
    
    /**
     * @brief Virtual destructor for proper polymorphic deletion
     */
    virtual ~Card() = default;

    /**
     * @brief Retrieves current card name
     * @return const reference to card's name string
     */
    std::string get_name() const;
    
    /**
     * @brief Updates card's display name
     * @param[in] new_name New name to assign
     * @post get_name() == new_name
     */
    void set_name(const std::string& new_name);

    /**
     * @brief Gets current effect description
     * @return Full description text as string
     */
    std::string get_description() const;

    /**
     * @brief Modifies card's effect description
     * @param[in] new_desc New description text
     * @post get_description() == new_desc
     */
    void set_description(const std::string& new_desc);

    /**
     * @brief Retrieves current rarity classification
     * @return Rarity enum value
     */
    Rarity get_rarity() const;

    /**
     * @brief Changes card's rarity category
     * @param[in] new_rarity New rarity to assign
     * @post get_rarity() == new_rarity
     */
    void set_rarity(Rarity new_rarity);

    /**
     * @brief Gets current mana cost value
     * @return Integer representing required mana
     */
    int get_mana_cost() const;

    /**
     * @brief Updates mana cost requirement
     * @param[in] new_cost New mana cost value
     * @pre new_cost >= 0
     * @post get_mana_cost() == new_cost
     */
    void set_mana_cost(int new_cost);
};

#endif