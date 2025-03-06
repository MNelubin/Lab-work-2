/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include <gtest/gtest.h>
#include "../include/cards/card.h"
#include "../include/cards/spell_card.h"
#include "../include/cards/enums.h"
#include "../include/cards/attack_spell_card.h"
#include "../include/cards/heal_spell_card.h"
#include "../include/cards/buff_spell_card.h"
#include "../include/cards/defence_spell_card.h"
#include "../include/cards/beast_card.h"
#include "../include/cards/creature_card.h"
#include "../include/cards/weapon_card.h"
#include "../include/cards/artifact_card.h"
#include "../include/cards/shield_card.h"
#include "../include/cards/buff_card.h"
#include "../include/player/hand.h"
#include "../include/player/player.h"
#include "../include/player/character.h"
#include "../include/player/tank_character.h"
#include "../include/player/healer_character.h"
#include "../include/player/knight_character.h"


// ==================== Card Class Tests ====================

/**
 * @test Verify base Card class constructor and getters
 * @addtogroup GCI
 */
TEST(CardBasicTest, ConstructorAndGetters) {
    // Arrange
    const std::string name = "Fireball";
    const std::string desc = "Deals 5 damage";
    const Rarity rarity = Rarity::Epic;
    const int mana = 5;
    
    // Act
    Weapon_Card card(name, desc, rarity, mana);
    
    // Assert
    EXPECT_EQ(card.get_name(), name);
    EXPECT_EQ(card.get_description(), desc);
    EXPECT_EQ(card.get_rarity(), rarity);
    EXPECT_EQ(card.get_mana_cost(), mana);
}

/**
 * @test Testing getters and setters of Card class
 * @addtogroup GCI
 */
TEST(CardBasicTest, SettersValidation) {
    // Arrange
    Weapon_Card card("", "", Rarity::Common, 0);
    
    // Act & Assert: Name
    card.set_name("Ice Lance");
    EXPECT_EQ(card.get_name(), "Ice Lance");
    
    // Act & Assert: Description
    card.set_description("Freezes target");
    EXPECT_EQ(card.get_description(), "Freezes target");
    
    // Act & Assert: Mana
    card.set_mana_cost(3);
    EXPECT_EQ(card.get_mana_cost(), 3);
    
    // Act & Assert: Rarity
    card.set_rarity(Rarity::Rare);
    EXPECT_EQ(card.get_rarity(), Rarity::Rare);
}

// ==================== Spell_Card Class Tests ====================

/**
 * @test Spell_Card elemental functionality verification
 * @addtogroup GCI
 */
TEST(SpellCardTest, InheritanceAndElementHandling) {
    // Arrange
    Defence_Spell_Card spell("Frost Nova", "Freeze enemies", 
                    Rarity::Uncommon, 4, Element::Water);
    
    // Act & Assert: Base conditions check
    EXPECT_EQ(spell.get_name(), "Frost Nova");
    EXPECT_EQ(spell.get_mana_cost(), 4);
    
    // Act & Assert: Element check
    EXPECT_EQ(spell.get_element(), Element::Water);
    
    // Act: Element change
    spell.set_element(Element::Fire);
    
    // Assert: check changes
    EXPECT_EQ(spell.get_element(), Element::Fire);
}

/**
 * @test Boundary values for Spell_Card mana
 * @addtogroup GCI
 */
TEST(SpellCardTest, ManaBoundaryCases) {
    // Arrange & Act: Min Value
    Defence_Spell_Card spell1("Spark", "Minor shock", 
                     Rarity::Common, 0, Element::Air);
    EXPECT_EQ(spell1.get_mana_cost(), 0);
    
    // Arrange & Act: Max value
    Defence_Spell_Card spell2("Armageddon", "Global destruction", 
                     Rarity::Epic, 10, Element::Fire);
    EXPECT_EQ(spell2.get_mana_cost(), 10);
}

// ==================== Attack_Spell_Card Class Tests ====================

/**
 * @test Attack_Spell_Card damage validation
 * @addtogroup GCI
 */
TEST(AttackSpellTest, DamageManagement) {
    Attack_Spell_Card spell("Fire Blast", "Instant damage", 
                           Rarity::Common, 2, Element::Fire, 3);
    
    EXPECT_EQ(spell.get_base_damage(), 3);
    
    spell.set_base_damage(5);
    ASSERT_EQ(spell.get_base_damage(), 5);
}

/**
 * @test Invalid damage initialization for Attack_Spell_Card
 * @addtogroup ErrorHandling
 */
