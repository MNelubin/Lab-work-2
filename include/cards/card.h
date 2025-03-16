/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef CARD_CLASS
#define CARD_CLASS

#include <cstdlib>
#include <ctime>
#include <string>
#include <memory>
#include <random>
#include <iostream>
/// @file enums.h
#include "enums.h"

class Player;


// Seed the random number generator
extern std::mt19937 rng;


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
     * @brief Default constructor
     * 
     * Initializes card with default values:
     * - name: "Unnamed Card"
     * - description: "No description"
     * - rarity: Rarity::Common
     * - mana_cost: 0
     */
    Card();



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


    /**
     * @brief Apply card effect to target
     * @param user Player using the card
     * @param target Player affected by the card
     */
    virtual void use(Player& user, Player& target) = 0;
    
    /**
     * @brief Get card type
     * @return CardType identifier
     */
    virtual CardType get_type() const = 0;

    /**
     * @brief Generates random properties based on card's rarity
     */
    virtual void generate_properties() = 0;

    /**
     * @brief Generates a random rarity based on predefined probabilities
     * @return Randomly selected rarity
     */
    Rarity generate_random_rarity();

    virtual void print_key_info() const = 0;
};




// Arrays of possible names, descriptions, and elements
const std::vector<std::string> spell_names = {
    "Arcane Bolt", "Mystic Strike", "Enchanted Blast", "Cosmic Beam",
    "Ethereal Wave", "Nether Bolt", "Celestial Arrow", "Void Shockwave",
    "Plasma Surge", "Thunderclap", "Frostbite", "Inferno Blast",
    "Tidal Wave", "Earthquake", "Wind Cutter", "Lightning Fury",
    "Solar Flare", "Lunar Beam", "Astral Projection", "Shadow Bolt"
};

const std::vector<std::string> spell_descriptions = {
    "Deals magical damage to the enemy", "Unleashes arcane energy",
    "Summons a powerful blast", "Releases contained magical energy",
    "Calls down celestial power", "Harnesses elemental forces",
    "Channels raw magical power", "Inflicts mystical damage",
    "Unleashes a wave of energy", "Summons ancient magical forces",
    "Releases contained magical energy", "Harnesses elemental forces",
    "Channels raw magical power", "Inflicts mystical damage",
    "Unleashes a wave of energy", "Summons ancient magical forces"
};


const std::vector<std::string> beast_names = {
    "Wild Boar", "Rabid Wolf", "Forest Troll", "Mountain Goat",
    "Desert Scorpion", "Venomous Snake", "Ferocious Bear", "Golden Eagle",
    "Shadow Panther", "Arctic Fox", "Fire Lizard", "Water Serpent",
    "Earth Elemental", "Air Spirit", "Crystal Golem", "Shadow Imp"
};

const std::vector<std::string> beast_descriptions = {
    "A fierce beast from the wild", "A dangerous creature seeking prey",
    "A mystical creature from ancient times", "A powerful beast with special abilities",
    "A creature from another dimension", "A beast with magical properties",
    "A dangerous predator", "A mythical creature with unique powers"
};

const std::vector<std::string> buff_names = {
    "Power Surge", "Mighty Blessing", "Strength Infusion", "Battle Fury",
    "Warrior's Rage", "Heroic Strength", "Titan's Power", "Dragon's Might",
    "Phoenix's Blessing", "Demon's Fury", "Angel's Grace", "God's Power"
};

const std::vector<std::string> buff_descriptions = {
    "Increases attack power significantly", "Boosts your combat abilities",
    "Enhances your offensive capabilities", "Gives you superhuman strength",
    "Channels ancient warrior spirits", "Summons inner rage for battle",
    "Infuses you with mythical power", "Grants you divine strength"
};

const std::vector<std::string> creature_names = {
    "Goblin Warrior", "Orc Marauder", "Phoenix Hatchling", "Ancient Beast",
    "Dragonspawn", "Demon Spawn", "Celestial Guardian", "Void Walker",
    "Elemental Lord", "Arcane Golem", "Crystal Defender", "Shadow Stalker"
};

const std::vector<std::string> creature_descriptions = {
    "A fierce warrior from the goblin tribe", "A brutal raider from the orc clans",
    "A young phoenix with fire abilities", "An ancient beast with immense power",
    "A creature born from dragon essence", "A demonic entity seeking destruction",
    "A guardian from the celestial realm", "A being from the void between worlds",
    "A lord of elemental forces", "A golem infused with arcane magic",
    "A defender made of crystal", "A stalker from the shadow realm"
};

