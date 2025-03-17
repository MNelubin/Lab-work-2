/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include <gtest/gtest.h>
#include <sstream>
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
#include "../include/player/ai_player.h"
#include "../include/player/human_player.h"


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

// ==================== Card Class Additional Tests ====================

/**
 * @test Verify generate_random_rarity() produces valid distributions
 * @addtogroup Card
 */
TEST(CardBasicTest, RarityDistribution) {
    class TestCard : public Card {
    public:
        TestCard() : Card("Test", "Test", Rarity::Common, 0) {}
        void use(Player&, Player&) override {}
        CardType get_type() const override { return CardType::Weapon; }
        void generate_properties() override {}
        void print_key_info() const override {}
    };

    TestCard card;
    std::map<Rarity, int> counts;
    const int SAMPLES = 1000;
    
    for (int i = 0; i < SAMPLES; ++i) {
        Rarity r = card.generate_random_rarity();
        EXPECT_TRUE(r >= Rarity::Common && r <= Rarity::Epic);
        counts[r]++;
    }
 
}

/**
 * @test Verify card type detection through get_type() in derived classes
 * @addtogroup Card
 */
TEST(CardBasicTest, PolymorphicTypeDetection) {
    Weapon_Card weapon("Sword", "Basic", Rarity::Common, 2, 5);
    Beast_Card beast("Wolf", "Fierce", Rarity::Common, 3, 5, Tribe::North);
    Buff_Card buff("Boost", "Power", Rarity::Common, 2, 1.1f);

    EXPECT_EQ(weapon.get_type(), CardType::Weapon);
    EXPECT_EQ(beast.get_type(), CardType::Beast);
    EXPECT_EQ(buff.get_type(), CardType::Buff);
}

/**
 * @test Verify pure virtual method contracts in derived classes
 * @addtogroup Card
 */
TEST(CardBasicTest, AbstractMethodImplementation) {
    // Test print_key_info() implementation
    testing::internal::CaptureStdout();
    Weapon_Card("Axe", "Chops", Rarity::Common, 3).print_key_info();
    EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());

    // Test generate_properties() implementation
    Buff_Card buff;
    EXPECT_NO_THROW(buff.generate_properties());
    
    // Test use() method
    AI_Player p1(100, 10, 0, "P1", nullptr);
    AI_Player p2(100, 10, 0, "P2", nullptr);
    EXPECT_NO_THROW(Beast_Card().use(p1, p2));
}

/**
 * @test Verify card cannot be instantiated directly
 * @addtogroup Card
 */