TEST(AttackSpellTest, InvalidDamageThrows) {
    EXPECT_THROW(
        Attack_Spell_Card("Invalid", "Test", Rarity::Common, 0, Element::Fire, -1),
        std::invalid_argument
    );
}


// ==================== Heal_Spell_Card Class Tests ====================

/**
 * @test Heal_Spell_Card value management
 * @addtogroup GCI
 */
TEST(HealSpellTest, HealManagement) {
    Heal_Spell_Card spell("Healing Wave", "Restore health", 
                         Rarity::Rare, 4, Element::Water, 10, 1.2f);
    
    // Check initial values
    EXPECT_EQ(spell.get_base_heal(), 10);
    ASSERT_FLOAT_EQ(spell.get_eff(), 1.2f);
    
    // Test setters
    spell.set_base_heal(15);
    spell.set_eff(1.5f);
    
    EXPECT_EQ(spell.get_base_heal(), 15);
    ASSERT_FLOAT_EQ(spell.get_eff(), 1.5f);
}

/**
 * @test Invalid heal/efficiency values for Heal_Spell_Card
 * @addtogroup ErrorHandling
 */
TEST(HealSpellTest, InvalidValuesThrow) {
    // Test invalid constructor arguments
    EXPECT_THROW(
        Heal_Spell_Card("Invalid Heal", "Test", Rarity::Common, 2, Element::Earth, -5, 0.5f),
        std::invalid_argument
    );
    
    EXPECT_THROW(
        Heal_Spell_Card("Invalid Eff", "Test", Rarity::Epic, 3, Element::Air, 10, -1.0f),
        std::invalid_argument
    );
    
    // Test invalid setter calls
    Heal_Spell_Card spell("Test", "Test", Rarity::Common, 1, Element::Fire, 5, 1.0f);
    
    EXPECT_THROW(spell.set_base_heal(-1), std::invalid_argument);
    ASSERT_THROW(spell.set_eff(0.0f), std::invalid_argument);
}


// ==================== Buff_Spell_Card Class Tests ====================

/**
 * @test Buff_Spell_Card basic functionality
 * @addtogroup GCI
 */
TEST(BuffSpellTest, BasicFunctionality) {
    Buff_Spell_Card spell("Power Up", "Increases strength", 
                       Rarity::Common, 3, Element::Earth, 1.5f);
    
    EXPECT_EQ(spell.get_name(), "Power Up");
    EXPECT_FLOAT_EQ(spell.get_multiplier(), 1.5f);
}

/**
 * @test Invalid values for Buff_Spell_Card
 * @addtogroup ErrorHandling
 */
TEST(BuffSpellTest, InvalidValuesThrow) {
    EXPECT_THROW(
        Buff_Spell_Card("Invalid", "Test", Rarity::Common, 2, Element::Fire, -1.0f),
        std::invalid_argument
    );
    
    Buff_Spell_Card spell("Test", "Test", Rarity::Common, 1, Element::Fire, 1.0f);
    
    EXPECT_THROW(spell.set_multiplier(0.0f), std::invalid_argument);
}


// ==================== Defence_Spell_Card Class Tests ====================

/**
 * @test Defence_Spell_Card basic functionality
 * @addtogroup GCI
 */
TEST(DefenceSpellTest, BasicFunctionality) {
    Defence_Spell_Card spell("Shield Wall", "Increases defense", 
                         Rarity::Common, 3, Element::Earth, 5);
    
    EXPECT_EQ(spell.get_name(), "Shield Wall");
    EXPECT_EQ(spell.get_base_def(), 5);
}

/**
 * @test Invalid values for Defence_Spell_Card
 * @addtogroup ErrorHandling
 */
TEST(DefenceSpellTest, InvalidValuesThrow) {
    EXPECT_THROW(
        Defence_Spell_Card("Invalid", "Test", Rarity::Common, 2, Element::Fire, -1),
        std::invalid_argument
    );
    
    Defence_Spell_Card spell("Test", "Test", Rarity::Common, 1, Element::Fire, 5);
    
    EXPECT_THROW(spell.set_base_def(0), std::invalid_argument);
}


// ==================== Beast_Card Class Tests ====================

/**
 * @test Beast_Card basic functionality
 * @addtogroup GCI
 */
