/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include <gtest/gtest.h>
#include "card.h"
#include "enums.h"

/**
 * @brief Test suite for Card class functionality
 * 
 * Covers constructor initialization and mutator methods validation.
 */
TEST(CardTest, ConstructorInitialization) {
    // Arrange
    const std::string expected_name = "Fireball";
    const int expected_mana = 5;
    const Rarity expected_rarity = Rarity::Epic;
    
    // Act
    Card card(expected_name, "Deals damage", expected_rarity, expected_mana);
    
    // Assert
    EXPECT_EQ(card.get_name(), expected_name);
    EXPECT_EQ(card.get_mana_cost(), expected_mana);
    EXPECT_EQ(card.get_rarity(), expected_rarity);
}

/**
 * @brief Tests mutator methods behavior
 * 
 * Verifies proper state changes after setters execution.
 */
TEST(CardTest, SettersFunctionality) {
    // Arrange
    Card card("", "", Rarity::Common, 0);
    const std::string new_name = "Ice Bolt";
    const int new_mana = 3;
    const Rarity new_rarity = Rarity::Rare;
    
    // Act
    card.set_name(new_name);
    card.set_mana_cost(new_mana);
    card.set_rarity(new_rarity);
    
    // Assert
    EXPECT_EQ(card.get_name(), new_name);
    EXPECT_EQ(card.get_mana_cost(), new_mana);
    EXPECT_EQ(card.get_rarity(), new_rarity);
}

/**
 * @brief Google Test entry point
 */
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}