TEST(CardBasicTest, AbstractClassCheck) {
    EXPECT_TRUE(std::is_abstract<Card>());
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

/**
 * @test Verify use() method applies damage with attack multiplier
 * @addtogroup AttackSpell
 */
TEST(AttackSpellTest, UseAppliesDamageWithMultiplier) {
    Attack_Spell_Card spell("Fireball", "Deals damage", Rarity::Common, 3, Element::Fire, 10);
    AI_Player caster(100, 10, 0, "Caster", nullptr);
    AI_Player target(100, 5, 0, "Target", nullptr);
    
    // Set attack multiplier
    caster.set_cumulative_attack_multiplier(1.5f);
    
    spell.use(caster, target);
    
    // Expected damage: 10 * 1.5 = 15
    EXPECT_EQ(target.get_hp(), 100 - 15);
    EXPECT_FALSE(!caster.is_turn_active()); // Verify turn ended
}


/**
 * @test Verify print_key_info() displays correct damage
 * @addtogroup AttackSpell
 */
TEST(AttackSpellTest, PrintKeyInfoOutput) {
    Attack_Spell_Card spell("Bolt", "Lightning strike", Rarity::Rare, 4, Element::Air, 8);
    testing::internal::CaptureStdout();
    spell.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Base Damage: 8") != std::string::npos);
}


// ==================== Heal_Spell_Card Class Tests ====================

/**
 * @test Verify constructor initializes fields correctly
 * @addtogroup HealSpell
 */
TEST(HealSpellTest, ConstructorAndGetters) {
    Heal_Spell_Card spell("Healing Wave", "Restores health", 
                         Rarity::Rare, 4, Element::Water, 10, 1.2f);
    
    EXPECT_EQ(spell.get_name(), "Healing Wave");
    EXPECT_EQ(spell.get_mana_cost(), 4);
    EXPECT_EQ(spell.get_base_heal(), 10);
    EXPECT_FLOAT_EQ(spell.get_eff(), 1.2f);
    EXPECT_EQ(spell.get_element(), Element::Water);
}

/**
 * @test Verify setters with valid values
 * @addtogroup HealSpell
 */
TEST(HealSpellTest, SettersValidValues) {
    Heal_Spell_Card spell("Test", "Test", Rarity::Common, 2, Element::Fire, 5, 1.0f);
    
    spell.set_base_heal(15);
    spell.set_eff(1.5f);
    
    EXPECT_EQ(spell.get_base_heal(), 15);
    EXPECT_FLOAT_EQ(spell.get_eff(), 1.5f);
}

/**
 * @test Verify setters throw for invalid values
 * @addtogroup ErrorHandling
 */
TEST(HealSpellTest, SettersInvalidValues) {
    Heal_Spell_Card spell("Test", "Test", Rarity::Common, 1, Element::Air, 5, 1.0f);
    
    EXPECT_THROW(spell.set_base_heal(-1), std::invalid_argument);
    EXPECT_THROW(spell.set_eff(0.0f), std::invalid_argument);
}

/**
 * @test Verify use() method correctly applies healing with all multipliers
 * @addtogroup HealSpell
 */
TEST(HealSpellTest, UseAppliesHealing) {
    Heal_Spell_Card spell("Cure", "Heals 20 HP", Rarity::Uncommon, 3, Element::Earth, 20, 1.5f);
    
    // Create a healer character with base heal multiplier
    auto healer = std::make_unique<Healer_Character>(
        100, 1, 0, "Healer", 
        2.0f,  // heal_multiplier
        1.0f,  // dmg_multiplier 
        1.0f,  // armor_multiplier
        "Test Healer", 
        1      // ability_uses
    );
    
    AI_Player caster(100, 10, 0, "Caster", std::move(healer));
    AI_Player target(50, 5, 0, "Target", nullptr);
    
    // Set cumulative heal multiplier
    caster.set_cumulative_heal_multiplier(1.2f);
    
    // Apply spell
    spell.use(caster, caster); // Heal the caster
    
    // Calculate expected healing:
    // 20 (base) * 2.0 (character multiplier) * 1.2 (cumulative) * 1.5 (eff) = 72
    EXPECT_EQ(caster.get_hp(), 100 + 72); // Initial HP was 100
}

/**
 * @test Verify print_key_info() displays correct formatted data
 * @addtogroup HealSpell
 */
TEST(HealSpellTest, PrintKeyInfoOutput) {
    Heal_Spell_Card spell("Minor Heal", "Basic healing", Rarity::Common, 2, Element::Water, 10, 1.0f);
    testing::internal::CaptureStdout();
    spell.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    // Check exact output format
    EXPECT_TRUE(output.find("Base Heal: 10") != std::string::npos);
    EXPECT_TRUE(output.find("Efficiency: 1.0") != std::string::npos); // Match float formatting
}

/**
 * @test Verify use() method applies correct healing with multipliers
 * @addtogroup HealSpell
 */
TEST(HealSpellTest, UseAppliesHealingWithMultipliers) {
    Heal_Spell_Card spell("Divine Light", "Major heal", Rarity::Epic, 8, Element::Earth, 20, 1.5f);
    
    // Исправленный конструктор с полным набором параметров
    auto healer = std::make_unique<Healer_Character>(
        100,    // xp_to_next_lvl
        1,      // lvl
        0,      // xp
        "Healer", 
        1.5f,   // heal_multiplier
        1.0f,   // dmg_multiplier
        1.0f,   // armor_multiplier
        "Test Healer", 
        1       // ability_uses
    );
    
    AI_Player player(50, 10, 0, "Patient", std::move(healer));
    
    // Setup multipliers
    player.set_cumulative_heal_multiplier(2.0f);
    
    spell.use(player, player);
    
    // Expected healing: 20 * 1.5(character) * 2.0(cumulative) * 1.5(eff) = 90
    EXPECT_EQ(player.get_hp(), 50 + 90);
    EXPECT_FALSE(!player.is_turn_active());
}

/**
 * @test Verify generate_properties() generates valid values for all rarities
 * @addtogroup HealSpell
 */
TEST(HealSpellTest, GeneratePropertiesRarityRanges) {
    const int SAMPLES = 500;
    std::map<Rarity, int> rarity_counts;
    
    for (int i = 0; i < SAMPLES; ++i) {
        Heal_Spell_Card spell;
        spell.generate_properties();
        
        Rarity r = spell.get_rarity();
        int bh = spell.get_base_heal();
        float eff = spell.get_eff();
        int mc = spell.get_mana_cost();
        
        switch(r) {
            case Rarity::Common:
                EXPECT_GE(bh, 3); EXPECT_LE(bh, 8);
                EXPECT_GE(eff, 1.0f); EXPECT_LE(eff, 1.3f);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 3);
                break;
            case Rarity::Uncommon:
                EXPECT_GE(bh, 3); EXPECT_LE(bh, 12);
                EXPECT_GE(eff, 1.2f); EXPECT_LE(eff, 1.6f);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 4);
                break;
            case Rarity::Rare:
                EXPECT_GE(bh, 6); EXPECT_LE(bh, 20);
                EXPECT_GE(eff, 1.4f); EXPECT_LE(eff, 2.1f);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 5);
                break;
            case Rarity::Epic:
                EXPECT_GE(bh, 10); EXPECT_LE(bh, 34);
                EXPECT_GE(eff, 1.7f); EXPECT_LE(eff, 2.9f);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 7);
                break;
            default: FAIL() << "Invalid rarity generated";
        }
        rarity_counts[r]++;
    }
    
    EXPECT_GT(rarity_counts[Rarity::Common], 0);
    EXPECT_GT(rarity_counts[Rarity::Uncommon], 0);
    EXPECT_GT(rarity_counts[Rarity::Rare], 0);
    EXPECT_GT(rarity_counts[Rarity::Epic], 0);
}

/**
 * @test Verify print_key_info() displays formatted heal and efficiency
 * @addtogroup HealSpell
 */
TEST(HealSpellTest, PrintKeyInfoFormatted) {
    Heal_Spell_Card spell("Cure", "Basic heal", Rarity::Common, 2, Element::Water, 5, 1.2f);
    testing::internal::CaptureStdout();
    spell.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Base Heal: 5") != std::string::npos);
    EXPECT_TRUE(output.find("Efficiency: 1.2") != std::string::npos);
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

/**
 * @test Verify use() method correctly applies multipliers to attack and heal
 * @addtogroup BuffSpell
 */
TEST(BuffSpellTest, UseAppliesMultipliers) {
    Buff_Spell_Card spell("Enhance", "Boosts stats", Rarity::Epic, 5, Element::Earth, 1.8f);
    AI_Player player(100, 10, 0, "TestPlayer", nullptr);
    
    // Set initial multipliers
    player.set_cumulative_attack_multiplier(2.0f);
    player.set_cumulative_heal_multiplier(1.5f);
    
    spell.use(player, player);
    
    EXPECT_FLOAT_EQ(player.get_cumulative_attack_multiplier(), 3.6f);
    EXPECT_FLOAT_EQ(player.get_cumulative_heal_multiplier(), 2.7f);
}

/**
 * @test Verify generate_properties() generates valid values for all rarities
 * @addtogroup BuffSpell
 */
TEST(BuffSpellTest, GeneratePropertiesRarityRanges) {
    const int SAMPLES = 500;
    std::map<Rarity, int> rarity_counts;
    
    for (int i = 0; i < SAMPLES; ++i) {
        // Use valid constructor parameters
        Buff_Spell_Card spell("TempName", "TempDesc", Rarity::Common, 1, Element::Fire, 1.0f);
        spell.generate_properties();
        
        Rarity r = spell.get_rarity();
        float m = spell.get_multiplier();
        int mc = spell.get_mana_cost();

        
        
        
        // Validate ranges
        switch(r) {
            case Rarity::Common:
                EXPECT_GE(m, 1.1f); EXPECT_LE(m, 1.6f);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 3);
                break;
            case Rarity::Uncommon:
                EXPECT_GE(m, 1.3f); EXPECT_LE(m, 2.1f);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 4);
                break;
            case Rarity::Rare:
                EXPECT_GE(m, 1.6f); EXPECT_LE(m, 2.7f);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 5);
                break;
            case Rarity::Epic:
                EXPECT_GE(m, 2.0f); EXPECT_LE(m, 3.6f);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 7);
                break;
            default: FAIL() << "Invalid rarity generated";
        }
        
        rarity_counts[r]++;
    }
    
    // Verify all rarities are generated
    EXPECT_GT(rarity_counts[Rarity::Common], 0);
    EXPECT_GT(rarity_counts[Rarity::Uncommon], 0);
    EXPECT_GT(rarity_counts[Rarity::Rare], 0);
    EXPECT_GT(rarity_counts[Rarity::Epic], 0);
}