TEST(BeastCardTest, BasicFunctionality) {
    Beast_Card beast("Wolf", "A fierce predator", 
                     Rarity::Common, 3, 5, Tribe::North);
    
    EXPECT_EQ(beast.get_name(), "Wolf");
    EXPECT_EQ(beast.get_base_dmg(), 5);
    EXPECT_EQ(beast.get_tribe(), Tribe::North);
}

/**
 * @test Invalid values for Beast_Card
 * @addtogroup ErrorHandling
 */
TEST(BeastCardTest, InvalidValuesThrow) {
    EXPECT_THROW(
        Beast_Card("Invalid", "Test", Rarity::Common, 2, -1, Tribe::North),
        std::invalid_argument
    );
    
    Beast_Card beast("Test", "Test", Rarity::Common, 1, 5, Tribe::North);
    
    EXPECT_THROW(beast.set_base_dmg(0), std::invalid_argument);
}


// ==================== Creature_Card Class Tests ====================

/**
 * @test Creature_Card basic functionality
 * @addtogroup GCI
 */
TEST(CreatureCardTest, BasicFunctionality) {
    Creature_Card creature("Knight", "A brave warrior", 
                            Rarity::Common, 4, 6, 1.2f);
    
    EXPECT_EQ(creature.get_name(), "Knight");
    EXPECT_EQ(creature.get_base_dmg(), 6);
    EXPECT_FLOAT_EQ(creature.get_weapon_multiplier(), 1.2f);
}

/**
 * @test Invalid values for Creature_Card
 * @addtogroup ErrorHandling
 */
TEST(CreatureCardTest, InvalidValuesThrow) {
    EXPECT_THROW(
        Creature_Card("Invalid", "Test", Rarity::Common, 2, -1, 1.0f),
        std::invalid_argument
    );
    
    EXPECT_THROW(
        Creature_Card("Invalid", "Test", Rarity::Common, 2, 5, 0.0f),
        std::invalid_argument
    );
    
    Creature_Card creature("Test", "Test", Rarity::Common, 1, 5, 1.0f);
    
    EXPECT_THROW(creature.set_base_dmg(0), std::invalid_argument);
    EXPECT_THROW(creature.set_weapon_multiplier(-1.0f), std::invalid_argument);
}


// ==================== Weapon_Card Class Tests ====================

/**
 * @test Weapon_Card basic functionality
 * @addtogroup GCI
 */
TEST(WeaponCardTest, BasicFunctionality) {
    Weapon_Card weapon("Sword", "Increases attack damage", 
                       Rarity::Common, 3, 5);
    
    EXPECT_EQ(weapon.get_name(), "Sword");
    EXPECT_EQ(weapon.get_dmg_up(), 5);
}

/**
 * @test Invalid values for Weapon_Card
 * @addtogroup ErrorHandling
 */
TEST(WeaponCardTest, InvalidValuesThrow) {
    EXPECT_THROW(
        Weapon_Card("Invalid", "Test", Rarity::Common, 2, -1),
        std::invalid_argument
    );
    
    Weapon_Card weapon("Test", "Test", Rarity::Common, 1, 5);
    
    EXPECT_THROW(weapon.set_dmg_up(0), std::invalid_argument);
}


// ==================== Artifact_Card Class Tests ====================

/**
 * @test Artifact_Card basic functionality
 * @addtogroup GCI
 */
TEST(ArtifactCardTest, BasicFunctionality) {
    Artifact_Card artifact("Amulet", "Increases power", 
                           Rarity::Rare, 4, 1.5f);
    
    EXPECT_EQ(artifact.get_name(), "Amulet");
    EXPECT_FLOAT_EQ(artifact.get_multiplier(), 1.5f);
}

/**
 * @test Invalid values for Artifact_Card
 * @addtogroup ErrorHandling
 */
TEST(ArtifactCardTest, InvalidValuesThrow) {
    EXPECT_THROW(
        Artifact_Card("Invalid", "Test", Rarity::Common, 2, -1.0f),
        std::invalid_argument
    );
    
    Artifact_Card artifact("Test", "Test", Rarity::Common, 1, 1.0f);
    
    EXPECT_THROW(artifact.set_multiplier(0.0f), std::invalid_argument);
}


// ==================== Shield_Card Class Tests ====================

/**
 * @test Shield_Card basic functionality
 * @addtogroup GCI
 */
TEST(ShieldCardTest, BasicFunctionality) {
    Shield_Card shield("Iron Shield", "Protects from damage", 
                       Rarity::Common, 3, 5);
    
    EXPECT_EQ(shield.get_name(), "Iron Shield");
    EXPECT_EQ(shield.get_usage(), 5);
}

