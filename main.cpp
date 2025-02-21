#include <iostream>
#include "card.h"
#include "enums.h"

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

    return 0;
} 