/**
 * @test Verify print_key_info() displays formatted multiplier value
 * @addtogroup BuffSpell
 */
TEST(BuffSpellTest, PrintKeyInfoOutput) {
    Buff_Spell_Card spell("Empower", "Strength boost", Rarity::Rare, 3, Element::Fire, 2.3f);
    testing::internal::CaptureStdout();
    spell.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Multiplier: 2.3") != std::string::npos)
        << "Actual output: " << output;
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

/**
 * @test Verify use() method correctly applies defense with armor multiplier
 * @addtogroup DefenceSpell
 */
TEST(DefenceSpellTest, UseAppliesDefenseWithMultiplier) {
    Defence_Spell_Card spell("Iron Shield", "Protection", Rarity::Epic, 5, Element::Earth, 10);
    AI_Player player(100, 10, 0, "TestPlayer", std::make_unique<Tank_Character>());
    
    // Set armor multiplier through character
    player.get_character().set_armor_multiplier(1.5f);
    player.set_armor(5);  // Initial armor
    
    spell.use(player, player);
    
    // Expected armor: 5 + (10 * 1.5) = 20
    EXPECT_EQ(player.get_armor(), 20);
}

/**
 * @test Verify generate_properties() generates valid values for all rarities
 * @addtogroup DefenceSpell
 */
TEST(DefenceSpellTest, GeneratePropertiesRarityRanges) {
    const int SAMPLES = 500;
    std::map<Rarity, int> rarity_counts;
    
    for (int i = 0; i < SAMPLES; ++i) {
        Defence_Spell_Card spell;
        spell.generate_properties();
        
        Rarity r = spell.get_rarity();
        int bd = spell.get_base_def();
        int mc = spell.get_mana_cost();

        
        // Validate value ranges
        switch(r) {
            case Rarity::Common:
                EXPECT_GE(bd, 2); EXPECT_LE(bd, 4);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 3);
                break;
            case Rarity::Uncommon:
                EXPECT_GE(bd, 3); EXPECT_LE(bd, 6);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 4);
                break;
            case Rarity::Rare:
                EXPECT_GE(bd, 5); EXPECT_LE(bd, 9);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 5);
                break;
            case Rarity::Epic:
                EXPECT_GE(bd, 8); EXPECT_LE(bd, 13);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 7);
                break;
            default: FAIL() << "Invalid rarity generated";
        }
        
        rarity_counts[r]++;
    }
    
    // Verify all rarities are generated
    EXPECT_GT(rarity_counts[Rarity::Common], 0);
    EXPECT_GT(rarity_counts[Rarity::Uncommon], 0);
    EXPECT_GT(rarity_counts[Rarity::Rare], 0);
    EXPECT_GT(rarity_counts[Rarity::Epic], 0);
}

/**
 * @test Verify print_key_info() displays correct defense value
 * @addtogroup DefenceSpell
 */
TEST(DefenceSpellTest, PrintKeyInfoOutput) {
    Defence_Spell_Card spell("Barrier", "Shield", Rarity::Rare, 3, Element::Water, 7);
    testing::internal::CaptureStdout();
    spell.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Base Defense: 7") != std::string::npos)
        << "Actual output: " << output;
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

/**
 * @test Verify use() method applies damage and ends turn
 * @addtogroup BeastCard
 */
TEST(BeastCardTest, UseAppliesDamageAndEndsTurn) {
    Beast_Card beast("Wolf", "A fierce predator", Rarity::Common, 3, 5, Tribe::North);
    AI_Player caster(100, 10, 0, "Caster", nullptr);
    AI_Player target(100, 5, 0, "Target", nullptr);
    
    // Set attack multiplier
    caster.set_cumulative_attack_multiplier(1.2f);
    
    beast.use(caster, target);
    
    // Expected damage: 5 * 1.2 = 6
    EXPECT_EQ(target.get_hp(), 100 - 6);
    EXPECT_FALSE(!caster.is_turn_active());
}


/**
 * @test Verify print_key_info() displays correct data
 * @addtogroup BeastCard
 */
TEST(BeastCardTest, PrintKeyInfoOutput) {
    Beast_Card beast("Bear", "Forest guardian", Rarity::Uncommon, 4, 6, Tribe::East);
    testing::internal::CaptureStdout();
    beast.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Base Damage: 6") != std::string::npos);
    EXPECT_TRUE(output.find("Tribe: East") != std::string::npos);
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

/**
 * @test Verify use() method applies correct damage with weapon bonuses
 * @addtogroup CreatureCard
 */
TEST(CreatureCardTest, UseAppliesDamageWithMultipliers) {
    Creature_Card creature("Dragon", "Fire breath", Rarity::Epic, 5, 10, 1.5f);
    AI_Player caster(100, 10, 0, "Caster", nullptr);
    AI_Player target(100, 5, 0, "Target", nullptr);
    
    // Setup bonuses
    caster.set_cumulative_weapon_bonus(4);
    caster.set_cumulative_attack_multiplier(2.0f);
    
    creature.use(caster, target);
    
    // Expected damage: (10 + (1.5 * 4)) * 2.0 = (10 + 6) * 2 = 32
    EXPECT_EQ(target.get_hp(), 100 - 32);
    EXPECT_FALSE(!caster.is_turn_active());
}

/**
 * @test Verify generate_properties() generates valid values for all rarities
 * @addtogroup CreatureCard
 */
TEST(CreatureCardTest, GeneratePropertiesRarityRanges) {
    const int SAMPLES = 500;
    std::map<Rarity, int> rarity_counts;
    
    for (int i = 0; i < SAMPLES; ++i) {
        Creature_Card card("Temp", "Temp", Rarity::Common, 1, 2, 1.0f);
        card.generate_properties();
        
        Rarity r = card.get_rarity();
        int dmg = card.get_base_dmg();
        float wm = card.get_weapon_multiplier();
        int mc = card.get_mana_cost();
        
        switch(r) {
            case Rarity::Common:
                EXPECT_GE(dmg, 2); EXPECT_LE(dmg, 4);
                EXPECT_GE(wm, 1.0f); EXPECT_LE(wm, 1.3f);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 3);
                break;
            case Rarity::Uncommon:
                EXPECT_GE(dmg, 3); EXPECT_LE(dmg, 6);
                EXPECT_GE(wm, 1.2f); EXPECT_LE(wm, 1.7f);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 4);
                break;
            case Rarity::Rare:
                EXPECT_GE(dmg, 5); EXPECT_LE(dmg, 9);
                EXPECT_GE(wm, 1.5f); EXPECT_LE(wm, 2.2f);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 5);
                break;
            case Rarity::Epic:
                EXPECT_GE(dmg, 8); EXPECT_LE(dmg, 13);
                EXPECT_GE(wm, 1.8f); EXPECT_LE(wm, 2.9f);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 7);
                break;
            default: FAIL() << "Invalid rarity generated";
        }
        
        rarity_counts[r]++;
    }
    
    EXPECT_GT(rarity_counts[Rarity::Common], 0);
    EXPECT_GT(rarity_counts[Rarity::Uncommon], 0);
    EXPECT_GT(rarity_counts[Rarity::Rare], 0);
    EXPECT_GT(rarity_counts[Rarity::Epic], 0);
}