/**
 * @test Invalid values for Shield_Card
 * @addtogroup ErrorHandling
 */
TEST(ShieldCardTest, InvalidValuesThrow) {
    EXPECT_THROW(
        Shield_Card("Invalid", "Test", Rarity::Common, 2, -1),
        std::invalid_argument
    );
    
    Shield_Card shield("Test", "Test", Rarity::Common, 1, 5);
    
    EXPECT_THROW(shield.set_usage(0), std::invalid_argument);
}


// ==================== Buff_Card Class Tests ====================

/**
 * @test Buff_Card basic functionality
 * @addtogroup GCI
 */
TEST(BuffCardTest, BasicFunctionality) {
    Buff_Card buff("Power Boost", "Increases attack power", 
                   Rarity::Common, 3, 1.5f);
    
    EXPECT_EQ(buff.get_name(), "Power Boost");
    EXPECT_FLOAT_EQ(buff.get_buff_amount(), 1.5f);
}

/**
 * @test Invalid values for Buff_Card
 * @addtogroup ErrorHandling
 */
TEST(BuffCardTest, InvalidValuesThrow) {
    EXPECT_THROW(
        Buff_Card("Invalid", "Test", Rarity::Common, 2, -1.0f),
        std::invalid_argument
    );
    
    Buff_Card buff("Test", "Test", Rarity::Common, 1, 1.0f);
    
    EXPECT_THROW(buff.set_buff_amount(0.0f), std::invalid_argument);
}


// ==================== Hand Class Tests ====================

/**
 * @test Basic Hand functionality
 * @addtogroup GCI
 */
TEST(HandTest, ConstructorAndGetters) {
    Hand hand;
    
    // Test initial state
    EXPECT_EQ(hand.get_amount(), 0);
    EXPECT_TRUE(hand.get_unique_card_types().empty());
}

/**
 * @test Add and remove card from Hand functionality
 * @addtogroup GCI
 */
TEST(HandTest, AddAndRemoveCard) {
    Hand hand;
    
    // Add a card and verify
    hand.add_card(std::make_unique<Shield_Card>("Test Shield", "Test", Rarity::Common, 2, 3));
    EXPECT_EQ(hand.get_amount(), 1);
    
    // Remove the card and verify
    hand.remove_card(0);
    EXPECT_EQ(hand.get_amount(), 0);
}

/**
 * @test Invalid index handling in Hand
 * @addtogroup ErrorHandling
 */
TEST(HandTest, InvalidIndexHandling) {
    Hand hand;
    
    // Test remove_card with invalid index
    EXPECT_THROW(hand.remove_card(-1), std::out_of_range);
    EXPECT_THROW(hand.remove_card(0), std::out_of_range);
    
    // Test get_card with invalid index
    EXPECT_THROW(hand.get_card(-1), std::out_of_range);
    EXPECT_THROW(hand.get_card(0), std::out_of_range);
}

/**
 * @test Card retrieval functionality in Hand
 * @addtogroup GCI
 */
TEST(HandTest, GetCard) {
    Hand hand;
    hand.add_card(std::make_unique<Shield_Card>("Test Shield", "Test", Rarity::Common, 2, 3));
    
    // Verify card properties
    Card& card = hand.get_card(0);
    EXPECT_EQ(card.get_name(), "Test Shield");
    EXPECT_EQ(card.get_mana_cost(), 2);
}

/**
 * @test Sorting Hand functionality
 * @addtogroup GCI
 */
TEST(HandTest, SortByMana) {
    Hand hand;
    
    // Add cards with different mana costs
    hand.add_card(std::make_unique<Shield_Card>("Shield 1", "Test", Rarity::Common, 5, 3));
    hand.add_card(std::make_unique<Buff_Card>("Buff 1", "Test", Rarity::Common, 2, 1.5f));
    hand.add_card(std::make_unique<Shield_Card>("Shield 2", "Test", Rarity::Common, 3, 3));
    
    // Sort and verify order
    hand.sort_by_mana();
    EXPECT_EQ(hand.get_card(0).get_mana_cost(), 5);
    EXPECT_EQ(hand.get_card(1).get_mana_cost(), 3);
    EXPECT_EQ(hand.get_card(2).get_mana_cost(), 2);
}

/**
 * @test Standard Hand generation
 * @addtogroup GCI
 */
