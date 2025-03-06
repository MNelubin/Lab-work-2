/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef ENUMS_H
#define ENUMS_H

/**
 * @enum Rarity
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
 * @enum Element
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
 * @enum Tribe
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
// enums.h
/**
 * @brief Card type enumeration
 */
enum class CardType {
    Beast,        ///< Cards representing creatures
    Buff,         ///< Cards providing temporary bonuses
    Creature,     ///< Cards that summon creatures
    Shield,       ///< Cards providing protection
    Weapon,       ///< Cards enhancing attack power
    Artifact,     ///< Cards with global effects
    AttackSpell,  ///< Damage-dealing spell cards
    HealSpell,    ///< Healing spell cards
    BuffSpell,    ///< Temporary buff spell cards
    DefenceSpell  ///< Defensive spell cards
};
#endif