/**
 * @test Verify print_key_info() displays correct damage and multiplier
 * @addtogroup CreatureCard
 */
TEST(CreatureCardTest, PrintKeyInfoOutput) {
    Creature_Card creature("Goblin", "Weak", Rarity::Common, 2, 3, 1.1f);
    testing::internal::CaptureStdout();
    creature.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Base Damage: 3") != std::string::npos);
    EXPECT_TRUE(output.find("Weapon Multiplier: 1.1") != std::string::npos);
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

/**
 * @test Verify use() method correctly adds damage bonus to player
 * @addtogroup WeaponCard
 */
TEST(WeaponCardTest, UseAddsDamageBonus) {
    Weapon_Card weapon("Dragon Slayer", "Legendary sword", Rarity::Epic, 6, 8);
    AI_Player player(100, 10, 0, "Warrior", nullptr);
    
    // Initial weapon bonus
    player.set_cumulative_weapon_bonus(3);
    weapon.use(player, player);
    
    EXPECT_EQ(player.get_cumulative_weapon_bonus(), 3 + 8);
}

/**
 * @test Verify generate_properties() generates valid values for all rarities
 * @addtogroup WeaponCard
 */
TEST(WeaponCardTest, GeneratePropertiesRarityRanges) {
    const int SAMPLES = 500;
    std::map<Rarity, int> rarity_counts;
    
    for (int i = 0; i < SAMPLES; ++i) {
        Weapon_Card weapon;
        weapon.generate_properties();
        
        Rarity r = weapon.get_rarity();
        int dmg = weapon.get_dmg_up();
        int mc = weapon.get_mana_cost();
        
        switch(r) {
            case Rarity::Common:
                EXPECT_GE(dmg, 2); EXPECT_LE(dmg, 4);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 3);
                break;
            case Rarity::Uncommon:
                EXPECT_GE(dmg, 3); EXPECT_LE(dmg, 6);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 4);
                break;
            case Rarity::Rare:
                EXPECT_GE(dmg, 5); EXPECT_LE(dmg, 9);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 5);
                break;
            case Rarity::Epic:
                EXPECT_GE(dmg, 8); EXPECT_LE(dmg, 13);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 7);
                break;
            default: FAIL() << "Invalid rarity generated";
        }
        
        rarity_counts[r]++;
    }
    
    EXPECT_GT(rarity_counts[Rarity::Common], 0);
    EXPECT_GT(rarity_counts[Rarity::Uncommon], 0);
    EXPECT_GT(rarity_counts[Rarity::Rare], 0);
    EXPECT_GT(rarity_counts[Rarity::Epic], 0);
}

/**
 * @test Verify print_key_info() displays correct damage increase value
 * @addtogroup WeaponCard
 */
TEST(WeaponCardTest, PrintKeyInfoOutput) {
    Weapon_Card weapon("Sword of Truth", "Holy weapon", Rarity::Rare, 4, 7);
    testing::internal::CaptureStdout();
    weapon.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Damage Increase: 7") != std::string::npos)
        << "Actual output: " << output;
}



// ==================== Artifact_Card Class Tests ====================

/**
 * @test Verify Artifact_Card's use() method correctly applies multipliers
 * @addtogroup ArtifactCard
 */
TEST(ArtifactCardTest, UseAppliesMultipliers) {
    Artifact_Card artifact("Test", "Boost", Rarity::Common, 2, 1.5f);
    AI_Player player(100, 10, 0, "TestPlayer", nullptr);
    
    // Set initial multipliers and bonus
    player.set_cumulative_attack_multiplier(2.0f);
    player.set_cumulative_heal_multiplier(1.0f);
    player.set_cumulative_weapon_bonus(4);

    // Apply artifact effect
    artifact.use(player, player);

    // Verify results with current logic (double multiplication)
    EXPECT_FLOAT_EQ(player.get_cumulative_attack_multiplier(), 6.0f); // 2.0 * (2.0 * 1.5)
    EXPECT_FLOAT_EQ(player.get_cumulative_heal_multiplier(), 1.5f);   // 1.0 * (1.0 * 1.5)
    EXPECT_EQ(player.get_cumulative_weapon_bonus(), 6);               // 4 * 1.5
}



/**
 * @test Verify print_key_info() displays correct multiplier
 * @addtogroup ArtifactCard
 */
TEST(ArtifactCardTest, PrintKeyInfoOutput) {
    Artifact_Card artifact("Test", "Desc", Rarity::Epic, 5, 2.5f);
    testing::internal::CaptureStdout();
    artifact.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Multiplier: 2.5") != std::string::npos);
}

/**
 * @test Verify constructor throws for invalid multiplier
 * @addtogroup ErrorHandling
 */