TEST(HandTest, GenerateStandardHands) {
    Hand hand;
    
    // Test valid hand generation
    EXPECT_NO_THROW(hand.generate(1));
    EXPECT_GT(hand.get_amount(), 0);
    
    EXPECT_NO_THROW(hand.generate(2));
    EXPECT_GT(hand.get_amount(), 0);
    
    EXPECT_NO_THROW(hand.generate(3));
    EXPECT_GT(hand.get_amount(), 0);
    
    // Test invalid hand ID
    EXPECT_THROW(hand.generate(0), std::invalid_argument);
    EXPECT_THROW(hand.generate(4), std::invalid_argument);
}

/**
 * @test Unique card types in Hand functionality
 * @addtogroup GCI
 */
TEST(HandTest, GetUniqueCardTypes) {
    Hand hand;
    
    // Add different card types
    hand.add_card(std::make_unique<Shield_Card>("Shield 1", "Test", Rarity::Common, 2, 3));
    hand.add_card(std::make_unique<Buff_Card>("Buff 1", "Test", Rarity::Common, 3, 1.5f));
    hand.add_card(std::make_unique<Shield_Card>("Shield 2", "Test", Rarity::Common, 2, 3));
    
    // Verify unique types
    auto types = hand.get_unique_card_types();
    EXPECT_EQ(types.size(), 2);
}

/**
 * @test Get cards by type in Hand functionality
 * @addtogroup GCI
 */
TEST(HandTest, GetCardsByType) {
    Hand hand;
    
    // Add cards
    hand.add_card(std::make_unique<Shield_Card>("Shield 1", "Test", Rarity::Common, 2, 3));
    hand.add_card(std::make_unique<Buff_Card>("Buff 1", "Test", Rarity::Common, 3, 1.5f));
    hand.add_card(std::make_unique<Shield_Card>("Shield 2", "Test", Rarity::Common, 2, 3));
    
    // Get Shield cards and verify
    auto shield_cards = hand.get_cards_by_type(typeid(Shield_Card).name());
    EXPECT_EQ(shield_cards.size(), 2);
    
    // Get Buff cards and verify
    auto buff_cards = hand.get_cards_by_type(typeid(Buff_Card).name());
    EXPECT_EQ(buff_cards.size(), 1);
}


// ==================== Character class Tests ====================

/**
 * @test Verify default constructor initializes fields correctly
 * @addtogroup GCI
 */
TEST(CharacterTest, DefaultConstructor) {
    // Arrange & Act
    Healer_Character character;

    // Assert
    EXPECT_EQ(character.get_xp(), 0);
    EXPECT_EQ(character.get_name(), "");
    EXPECT_FLOAT_EQ(character.get_heal_multiplier(), 1.0f);
    EXPECT_FLOAT_EQ(character.get_dmg_multiplier(), 1.0f);
    EXPECT_FLOAT_EQ(character.get_armor_multiplier(), 1.0f);
    EXPECT_EQ(character.get_description(), "");
    EXPECT_EQ(character.get_xp_to_next_lvl(), 100);
    EXPECT_EQ(character.get_level(), 1);
}

/**
 * @test Verify name/description constructor with valid input
 * @addtogroup GCI
 */
TEST(CharacterTest, NameDescriptionConstructorValid) {
    // Arrange & Act
    Healer_Character character("Aragorn", "A brave ranger from the North");

    // Assert
    EXPECT_EQ(character.get_name(), "Aragorn");
    EXPECT_EQ(character.get_description(), "A brave ranger from the North");
}

/**
 * @test Verify name/description constructor throws for invalid name length
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, NameDescriptionConstructorInvalidName) {
    EXPECT_THROW(
        Healer_Character character(std::string(51, 'a'), "Valid description"),
        std::invalid_argument
    );
}

/**
 * @test Verify name/description constructor throws for invalid description length
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, NameDescriptionConstructorInvalidDescription) {
    EXPECT_THROW(
        Healer_Character character("Valid name", std::string(201, 'a')),
        std::invalid_argument
    );
}

/**
 * @test Verify full constructor with valid parameters
 * @addtogroup GCI
 */
TEST(CharacterTest, FullConstructorValid) {
    // Arrange & Act
    Healer_Character character(200, 2, 100, "Legolas", 1.2f, 1.3f, 1.1f, "Elven archer",1);

    // Assert
    EXPECT_EQ(character.get_xp_to_next_lvl(), 200);
    EXPECT_EQ(character.get_level(), 2);
    EXPECT_EQ(character.get_xp(), 100);
    EXPECT_EQ(character.get_name(), "Legolas");
    EXPECT_FLOAT_EQ(character.get_heal_multiplier(), 1.2f);
    EXPECT_FLOAT_EQ(character.get_dmg_multiplier(), 1.3f);
    EXPECT_FLOAT_EQ(character.get_armor_multiplier(), 1.1f);
    EXPECT_EQ(character.get_description(), "Elven archer");
    EXPECT_EQ(character.get_ability_uses(), 1);
    
}

