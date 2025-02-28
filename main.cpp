/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include <iostream>
#include "card.h"
#include "enums.h"
#include "spell_card.h"
#include "attack_spell_card.h"
#include "heal_spell_card.h"
#include "buff_spell_card.h"
#include "defence_spell_card.h"

void demonstrate_spell() {
    Spell_Card lightning("Lightning Bolt", "Deals 8 damage", 
                        Rarity::Rare, 6, Element::Air);
    
    std::cout << "\nSpell Demo:\n"
              << "Name: " << lightning.get_name() << "\n"
              << "Element: " << static_cast<int>(lightning.get_element()) << "\n"
              << "Mana Cost: " << lightning.get_mana_cost() << "\n";
    
    lightning.set_element(Element::Fire);
    std::cout << "Updated Element: " << static_cast<int>(lightning.get_element()) << "\n";
}

void demonstrate_attack_spell() {
    try {
        // Create attack spell
        Attack_Spell_Card fireball("Dragon's Breath", 
            "Deals fire damage to all enemies",
            Rarity::Epic, 6, Element::Fire, 8);
        
        // Display initial stats
        std::cout << "\n[Attack Spell Demo]\n"
                  << "Name: " << fireball.get_name() << "\n"
                  << "Damage: " << fireball.get_base_damage() << "\n"
                  << "Element: " << static_cast<int>(fireball.get_element()) << "\n";
        
        // Modify damage
        fireball.set_base_damage(12);
        std::cout << "Upgraded Damage: " << fireball.get_base_damage() << "\n";
        
        // Test invalid damage
        Attack_Spell_Card invalid("Broken Spell", "", 
            Rarity::Common, 1, Element::Water, -5);
    }
    catch(const std::exception& e) {
        std::cerr << "\nError: " << e.what() << "\n";
    }
}

void demonstrate_heal_spell() {
    try {
        // Create
        Heal_Spell_Card rejuvenation("Nature's Touch", 
            "Restores health to all allies",
            Rarity::Epic, 8, Element::Earth, 15, 1.5f);
        
        // Output values
        std::cout << "\n[Heal Spell Demo]\n"
                  << "Name: " << rejuvenation.get_name() << "\n"
                  << "Base Heal: " << rejuvenation.get_base_heal() << "\n"
                  << "Efficiency: " << rejuvenation.get_eff() << "\n"
                  << "Element: " << static_cast<int>(rejuvenation.get_element()) << "\n";
        
        // Modifying values
        rejuvenation.set_base_heal(25);
        rejuvenation.set_eff(2.0f);
        std::cout << "Upgraded Heal: " << rejuvenation.get_base_heal() << "\n"
                  << "Improved Efficiency: " << rejuvenation.get_eff() << "\n";
        
        // Constructor test
        Heal_Spell_Card invalid_heal("Broken Heal", "", 
            Rarity::Common, 2, Element::Water, -10, 0.5f);
            
        Heal_Spell_Card invalid_eff("No Effect", "", 
            Rarity::Rare, 3, Element::Air, 10, -1.0f);
    }
    catch(const std::exception& e) {
        std::cerr << "\nError: " << e.what() << "\n";
    }

    // Added setters checkup
    try {
        Heal_Spell_Card test("Test Spell", "", Rarity::Common, 1, Element::Fire, 5, 1.0f);
        test.set_base_heal(-5); 
    }
    catch(const std::exception& e) {
        std::cerr << "Setter Error: " << e.what() << "\n";
    }
}

void demonstrate_buff_spell() {
    try {
        // Create
        Buff_Spell_Card powerUp("Power Surge", 
            "Increases attack power of all allies",
            Rarity::Rare, 6, Element::Fire, 1.8f);
        
        // Output values
        std::cout << "\n[Buff Spell Demo]\n"
                  << "Name: " << powerUp.get_name() << "\n"
                  << "Multiplier: " << powerUp.get_multiplier() << "\n"
                  << "Element: " << static_cast<int>(powerUp.get_element()) << "\n";
        
        // Modifying values
        powerUp.set_multiplier(2.5f);
        std::cout << "Upgraded Multiplier: " << powerUp.get_multiplier() << "\n";
        
        // Constructor test
        Buff_Spell_Card invalid_buff("Broken Buff", "", 
            Rarity::Common, 2, Element::Water, -1.0f);
    }
    catch(const std::exception& e) {
        std::cerr << "\nError: " << e.what() << "\n";
    }

    // Added setters checkup
    try {
        Buff_Spell_Card test("Test Buff", "", Rarity::Common, 1, Element::Air, 1.0f);
        test.set_multiplier(0.0f); 
    }
    catch(const std::exception& e) {
        std::cerr << "Setter Error: " << e.what() << "\n";
    }
}
void demonstrate_defence_spell() {
    try {
        // Create
        Defence_Spell_Card shield("Shield Wall", 
            "Increases defense of all allies",
            Rarity::Rare, 4, Element::Earth, 5);
        
        // Output values
        std::cout << "\n[Defence Spell Demo]\n"
                  << "Name: " << shield.get_name() << "\n"
                  << "Base Defense: " << shield.get_base_def() << "\n"
                  << "Element: " << static_cast<int>(shield.get_element()) << "\n";
        
        // Modifying values
        shield.set_base_def(8);
        std::cout << "Upgraded Defense: " << shield.get_base_def() << "\n";
        
        // Constructor test
        Defence_Spell_Card invalid_def("Broken Shield", "", 
            Rarity::Common, 2, Element::Water, -1);
    }
    catch(const std::exception& e) {
        std::cerr << "\nError: " << e.what() << "\n";
    }

    // Added setters checkup
    try {
        Defence_Spell_Card test("Test Shield", "", Rarity::Common, 1, Element::Air, 5);
        test.set_base_def(0); 
    }
    catch(const std::exception& e) {
        std::cerr << "Setter Error: " << e.what() << "\n";
    }
}


int main() {
    // Create sample card
    Card fireball("Fireball", "Deals 5 damage", Rarity::Uncommon, 3);
    
    // Demonstrate accessors
    std::cout << "Card Name: " << fireball.get_name() << "\n"
              << "Mana Cost: " << fireball.get_mana_cost() << "\n"
              << "Rarity: " << static_cast<int>(fireball.get_rarity()) << "\n";
    
    // Test mutators
    fireball.set_mana_cost(4);
    std::cout << "Updated Mana Cost: " << fireball.get_mana_cost() << std::endl;

    demonstrate_spell();
    demonstrate_attack_spell();
    demonstrate_heal_spell();
    demonstrate_buff_spell();
    demonstrate_defence_spell();
    return 0;
} 