TEST(ArtifactCardTest, InvalidMultiplierThrows) {
    EXPECT_THROW(
        Artifact_Card("Invalid", "Test", Rarity::Common, 2, 0.0f),
        std::invalid_argument
    );
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

/**
 * @test Verify use() method correctly increases shield amount
 * @addtogroup ShieldCard
 */
TEST(ShieldCardTest, UseIncreasesShield) {
    Shield_Card shield("Iron Barrier", "Strong shield", Rarity::Epic, 5, 3);
    AI_Player player(100, 10, 0, "TestPlayer", nullptr);
    
    player.set_shield_amount(2); // Initial shield
    shield.use(player, player);
    
    EXPECT_EQ(player.get_shield_amount(), 5); // 2 + 3
}

/**
 * @test Verify generate_properties() generates valid values for all rarities
 * @addtogroup ShieldCard
 */
TEST(ShieldCardTest, GeneratePropertiesRarityRanges) {
    const int SAMPLES = 500;
    std::map<Rarity, int> rarity_counts;
    
    for (int i = 0; i < SAMPLES; ++i) {
        Shield_Card shield;
        shield.generate_properties();
        
        Rarity r = shield.get_rarity();
        int usage = shield.get_usage();
        int mc = shield.get_mana_cost();
        
        switch(r) {
            case Rarity::Common:
                EXPECT_GE(usage, 2); EXPECT_LE(usage, 4);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 3);
                break;
            case Rarity::Uncommon:
                EXPECT_GE(usage, 2); EXPECT_LE(usage, 6);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 4);
                break;
            case Rarity::Rare:
                EXPECT_GE(usage, 4); EXPECT_LE(usage, 8);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 5);
                break;
            case Rarity::Epic:
                EXPECT_GE(usage, 6); EXPECT_LE(usage, 11);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 7);
                break;
            default: FAIL() << "Invalid rarity generated";
        }
        
        rarity_counts[r]++;
    }
    
    EXPECT_GT(rarity_counts[Rarity::Common], 0);
    EXPECT_GT(rarity_counts[Rarity::Uncommon], 0);
    EXPECT_GT(rarity_counts[Rarity::Rare], 0);
    EXPECT_GT(rarity_counts[Rarity::Epic], 0);
}

/**
 * @test Verify print_key_info() displays correct usage value
 * @addtogroup ShieldCard
 */
TEST(ShieldCardTest, PrintKeyInfoOutput) {
    Shield_Card shield("Diamond Shield", "Ultimate protection", Rarity::Rare, 4, 5);
    testing::internal::CaptureStdout();
    shield.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Usage: 5") != std::string::npos)
        << "Actual output: " << output;
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

/**
 * @test Verify use() method correctly applies attack and heal multipliers
 * @addtogroup BuffCard
 */
TEST(BuffCardTest, UseAppliesMultipliers) {
    Buff_Card buff("Power Surge", "Boosts stats", Rarity::Epic, 5, 1.8f);
    AI_Player player(100, 10, 0, "TestPlayer", nullptr);
    
    // Set initial multipliers
    player.set_cumulative_attack_multiplier(2.0f);
    player.set_cumulative_heal_multiplier(1.5f);
    
    buff.use(player, player);
    
    EXPECT_FLOAT_EQ(player.get_cumulative_attack_multiplier(), 3.6f); // 2.0 * 1.8
    EXPECT_FLOAT_EQ(player.get_cumulative_heal_multiplier(), 2.7f);   // 1.5 * 1.8
}

/**
 * @test Verify generate_properties() generates valid values for all rarities
 * @addtogroup BuffCard
 */
TEST(BuffCardTest, GeneratePropertiesRarityRanges) {
    const int SAMPLES = 500;
    std::map<Rarity, int> rarity_counts;
    
    for (int i = 0; i < SAMPLES; ++i) {
        Buff_Card buff;
        buff.generate_properties();
        
        Rarity r = buff.get_rarity();
        float ba = buff.get_buff_amount();
        int mc = buff.get_mana_cost();
        
        // Validate ranges
        switch(r) {
            case Rarity::Common:
                EXPECT_GE(ba, 1.1f); EXPECT_LE(ba, 1.6f);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 3);
                break;
            case Rarity::Uncommon:
                EXPECT_GE(ba, 1.3f); EXPECT_LE(ba, 2.1f);
                EXPECT_GE(mc, 1); EXPECT_LE(mc, 4);
                break;
            case Rarity::Rare:
                EXPECT_GE(ba, 1.6f); EXPECT_LE(ba, 2.7f);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 5);
                break;
            case Rarity::Epic:
                EXPECT_GE(ba, 2.0f); EXPECT_LE(ba, 3.6f);
                EXPECT_GE(mc, 2); EXPECT_LE(mc, 7);
                break;
            default: FAIL() << "Invalid rarity generated";
        }
        
        rarity_counts[r]++;
    }
    
    // Verify all rarities can be generated
    EXPECT_GT(rarity_counts[Rarity::Common], 0);
    EXPECT_GT(rarity_counts[Rarity::Uncommon], 0);
    EXPECT_GT(rarity_counts[Rarity::Rare], 0); 
    EXPECT_GT(rarity_counts[Rarity::Epic], 0);
}

/**
 * @test Verify print_key_info() displays formatted buff amount
 * @addtogroup BuffCard
 */