/**
 * @test Verify full constructor throws for invalid xp
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, FullConstructorInvalidXp) {
    EXPECT_THROW(
        Healer_Character character(100, 1, -1, "Valid", 1.0f, 1.0f, 1.0f, "Valid",1),
        std::invalid_argument
    );
}

/**
 * @test Verify full constructor throws for invalid heal multiplier
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, FullConstructorInvalidHealMultiplier) {
    EXPECT_THROW(
        Healer_Character character(100, 1, 0, "Valid", 0.0f, 1.0f, 1.0f, "Valid",1),
        std::invalid_argument
    );
}

/**
 * @test Verify full constructor throws for invalid xp_to_next_lvl
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, FullConstructorInvalidXpToNextLvl) {
    EXPECT_THROW(
        Healer_Character character(0, 1, 0, "Valid", 1.0f, 1.0f, 1.0f, "Valid",1),
        std::invalid_argument
    );
}

/**
 * @test Verify full constructor throws for invalid level
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, FullConstructorInvalidLevel) {
    EXPECT_THROW(
        Healer_Character character(100, 0, 0, "Valid", 1.0f, 1.0f, 1.0f, "Valid",1),
        std::invalid_argument
    );
}

// --------------------- Character Setter Tests ---------------------

/**
 * @test Verify set_xp with valid values
 * @addtogroup GCI
 */
TEST(CharacterTest, SetXpValid) {
    // Arrange
    Healer_Character character;

    // Act & Assert
    character.set_xp(50);
    EXPECT_EQ(character.get_xp(), 50);
}

/**
 * @test Verify set_xp throws for negative values
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, SetXpInvalid) {
    Healer_Character character;
    EXPECT_THROW(character.set_xp(-1), std::invalid_argument);
}

/**
 * @test Verify set_name with valid values
 * @addtogroup GCI
 */
TEST(CharacterTest, SetNameValid) {
    // Arrange
    Healer_Character character;

    // Act & Assert
    character.set_name("Gandalf");
    EXPECT_EQ(character.get_name(), "Gandalf");
}

/**
 * @test Verify set_name throws for invalid length
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, SetNameInvalid) {
    Healer_Character character;
    EXPECT_THROW(character.set_name(std::string(51, 'a')), std::invalid_argument);
}

/**
 * @test Verify set_heal_multiplier with valid values
 * @addtogroup GCI
 */
TEST(CharacterTest, SetHealMultiplierValid) {
    // Arrange
    Healer_Character character;

    // Act & Assert
    character.set_heal_multiplier(1.5f);
    EXPECT_FLOAT_EQ(character.get_heal_multiplier(), 1.5f);
}

/**
 * @test Verify set_heal_multiplier throws for invalid values
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, SetHealMultiplierInvalid) {
    Healer_Character character;
    EXPECT_THROW(character.set_heal_multiplier(0.0f), std::invalid_argument);
}

/**
 * @test Verify set_description with valid values
 * @addtogroup GCI
 */
TEST(CharacterTest, SetDescriptionValid) {
    // Arrange
    Healer_Character character;

    // Act & Assert
    character.set_description("A wise wizard");
    EXPECT_EQ(character.get_description(), "A wise wizard");
}

/**
 * @test Verify set_description throws for invalid length
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, SetDescriptionInvalid) {
    Healer_Character character;
    EXPECT_THROW(character.set_description(std::string(201, 'a')), std::invalid_argument);
}

/**
 * @test Verify set_xp_to_next_lvl with valid values
 * @addtogroup GCI
 */
TEST(CharacterTest, SetXpToNextLvlValid) {
    // Arrange
    Healer_Character character;

    // Act & Assert
    character.set_xp_to_next_lvl(150);
    EXPECT_EQ(character.get_xp_to_next_lvl(), 150);
}

/**
 * @test Verify set_xp_to_next_lvl throws for invalid values
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, SetXpToNextLvlInvalid) {
    Healer_Character character;
    EXPECT_THROW(character.set_xp_to_next_lvl(0), std::invalid_argument);
}

/**
 * @test Verify set_level with valid values
 * @addtogroup GCI
 */
