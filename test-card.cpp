/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include <gtest/gtest.h>
#include "card.h"
#include "spell_card.h"
#include "enums.h"
#include "attack_spell_card.h"

// ==================== Card Class Tests ====================

/**
 * @test Verify base Card class constructor and getters
 * @group Getters/Setters/Initializations
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
 * @test Testing getters and setters
 * @group Getters/Setters/Initializations
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
 * @group Getters/Setters/Initializations
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
 * @test Boundary values for mana
 * @group SpellTests
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
 * @test Attack spell damage validation
 * @group Getters/Setters/Initializations
 */
TEST(AttackSpellTest, DamageManagement) {
    Attack_Spell_Card spell("Fire Blast", "Instant damage", 
                           Rarity::Common, 2, Element::Fire, 3);
    
    EXPECT_EQ(spell.get_base_damage(), 3);
    
    spell.set_base_damage(5);
    ASSERT_EQ(spell.get_base_damage(), 5);
}

/**
 * @test Invalid damage initialization
 * @group ErrorHandling
 */
TEST(AttackSpellTest, InvalidDamageThrows) {
    EXPECT_THROW(
        Attack_Spell_Card("Invalid", "Test", Rarity::Common, 0, Element::Fire, -1),
        std::invalid_argument
    );
}


// ==================== Heal_Spell_Card Class Tests ====================

/**
 * @test Heal value management
 * @group Getters/Setters/Initializations
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
 * @test Invalid heal/efficiency values
 * @group ErrorHandling
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

// ==================== Test Runner ====================

/**
 * @brief Test entry point
 */
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}