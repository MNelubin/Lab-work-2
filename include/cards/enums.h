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

/**
 * @brief Converts CardType enum to string representation
 * 
 * @param type CardType value
 * @return std::string Textual representation of the card type
 */
inline std::string cardTypeToString(CardType type) {
    switch (type) {
        case CardType::Beast:        return "Beast";
        case CardType::Buff:         return "Buff";
        case CardType::Creature:     return "Creature";
        case CardType::Shield:       return "Shield";
        case CardType::Weapon:       return "Weapon";
        case CardType::Artifact:     return "Artifact";
        case CardType::AttackSpell:  return "Attack Spell";
        case CardType::HealSpell:    return "Heal Spell";
        case CardType::BuffSpell:    return "Buff Spell";
        case CardType::DefenceSpell: return "Defence Spell";
        default:                     return "Unknown";
    }
}

/**
 * @brief Converts a Tribe enum value to its string representation
 * 
 * This function takes a Tribe enum value and returns the corresponding
 * string representation. It is useful for displaying tribe information
 * in a human-readable format.
 * 
 * @param tribe The Tribe enum value to convert
 * @return std::string The string representation of the tribe
 */
inline std::string tribeToString(Tribe tribe) {
    switch (tribe) {
        case Tribe::North:
            return "North";
        case Tribe::East:
            return "East";
        case Tribe::West:
            return "West";
        case Tribe::South:
            return "South";
        default:
            return "Unknown Tribe";
    }
}
#endif