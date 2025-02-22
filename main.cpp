/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include <iostream>
#include "card.h"
#include "enums.h"
#include "spell_card.h"
#include "attack_spell_card.h"

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
    return 0;
} 