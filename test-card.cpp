/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include <gtest/gtest.h>
#include "card.h"
#include "spell_card.h"
#include "enums.h"
#include "attack_spell_card.h"
#include "heal_spell_card.h"
#include "buff_spell_card.h"
#include "defence_spell_card.h"
#include "beast_card.h"
#include "creature_card.h"
#include "weapon_card.h"
#include "artifact_card.h"
#include "shield_card.h"
#include "buff_card.h"
#include "hand.h"

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
    Card card(name, desc, rarity, mana);
    
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
    Card card("", "", Rarity::Common, 0);
    
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
    Spell_Card spell("Frost Nova", "Freeze enemies", 
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
    Spell_Card spell1("Spark", "Minor shock", 
                     Rarity::Common, 0, Element::Air);
    EXPECT_EQ(spell1.get_mana_cost(), 0);
    
    // Arrange & Act: Max value
    Spell_Card spell2("Armageddon", "Global destruction", 
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

// ==================== Test Runner ====================

/**
 * @brief Test entry point
 */
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}