TEST(BuffCardTest, PrintKeyInfoFormatted) {
    Buff_Card buff("Might Boost", "Strength", Rarity::Rare, 3, 2.3f);
    testing::internal::CaptureStdout();
    buff.print_key_info();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Buff Amount: 2.3") != std::string::npos)
        << "Actual output: " << output;
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
    EXPECT_THROW(hand.generate(5), std::invalid_argument);
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

// ==================== Hand Class Additional Tests ====================

/**
 * @test Verify generate_random_card() adds one card and maintains type distribution
 * @addtogroup Hand
 */
TEST(HandTest, GenerateRandomCardAddsValidCard) {
    Hand hand;
    const int INITIAL_SIZE = hand.get_amount();
    
    hand.generate_random_card();
    
    // Verify card count increased by 1
    EXPECT_EQ(hand.get_amount(), INITIAL_SIZE + 1);
    
    // Verify card type is valid
    Card& card = hand.get_card(0);
    bool is_valid_type = 
        dynamic_cast<Beast_Card*>(&card) ||
        dynamic_cast<Buff_Card*>(&card) ||
        dynamic_cast<Creature_Card*>(&card) ||
        dynamic_cast<Shield_Card*>(&card) ||
        dynamic_cast<Weapon_Card*>(&card) ||
        dynamic_cast<Artifact_Card*>(&card) ||
        dynamic_cast<Attack_Spell_Card*>(&card) ||
        dynamic_cast<Heal_Spell_Card*>(&card) ||
        dynamic_cast<Buff_Spell_Card*>(&card) ||
        dynamic_cast<Defence_Spell_Card*>(&card);
    
    EXPECT_TRUE(is_valid_type);
}

/**
 * @test Verify generate_random_card() follows probability distribution
 * @addtogroup Hand
 */
TEST(HandTest, GenerateRandomCardDistribution) {
    Hand hand;
    const int SAMPLES = 10000;
    std::map<std::string, int> type_counts;
    
    for (int i = 0; i < SAMPLES; ++i) {
        hand.generate_random_card();
        Card& card = hand.get_card(0);
        std::string type = typeid(card).name();
        type_counts[type]++;
        hand.remove_card(0);
    }
    
    // Check approximate distribution (10% ± 2% tolerance)
    for (const auto& pair : type_counts) {
        double percentage = (pair.second * 100.0) / SAMPLES;
        EXPECT_NEAR(percentage, 10.0, 2.0)
            << "Type: " << pair.first << " had " << percentage << "% distribution";
    }
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
    AI_Player player(100, 50, 0, "Test Player", std::make_unique<Healer_Character>(10, 100, 1, 0, "Healer", 1.0f, 1.0f, 1.0f, "Healer description", 2));
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
    AI_Player player(100, 50, 0, "Test Player", nullptr, 0);
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
    AI_Player player(100, 50, 0, "Test Player", nullptr, 0);
    Knight_Character knight(100, 1, 0, "Knight", 1.0f, 1.0f, 1.0f, "Knight description", 2, 5, 0);
    player.set_character(std::make_unique<Knight_Character>(knight));
    
    EXPECT_NO_THROW(player.perform_special_action());
    
    auto* knight_ptr = dynamic_cast<Knight_Character*>(&player.get_character());
    ASSERT_NE(knight_ptr, nullptr);
    
    EXPECT_EQ(player.get_armor(), 5);
    EXPECT_EQ(knight_ptr->get_armored_amount(), 1);
    EXPECT_EQ(knight_ptr->get_ability_uses(), 1);   
}

// ==================== Character Class Additional Tests ====================

/**
 * @test Verify get_character_statistics() returns formatted string with all stats
 * @addtogroup Character
 */
TEST(CharacterTest, GetCharacterStatisticsFormatsCorrectly) {
    Healer_Character character(
        150,    // xp_to_next_lvl
        2,      // lvl
        80,     // xp
        "TestHero",
        1.2f,   // heal_mltpl
        1.3f,   // dmg_mltpl
        1.1f,   // armor_mltpl
        "Test description",
        2       // ability_uses
    );
    
    std::string stats = character.get_character_statistics();
    
    EXPECT_TRUE(stats.find("Name: TestHero") != std::string::npos);
    EXPECT_TRUE(stats.find("Level: 2") != std::string::npos);
    EXPECT_TRUE(stats.find("XP: 80/150") != std::string::npos);
    EXPECT_TRUE(stats.find("Heal Multiplier: 1.2") != std::string::npos);
    EXPECT_TRUE(stats.find("Damage Multiplier: 1.3") != std::string::npos);
    EXPECT_TRUE(stats.find("Armor Multiplier: 1.1") != std::string::npos);
}


/**
 * @test Verify get_class_name() returns correct identifier for Healer
 * @addtogroup Character
 */
TEST(HealerCharacterTest, GetClassNameReturnsCorrectValue) {
    Healer_Character healer;
    EXPECT_EQ(healer.get_class_name(), "Healer");
}

/**
 * @test Verify get_class_name() returns correct identifier for Tank
 * @addtogroup Character
 */
TEST(TankCharacterTest, GetClassNameReturnsCorrectValue) {
    Tank_Character tank;
    EXPECT_EQ(tank.get_class_name(), "Tank");
}

// ==================== Healer_Character Serialization Tests ====================

/**
 * @test Verify serialization and deserialization maintains heal_amount
 * @addtogroup HealerCharacter
 */
TEST(HealerCharacterTest, SerializeDeserializeIntegrity) {
    // Arrange
    Healer_Character original(
        15,     // heal_amount
        200,    // xp_to_next_lvl
        3,      // lvl
        150,    // xp
        "Mercy", 
        1.5f,   // heal_mltpl
        1.0f,   // dmg_mltpl
        1.1f,   // armor_mltpl
        "Main healer",
        3       // ability_uses
    );
    
    // Act - Serialize
    std::stringstream ss;
    original.serialize(ss);
    
    // Act - Deserialize
    Healer_Character restored;
    restored.deserialize(ss);
    
    // Assert
    EXPECT_EQ(restored.get_heal_amount(), 3 * 10); // level * 10 logic
    EXPECT_EQ(restored.get_xp_to_next_lvl(), 200);
    EXPECT_EQ(restored.get_level(), 3);
    EXPECT_EQ(restored.get_xp(), 150);
    EXPECT_EQ(restored.get_name(), "Mercy");
    EXPECT_FLOAT_EQ(restored.get_heal_multiplier(), 1.5f);
    EXPECT_FLOAT_EQ(restored.get_dmg_multiplier(), 1.0f);
    EXPECT_FLOAT_EQ(restored.get_armor_multiplier(), 1.1f);
    EXPECT_EQ(restored.get_description(), "Main healer");
    EXPECT_EQ(restored.get_ability_uses(), 3); // Изменено в соответствии с логикой сериализации
}

/**
 * @test Verify deserialize uses level-based calculation
 * @addtogroup HealerCharacter
 */
TEST(HealerCharacterTest, DeserializeRecalculatesHealAmount) {
    // Arrange
    std::stringstream ss;
    {
        Healer_Character original(25, 100, 5, 0, "Test", 1.0f, 1.0f, 1.0f, "Test", 5);
        original.serialize(ss);
    }
    
    // Act
    Healer_Character restored;
    restored.deserialize(ss);
    
    // Assert
    EXPECT_EQ(restored.get_heal_amount(), 5 * 10); // level * 10
    EXPECT_EQ(restored.get_ability_uses(), 5); // Проверка исправленной логики
}

/**
 * @test Verify serialization throws on stream error
 * @addtogroup ErrorHandling
 */
TEST(HealerCharacterTest, SerializeInvalidStream) {
    Healer_Character healer;
    std::stringstream ss;
    ss.setstate(std::ios::failbit);
    
    EXPECT_THROW(healer.serialize(ss), std::ios_base::failure)
        << "Serialize should check stream state before writing";
}



// ==================== Knight_Character Serialization Tests ====================

/**
 * @test Verify serialization and deserialize recalculates armor values
 * @addtogroup KnightCharacter
 */
TEST(KnightCharacterTest, SerializeDeserializeArmorRecalculation) {
    // Arrange
    Knight_Character original(
        150,    // xp_to_next_lvl
        3,      // lvl
        100,    // xp
        "Sir Lancelot",
        1.2f,   // heal_mltpl
        1.5f,   // dmg_mltpl
        1.3f,   // armor_mltpl
        "Brave knight",
        2,      // ability_uses
        15,     // armor_up
        3       // armored_amount
    );
    
    // Act - Serialize
    std::stringstream ss;
    original.serialize(ss);
    
    // Act - Deserialize
    Knight_Character restored;
    restored.deserialize(ss);
    
    // Assert - Check recalculated values
    EXPECT_EQ(restored.get_armor_up(), 3 * 5 + 20); // level * 5 + 20
    EXPECT_EQ(restored.get_armored_amount(), 0);
    EXPECT_EQ(restored.get_level(), 3);
}

/**
 * @test Verify deserialize ignores stored armor values
 * @addtogroup KnightCharacter
 */
TEST(KnightCharacterTest, DeserializeOverridesArmorValues) {
    // Arrange
    std::stringstream ss;
    {
        Knight_Character original(
            100, 1, 0, "Test", 
            1.0f, 1.0f, 1.0f, "Test", 
            1, 999, 999 // Неправильные значения
        );
        original.serialize(ss);
    }
    
    // Act
    Knight_Character restored;
    restored.deserialize(ss);
    
    // Assert
    EXPECT_EQ(restored.get_armor_up(), 1 * 5 + 20); 
    EXPECT_EQ(restored.get_armored_amount(), 0);     
}

/**
 * @test Verify serialization handles stream errors
 * @addtogroup ErrorHandling
 */
TEST(KnightCharacterTest, SerializeStreamFailure) {
    Knight_Character knight;
    std::stringstream ss;
    ss.setstate(std::ios::badbit);
    
    EXPECT_THROW(knight.serialize(ss), std::ios_base::failure)
        << "need error";
}

/**
 * @test Verify deserialize handles stream errors
 * @addtogroup ErrorHandling
 */
TEST(KnightCharacterTest, DeserializeStreamFailure) {
    Knight_Character knight;
    std::stringstream ss;
    
    // Generate invalid name length
    const size_t invalid_name_len = 1000;
    ss.write(reinterpret_cast<const char*>(&invalid_name_len), sizeof(invalid_name_len));
    ss.seekg(0);

    EXPECT_THROW(knight.deserialize(ss), std::ios_base::failure)
        << "Must throw on invalid name length";
}

// ==================== Tank_Character Serialization Tests ====================

/**
 * @test Verify serialization/deserialization integrity for Tank_Character
 * @addtogroup TankCharacter
 */
TEST(TankCharacterTest, SerializeDeserializeIntegrity) {
    // Arrange
    Tank_Character original(
        150,    // xp_to_next_lvl
        3,      // lvl
        100,    // xp
        "Ironclad",
        1.1f,   // heal_mltpl
        1.0f,   // dmg_mltpl
        1.5f,   // armor_mltpl
        "Heavy defender",
        2,      // ability_uses
        8       // shield_add
    );
    
    // Act - Serialize
    std::stringstream ss;
    original.serialize(ss);
    
    // Act - Deserialize
    Tank_Character restored;
    restored.deserialize(ss);
    
    EXPECT_EQ(restored.get_ability_uses(), 2)
        << "Ability uses must be preserved during deserialization";
    EXPECT_EQ(restored.get_shield_add(), 3 + 5)
        << "Shield add should be recalculated as level + 5";
    EXPECT_FALSE(restored.get_was_ability_used())
        << "Ability flag must be reset";
}

TEST(TankCharacterTest, DeserializeCorruptedData) {
    Tank_Character tank;
    std::stringstream ss;
    
    // Generate invalid name length
    const size_t invalid_name_len = 1000;
    ss.write(reinterpret_cast<const char*>(&invalid_name_len), sizeof(invalid_name_len));
    ss.seekg(0);

    EXPECT_THROW(tank.deserialize(ss), std::ios_base::failure)
        << "Must throw on invalid name length";
}




// ==================== AI_Player Method Tests ====================

/**
 * @test Verify calculation of card value for Attack_Spell_Card
 * @addtogroup AI_Player
 */
TEST(AIPlayerTest, CalculateAttackSpellValue) {
    AI_Player player(100, 10, 50, "TestAI");
    player.set_cumulative_attack_multiplier(2.0f);
    Attack_Spell_Card card("Fireball", "Deals damage", Rarity::Common, 3, Element::Fire, 10);
    
    EXPECT_EQ(player.calculate_card_value(card), 20) 
        << "Attack spell value should be base damage * attack multiplier";
}

/**
 * @test Verify calculation of card value for Beast_Card
 * @addtogroup AI_Player
 */
TEST(AIPlayerTest, CalculateBeastValue) {
    AI_Player player(100, 10, 50, "TestAI");
    player.set_cumulative_weapon_bonus(5);
    Beast_Card card("Wolf", "Fierce", Rarity::Common, 3, 8, Tribe::North);
    
    EXPECT_EQ(player.calculate_card_value(card), 13) 
        << "Beast value should be base damage + weapon bonus";
}

/**
 * @test Verify calculation of card value for Heal_Spell_Card
 * @addtogroup AI_Player
 */
TEST(AIPlayerTest, CalculateHealSpellValue) {
    AI_Player player(100, 10, 50, "TestAI");
    player.set_cumulative_heal_multiplier(1.5f);
    Heal_Spell_Card card("Cure", "Heals", Rarity::Common, 2, Element::Water, 20, 1.0f);
    
    EXPECT_EQ(player.calculate_card_value(card), 30) 
        << "Heal spell value should be base heal * heal multiplier";
}

/**
 * @test Verify calculation of card value for Buff_Spell_Card
 * @addtogroup AI_Player
 */
TEST(AIPlayerTest, CalculateBuffSpellValue) {
    Buff_Spell_Card card("Boost", "Improves", Rarity::Uncommon, 2, Element::Earth, 1.8f);
    AI_Player player;
    
    EXPECT_EQ(player.calculate_card_value(card), 18) 
        << "Buff spell value should be multiplier * 10";
}

// ==================== find_best_combination Tests ====================

/**
 * @test Verify selection of best attack + buff combination
 * @addtogroup AI_Player
 */
TEST(AIPlayerTest, SelectBestAttackBuffCombo) {
    AI_Player player(100, 10, 7, "TestAI"); // Total mana = 7
    
    // Setup hand with various cards
    player.get_hand().add_card(std::make_unique<Attack_Spell_Card>(
        "Fire", "Dmg", Rarity::Common, 3, Element::Fire, 10)); // Value: 10
    player.get_hand().add_card(std::make_unique<Buff_Spell_Card>(
        "Boost", "Buff", Rarity::Common, 2, Element::Earth, 1.5f)); // Value: 15
    player.get_hand().add_card(std::make_unique<Shield_Card>(
        "Shield", "Def", Rarity::Common, 4, 3)); // Value: 0
    
    auto result = player.find_best_combination();
    EXPECT_EQ(result.first, 0) << "Should select Attack spell (cost 3)";
    EXPECT_EQ(result.second, 1) << "Should select Buff spell (cost 2)";
}

/**
 * @test Verify fallback to single card when mana is limited
 * @addtogroup AI_Player
 */
TEST(AIPlayerTest, SelectSingleCardWhenManaLimited) {
    AI_Player player(100, 10, 4, "TestAI");
    
    player.get_hand().add_card(std::make_unique<Attack_Spell_Card>(
        "Fire", "Dmg", Rarity::Common, 5, Element::Fire, 10)); // Too expensive
    player.get_hand().add_card(std::make_unique<Heal_Spell_Card>(
        "Cure", "Heal", Rarity::Common, 3, Element::Water, 15, 1.0f)); // Cost 3
    
    auto result = player.find_best_combination();
    EXPECT_EQ(result.first, 1) << "Should select Heal spell as only affordable option";
    EXPECT_EQ(result.second, -1) << "Should not select second card";
}

/**
 * @test Verify combat cards are prioritized
 * @addtogroup AI_Player
 */
TEST(AIPlayerTest, PreferCombatCardsFirst) {
    AI_Player player(100, 10, 10, "TestAI");
    
    player.get_hand().add_card(std::make_unique<Buff_Spell_Card>(
        "Boost", "Buff", Rarity::Common, 2, Element::Earth, 1.5f));
    player.get_hand().add_card(std::make_unique<Attack_Spell_Card>(
        "Fire", "Dmg", Rarity::Common, 5, Element::Fire, 20));
    
    auto result = player.find_best_combination();
    EXPECT_EQ(result.first, 1) << "Should prioritize Attack spell over Buff";
}

/**
 * @test Verify (-1, -1) is returned when no valid cards exist
 * @addtogroup AI_Player
 */
TEST(AIPlayerTest, NoValidCardsReturnsInvalid) {
    AI_Player player(100, 2, 0, "TestAI"); // Fixed: mana=2, armor=0
    
    player.get_hand().add_card(std::make_unique<Attack_Spell_Card>(
        "Fire", "Dmg", Rarity::Common, 3, Element::Fire, 10)); // Cost 3 > 2
    
    auto result = player.find_best_combination();
    EXPECT_EQ(result.first, -1) << "Should return -1 when no cards are affordable";
    EXPECT_EQ(result.second, -1) << "Should return -1 when no second card is possible";
}





// ==================== Human_Player Tests ====================

/**
 * @test Verify adding characters to Human_Player
 * @addtogroup HumanPlayer
 */
TEST(HumanPlayerTest, AddCharacter) {
    Human_Player player;
    auto healer = std::make_unique<Healer_Character>();
    auto knight = std::make_unique<Knight_Character>();
    
    EXPECT_EQ(player.get_characters().size(), 0);
    
    player.add_character(std::move(healer));
    EXPECT_EQ(player.get_characters().size(), 1);
    
    player.add_character(std::move(knight));
    EXPECT_EQ(player.get_characters().size(), 2);
}

/**
 * @test Verify saving and loading characters
 * @addtogroup HumanPlayer
 */
TEST(HumanPlayerTest, SaveAndLoadCharacters) {
    const std::string filename = "test_save.bin";
    
    // Create player and add characters
    Human_Player player;
    player.add_character(std::make_unique<Healer_Character>());
    player.add_character(std::make_unique<Knight_Character>());
    player.add_character(std::make_unique<Tank_Character>());
    
    // Save characters
    player.save_characters(filename);
    
    // Load characters into a new player
    Human_Player loaded_player;
    loaded_player.load_characters(filename);
    
    // Verify loaded characters
    EXPECT_EQ(loaded_player.get_characters().size(), 3);
    
    // Check types of loaded characters
    bool found_healer = false;
    bool found_knight = false;
    bool found_tank = false;
    
    for (const auto& char_ptr : loaded_player.get_characters()) {
        if (dynamic_cast<Healer_Character*>(char_ptr.get())) {
            found_healer = true;
        } else if (dynamic_cast<Knight_Character*>(char_ptr.get())) {
            found_knight = true;
        } else if (dynamic_cast<Tank_Character*>(char_ptr.get())) {
            found_tank = true;
        }
    }
    
    EXPECT_TRUE(found_healer);
    EXPECT_TRUE(found_knight);
    EXPECT_TRUE(found_tank);
    
    // Clean up test file
    std::remove(filename.c_str());
}


/**
 * @test Verify showing characters information
 * @addtogroup HumanPlayer
 */
TEST(HumanPlayerTest, ShowCharacters) {
    Human_Player player;
    player.add_character(std::make_unique<Healer_Character>());
    player.add_character(std::make_unique<Knight_Character>());
    
    testing::internal::CaptureStdout();
    player.show_characters();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Available characters") != std::string::npos);
    EXPECT_TRUE(output.find("Healer") != std::string::npos);
    EXPECT_TRUE(output.find("Knight") != std::string::npos);
}



// ==================== Test Runner ====================

/**
 * @brief Test entry point
 */
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}