/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef ENUMS_H
#define ENUMS_H

/**
 * @brief Defines card rarity classifications
 * 
 * Determines drop probability and crafting cost.
 * Ordered from most common to rarest.
 */
enum class Rarity {
    Common,     ///< Basic quality
    Uncommon,   ///< Not common rarity
    Rare,       ///< Powerful effects, limited quantity
    Epic        ///< Legendary status, extremely rare
};

/**
 * @brief Elemental affinity types
 * 
 * Defines card's magical alignment
 * Now contains placeholders as descriptions
 */
enum class Element {
    Fire,       ///< Just fire
    Water,      ///< Just water
    Earth,      ///< Just dirt
    Air         ///< just oxygen
};

/**
 * @brief Geographic faction classifications
 * 
 * Determines faction alliances.
 * Affects gameplay mechanics.
 */
enum class Tribe {
    North,      ///< Northern realms
    East,       ///< Eastern empires
    West,       ///< Western alliance
    South       ///< Southern tribes
};

#endif