TEST(CharacterTest, SetLevelValid) {
    // Arrange
    Healer_Character character;

    // Act & Assert
    character.set_level(3);
    EXPECT_EQ(character.get_level(), 3);
}

/**
 * @test Verify set_level throws for invalid values
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, SetLevelInvalid) {
    Healer_Character character;
    EXPECT_THROW(character.set_level(0), std::invalid_argument);
}

// --------------------- Character Getter Tests ---------------------

/**
 * @test Verify all getters return correct values
 * @addtogroup GCI
 */
TEST(CharacterTest, GettersReturnCorrectValues) {
    // Arrange
    Healer_Character character(200, 2,100, "Frodo", 1.2f, 1.3f, 1.1f, "Hobbit from the Shire",1 );

    // Act & Assert
    EXPECT_EQ(character.get_xp_to_next_lvl(), 200);
    EXPECT_EQ(character.get_level(), 2);
    EXPECT_EQ(character.get_xp(), 100);
    EXPECT_EQ(character.get_name(), "Frodo");
    EXPECT_FLOAT_EQ(character.get_heal_multiplier(), 1.2f);
    EXPECT_FLOAT_EQ(character.get_dmg_multiplier(), 1.3f);
    EXPECT_FLOAT_EQ(character.get_armor_multiplier(), 1.1f);
    EXPECT_EQ(character.get_description(), "Hobbit from the Shire");
    
}

// --------------------- Level-Up Logic Tests ---------------------

/**
 * @test Verify single level-up when XP reaches threshold
 * @addtogroup GCI
 */
TEST(CharacterTest, SingleLevelUp) {
    // Arrange
    Healer_Character character;
    character.set_xp_to_next_lvl(100);
    character.set_xp(100);

    // Act & Assert
    EXPECT_EQ(character.get_level(), 2);
    EXPECT_EQ(character.get_xp(), 0);
    EXPECT_FLOAT_EQ(character.get_heal_multiplier(), 1.05f);
    EXPECT_FLOAT_EQ(character.get_dmg_multiplier(), 1.05f);
    EXPECT_FLOAT_EQ(character.get_armor_multiplier(), 1.05f);
    EXPECT_EQ(character.get_xp_to_next_lvl(), 120);
}

/**
 * @test Verify multiple level-ups when XP exceeds multiple thresholds
 * @addtogroup GCI
 */
TEST(CharacterTest, MultipleLevelUps) {
    // Arrange
    Healer_Character character;
    character.set_xp_to_next_lvl(100);
    character.set_xp(250); // Enough for 2 level-ups


    // Act & Assert
    EXPECT_EQ(character.get_level(), 3);
    EXPECT_EQ(character.get_xp(), 30); // 250 - 100 - 120 = 30
    EXPECT_FLOAT_EQ(character.get_heal_multiplier(), 1.10f);
    EXPECT_FLOAT_EQ(character.get_dmg_multiplier(), 1.10f);
    EXPECT_FLOAT_EQ(character.get_armor_multiplier(), 1.10f);
    EXPECT_EQ(character.get_xp_to_next_lvl(), 144); // 120 * 1.2
}

/**
 * @test Verify no level-up when XP is below threshold
 * @addtogroup GCI
 */
TEST(CharacterTest, NoLevelUp) {
    // Arrange
    Healer_Character character;
    character.set_xp_to_next_lvl(100);
    character.set_xp(99);

    // Act & Assert
    EXPECT_EQ(character.get_level(), 1);
    EXPECT_EQ(character.get_xp(), 99);
    EXPECT_FLOAT_EQ(character.get_heal_multiplier(), 1.0f);
    EXPECT_FLOAT_EQ(character.get_dmg_multiplier(), 1.0f);
    EXPECT_FLOAT_EQ(character.get_armor_multiplier(), 1.0f);
    EXPECT_EQ(character.get_xp_to_next_lvl(), 100);
}

// --------------------- add_xp Method Tests ---------------------

/**
 * @test Verify add_xp with positive value
 * @addtogroup GCI
 */
TEST(CharacterTest, AddXpPositive) {
    // Arrange
    Healer_Character character;
    character.set_xp(50);

    // Act
    character.add_xp(30);

    // Assert
    EXPECT_EQ(character.get_xp(), 80);
}

/**
 * @test Verify add_xp with zero value
 * @addtogroup GCI
 */
TEST(CharacterTest, AddXpZero) {
    // Arrange
    Healer_Character character;
    character.set_xp(50);

    // Act
    character.add_xp(0);

    // Assert
    EXPECT_EQ(character.get_xp(), 50);
}

