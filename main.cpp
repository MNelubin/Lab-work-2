#include <iostream>
#include "card.h"
#include "enums.h"
#include "spell_card.h"

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
    return 0;
} 