const std::vector<std::string> shield_names = {
    "Basic Shield", "Advanced Shield", "Iron Barrier", "Royal Guard Shield",
    "Legendary Shield", "Diamond Protection", "Cosmic Ward", "Ancient Shield",
    "Divine Barrier", "Mythical Guard", "Eternal Shield", "Ultimate Protection"
};

const std::vector<std::string> shield_descriptions = {
    "Provides basic protection", "Strong protection", "Metallic shield",
    "Decorative but effective", "Best protection", "Hardened defense",
    "Cosmic protection", "Ancient protection", "Divine protection",
    "Mythical protection", "Eternal protection", "Ultimate protection"
};

const std::vector<std::string> weapon_names = {
    "Bronze Sword", "Steel Longsword", "Mythril Axe", "Arcane Blade",
    "Oblivion Edge", "Dragonfang Sword", "Phoenix Blade", "Thunder Hammer",
    "Frostbite Axe", "Shadow Dagger", "Celestial Blade", "Divine Weapon"
};

const std::vector<std::string> weapon_descriptions = {
    "Simple weapon", "Balanced weapon", "Advanced weapon", "Elemental weapon",
    "Legendary weapon", "Dragon-killing weapon", "Fire-based weapon",
    "Electric weapon", "Ice weapon", "Stealth weapon", "Heavenly weapon",
    "Divine weapon"
};

const std::vector<std::string> artifact_names = {
    "Amulet of Majesty", "Ring of Power", "Crown of Elements", "Scepter of Dominion",
    "Talisman of Protection", "Orb of Power", "Staff of Elements", "Amulet of the Gods",
    "Ring of the Elements", "Crown of the Ancients", "Scepter of the Titans",
    "Talisman of the Phoenix"
};

const std::vector<std::string> artifact_descriptions = {
    "Enhances all attributes", "Concentrates magical energy", "Controls elemental forces",
    "Grants dominion over magical energies", "Provides powerful protection",
    "Stores immense power", "Channels elemental magic", "Blessed by the gods",
    "Master of the elements", "Worn by ancient rulers", "Wielded by titans",
    "Forged in the heart of a phoenix"
};

const std::vector<std::string> heal_names = {
    "Small Heal", "Moderate Heal", "Great Heal", "Eternal Life", "Sacred Blessing",
    "Heavenly Restoration", "Divine Cure", "Phoenix Renewal", "Angel's Mercy",
    "Life Infusion", "Soul Healing", "Ultimate Restoration"
};

const std::vector<std::string> heal_descriptions = {
    "Restores minor HP", "Restores moderate HP", "Restores significant HP",
    "Restores full HP", "Holy healing", "Divine restoration", "Mystical cure",
    "Rebirth through fire", "Blessing from above", "Infuses life energy",
    "Heals the soul", "Complete restoration"
};

const std::vector<std::string> buff_spell_names = {
    "Battle Cry", "Strength Surge", "Divine Grace", "Heroic Might", "Blessing of the Gods",
    "Titan's Fury", "Phoenix's Wrath", "Angel's Power", "Demon's Blessing",
    "Warrior's Spirit", "Battle Fury", "Ultimate Power"
};

const std::vector<std::string> buff_spell_descriptions = {
    "Temporary attack boost", "Sudden increase in strength", "Divine enhancement",
    "Heroic power surge", "Blessing from the gods", "Titanic power infusion",
    "Wrath of the phoenix", "Angelic power boost", "Demoniacal enhancement",
    "Ancient warrior spirit", "Frenzy attack mode", "Maximum power release"
};

const std::vector<std::string> defence_spell_names = {
    "Iron Skin", "Diamond Defense", "Cosmic Barrier", "Divine Shield",
    "Ancient Protection", "Eternal Ward", "Ultimate Defense", "Void Protection",
    "Elemental Ward", "Celestial Shield", "Mythical Barrier", "God's Protection"
};

const std::vector<std::string> defence_spell_descriptions = {
    "Hardened defense", "Cosmic protection", "Divine protection",
    "Ancient protection", "Eternal protection", "Ultimate protection",
    "Protection from the void", "Elemental protection", "Heavenly shield",
    "Mythical protection", "Supreme protection", "Divine safeguard"
};

const std::vector<Element> spell_elements = {
    Element::Fire, Element::Water, Element::Earth, Element::Air
};

#endif