/**
 * @test Verify add_xp throws for negative value
 * @addtogroup ErrorHandling
 */
TEST(CharacterTest, AddXpNegative) {
    // Arrange
    Healer_Character character;

    // Act & Assert
    EXPECT_THROW(character.add_xp(-10), std::invalid_argument);
}

/**
 * @test Verify add_xp triggers level-up
 * @addtogroup GCI
 */
TEST(CharacterTest, AddXpTriggersLevelUp) {
    // Arrange
    Healer_Character character;
    character.set_xp_to_next_lvl(100);
    character.set_xp(50);

    // Act
    character.add_xp(50);

    // Assert
    EXPECT_EQ(character.get_level(), 2);
    EXPECT_EQ(character.get_xp(), 0);
}

/**
 * @test Verify Healer_Character constructor initializes fields correctly
 * @addtogroup GCI
 */
TEST(HealerCharacterTest, Constructor) {
    Healer_Character healer(15, 100, 1, 0, "Healer", 1.0f, 1.0f, 1.0f, "Healer description", 3);
    EXPECT_EQ(healer.get_heal_amount(), 15);
    EXPECT_EQ(healer.get_ability_uses(), 3);
}

/**
 * @test Verify Healer_Character special action heals the player
 * @addtogroup GCI
 */
TEST(HealerCharacterTest, SpecialAction) {
    Player player(100, 50, 0, "Test Player", std::make_unique<Healer_Character>(10, 100, 1, 0, "Healer", 1.0f, 1.0f, 1.0f, "Healer description", 2));
    EXPECT_NO_THROW(player.perform_special_action());
    EXPECT_EQ(player.get_hp(), 110);
    EXPECT_EQ(player.get_character().get_ability_uses(), 1);
}

// ==================== Tank_Character Tests ====================

/**
 * @test Verify Tank_Character constructor initializes fields correctly
 * @addtogroup GCI
 */
TEST(TankCharacterTest, Constructor) {
    Tank_Character tank( 100, 1, 0, "Tank", 1.0f, 1.0f, 1.0f, "Tank description", 3, 2);
    EXPECT_EQ(tank.get_shield_add(), 2);
    EXPECT_EQ(tank.get_ability_uses(), 3);
}

/**
 * @test Verify Tank_Character special action applies shield correctly
 * @addtogroup GCI
 */
TEST(TankCharacterTest, SpecialAction) {
    Player player(100, 50, 0, "Test Player", nullptr, 0);
    Tank_Character tank(100, 1, 0, "Tank", 1.0f, 1.0f, 1.0f, "Tank description", 2, 3);
    player.set_character(std::make_unique<Tank_Character>(tank));
    
    EXPECT_NO_THROW(player.perform_special_action());
    EXPECT_EQ(player.get_shield_amount(), 3); 
    EXPECT_EQ(player.get_character().get_ability_uses(), 1);
}

// ==================== Knight_Character Tests ====================

/**
 * @test Verify Knight_Character constructor initializes fields correctly
 * @addtogroup GCI
 */
TEST(KnightCharacterTest, Constructor) {
    Knight_Character knight(100, 1, 0, "Knight", 1.0f, 1.0f, 1.0f, "Knight description", 3, 5, 0);
    EXPECT_EQ(knight.get_armor_up(), 5);
    EXPECT_EQ(knight.get_armored_amount(), 0);
    EXPECT_EQ(knight.get_ability_uses(), 3);
}

/**
 * @test Verify Knight_Character special action applies armor correctly
 * @addtogroup GCI
 */
TEST(KnightCharacterTest, SpecialAction) {
    Player player(100, 50, 0, "Test Player", nullptr, 0);
    Knight_Character knight(100, 1, 0, "Knight", 1.0f, 1.0f, 1.0f, "Knight description", 2, 5, 0);
    player.set_character(std::make_unique<Knight_Character>(knight));
    
    EXPECT_NO_THROW(player.perform_special_action());
    
    auto* knight_ptr = dynamic_cast<Knight_Character*>(&player.get_character());
    ASSERT_NE(knight_ptr, nullptr);
    
    EXPECT_EQ(player.get_armor(), 5);
    EXPECT_EQ(knight_ptr->get_armored_amount(), 1);
    EXPECT_EQ(knight_ptr->get_ability_uses(), 1);
}
// ==================== Test Runner ====================

/**
 * @brief Test entry point
 */
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}