/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/player/hand.h"
#include "../../include/cards/shield_card.h"
#include "../../include/cards/buff_card.h"
#include "../../include/cards/heal_spell_card.h"
#include "../../include/cards/creature_card.h"
#include "../../include/cards/weapon_card.h"
#include "../../include/cards/attack_spell_card.h"
#include "../../include/cards/defence_spell_card.h"
#include "../../include/cards/beast_card.h"
#include "../../include/cards/artifact_card.h"
#include "../../include/cards/buff_spell_card.h"
#include <stdexcept>
#include <algorithm>

Hand::Hand() : amount(0) {}

void Hand::add_card(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
    amount++;
}

void Hand::remove_card(int index) {
        if (index < 0 || index >= static_cast<int>(cards.size())) {
            throw std::out_of_range("Invalid card index");
        }
        cards.erase(cards.begin() + index);
        amount = static_cast<int>(cards.size());
    }

Card& Hand::get_card(int index) const {
        if (index < 0 || index >= static_cast<int>(cards.size())) {
            throw std::out_of_range("Invalid card index");
        }
        return *cards[index];
    }

void Hand::sort_by_mana() {
    std::sort(cards.begin(), cards.end(),
        [](const std::unique_ptr<Card>& a, const std::unique_ptr<Card>& b) {
            return a->get_mana_cost() > b->get_mana_cost();
        });
}

void Hand::generate(int id) {
    cards.clear();
    amount = 0;
    
    switch (id) {
        case 1:
            create_standard_hand_1();
            break;
        case 2:
            create_standard_hand_2();
            break;
        case 3:
            create_standard_hand_3();
            break;
        case 4: {
            int num_cards = 15 + (rng() % 6); // Generates 15-20 inclusive
            for (int i = 0; i < num_cards; ++i) {
                generate_random_card();
            }
            break;
        }
        default:
            throw std::invalid_argument("Invalid hand ID");
    }
}

int Hand::get_amount() const {
    return amount;
}

std::vector<std::string> Hand::get_unique_card_types() const {
    std::vector<std::string> types;
    for (const auto& card : cards) {
        std::string type = typeid(*card).name();
        if (std::find(types.begin(), types.end(), type) == types.end()) {
            types.push_back(type);
        }
    }
    return types;
}

std::vector<std::reference_wrapper<Card>> Hand::get_cards_by_type(const std::string& type_name) const {
    std::vector<std::reference_wrapper<Card>> result;
    for (const auto& card : cards) {
        if (typeid(*card).name() == type_name) {
            result.push_back(std::ref(*card));
        }
    }
    return result;
}

// Implementation of standard hands
void Hand::create_standard_hand_1() {
    add_card(std::make_unique<Shield_Card>("Basic Shield", "Provides basic protection", Rarity::Common, 2, 3));
    add_card(std::make_unique<Buff_Card>("Power Boost", "Increases attack power", Rarity::Common, 3, 1.5f));
    add_card(std::make_unique<Beast_Card>("Wild Boar", "Basic beast attack", Rarity::Common, 2, 4, Tribe::North));
    add_card(std::make_unique<Shield_Card>("Minor Ward", "Small protective ward", Rarity::Uncommon, 3, 2));
    add_card(std::make_unique<Buff_Card>("Quickening", "Slight speed increase", Rarity::Common, 2, 1.2f));
    add_card(std::make_unique<Weapon_Card>("Bronze Sword", "Simple weapon", Rarity::Common, 2, 3));
    add_card(std::make_unique<Heal_Spell_Card>("Small Heal", "Restores minor HP", Rarity::Common, 2, Element::Water, 5, 1.0f));
    add_card(std::make_unique<Creature_Card>("Goblin Thug", "Weak creature", Rarity::Common, 3, 4, 1.1f));
    add_card(std::make_unique<Attack_Spell_Card>("Firebolt", "Basic fire damage", Rarity::Common, 3, Element::Fire, 6));
    add_card(std::make_unique<Shield_Card>("Wooden Buckler", "Basic wooden shield", Rarity::Common, 2, 2));
    add_card(std::make_unique<Buff_Card>("Minor Fortification", "Slight defense increase", Rarity::Uncommon, 3, 1.3f));
    add_card(std::make_unique<Weapon_Card>("Iron Dagger", "Basic dagger", Rarity::Uncommon, 2, 5));
    add_card(std::make_unique<Heal_Spell_Card>("Swift Mend", "Quick minor healing", Rarity::Uncommon, 3, Element::Water, 8, 1.1f));
    add_card(std::make_unique<Beast_Card>("Rabid Wolf", "Faster beast attack", Rarity::Uncommon, 3, 5, Tribe::West));
    add_card(std::make_unique<Shield_Card>("Traveler's Cloak", "Portable protection", Rarity::Uncommon, 3, 3));
}

void Hand::create_standard_hand_2() {
    add_card(std::make_unique<Shield_Card>("Advanced Shield", "Strong protection", Rarity::Rare, 4, 5));
    add_card(std::make_unique<Buff_Card>("Mega Boost", "Greatly increases power", Rarity::Rare, 5, 2.5f));
    add_card(std::make_unique<Weapon_Card>("Steel Longsword", "Balanced weapon", Rarity::Uncommon, 4, 7));
    add_card(std::make_unique<Heal_Spell_Card>("Moderate Heal", "Restores moderate HP", Rarity::Uncommon, 3, Element::Water, 12, 1.2f));
    add_card(std::make_unique<Creature_Card>("Orc Marauder", "Strong creature", Rarity::Uncommon, 4, 6, 1.3f));
    add_card(std::make_unique<Attack_Spell_Card>("Frost Nova", "Ice damage to multiple enemies", Rarity::Rare, 5, Element::Water, 12));
    add_card(std::make_unique<Shield_Card>("Iron Barrier", "Metallic shield", Rarity::Uncommon, 4, 4));
    add_card(std::make_unique<Buff_Card>("Strength Surge", "Temporary attack boost", Rarity::Rare, 4, 2.0f));
    add_card(std::make_unique<Weapon_Card>("Mythril Axe", "Advanced weapon", Rarity::Rare, 5, 10));
    add_card(std::make_unique<Heal_Spell_Card>("Sacred Blessing", "Holy healing", Rarity::Rare, 4, Element::Water, 18, 1.3f));
    add_card(std::make_unique<Creature_Card>("Phoenix Hatchling", "Fire-based creature", Rarity::Rare, 6, 8, 1.5f));
    add_card(std::make_unique<Attack_Spell_Card>("Thunder Strike", "Lightning damage", Rarity::Rare, 5, Element::Air, 15));
    add_card(std::make_unique<Shield_Card>("Royal Guard Shield", "Decorative but effective", Rarity::Rare, 5, 6));
    add_card(std::make_unique<Buff_Card>("Battle Fury", "Frenzy attack mode", Rarity::Rare, 5, 2.2f));
}

void Hand::create_standard_hand_3() {
    add_card(std::make_unique<Buff_Card>("Ultra Boost", "Massive power increase", Rarity::Epic, 6, 3.5f));
    add_card(std::make_unique<Artifact_Card>("Amulet of Majesty", "Enhances all attributes", Rarity::Epic, 7, 1.7f));
    add_card(std::make_unique<Defence_Spell_Card>("Diamond Skin", "Hardened defense", Rarity::Epic, 8, Element::Earth, 10));
    add_card(std::make_unique<Heal_Spell_Card>("Great Heal", "Restores significant HP", Rarity::Rare, 5, Element::Water, 25, 1.5f));
    add_card(std::make_unique<Creature_Card>("Ancient Beast", "Powerful creature", Rarity::Epic, 9, 12, 1.4f));
    add_card(std::make_unique<Weapon_Card>("Arcane Blade", "Elemental weapon", Rarity::Epic, 7, 15));
    add_card(std::make_unique<Buff_Spell_Card>("Battle Cry", "Temporary attack boost", Rarity::Rare, 4, Element::Air, 2.0f));
    add_card(std::make_unique<Shield_Card>("Legendary Shield", "Best protection", Rarity::Uncommon, 7, 10));
    add_card(std::make_unique<Artifact_Card>("Ring of Power", "Concentrates magical energy", Rarity::Epic, 8, 2.0f));
    add_card(std::make_unique<Defence_Spell_Card>("Astral Barrier", "Cosmic protection", Rarity::Epic, 9, Element::Air, 15));
    add_card(std::make_unique<Heal_Spell_Card>("Eternal Life", "Restores full HP", Rarity::Epic, 10, Element::Water, 50, 2.0f));
    add_card(std::make_unique<Creature_Card>("Dragonspawn", "Fire-breathing creature", Rarity::Epic, 10, 15, 1.8f));
    add_card(std::make_unique<Weapon_Card>("Oblivion Edge", "Legendary weapon", Rarity::Epic, 9, 20));
}

void Hand::generate_random_card() {
    int random = rng() % 100; // Generates a number between 0 and 99

    // Define probability ranges for each card type
    if (random < 10) { // 10% chance for Beast Card
        auto card = std::make_unique<Beast_Card>("Wild Boar", "Basic beast attack", Rarity::Common, 2, 4, Tribe::North);
        card->generate_properties();
        add_card(std::move(card));
    } else if (random < 20) { // 10% chance for Buff Card
        auto card = std::make_unique<Buff_Card>("Power Boost", "Increases attack power", Rarity::Common, 3, 1.5f);
        card->generate_properties();
        add_card(std::move(card));
    } else if (random < 30) { // 10% chance for Creature Card
        auto card = std::make_unique<Creature_Card>("Goblin Warrior", "Weak creature", Rarity::Common, 3, 4, 1.1f);
        card->generate_properties();
        add_card(std::move(card));
    } else if (random < 40) { // 10% chance for Shield Card
        auto card = std::make_unique<Shield_Card>("Basic Shield", "Provides basic protection", Rarity::Common, 2, 3);
        card->generate_properties();
        add_card(std::move(card));
    } else if (random < 50) { // 10% chance for Weapon Card
        auto card = std::make_unique<Weapon_Card>("Bronze Sword", "Simple weapon", Rarity::Common, 2, 3);
        card->generate_properties();
        add_card(std::move(card));
    } else if (random < 60) { // 10% chance for Artifact Card
        auto card = std::make_unique<Artifact_Card>("Amulet of Majesty", "Enhances all attributes", Rarity::Epic, 7, 1.7f);
        card->generate_properties();
        add_card(std::move(card));
    } else if (random < 70) { // 10% chance for Attack Spell Card
        auto card = std::make_unique<Attack_Spell_Card>("Firebolt", "Basic fire damage", Rarity::Common, 3, Element::Fire, 6);
        card->generate_properties();
        add_card(std::move(card));
    } else if (random < 80) { // 10% chance for Heal Spell Card
        auto card = std::make_unique<Heal_Spell_Card>("Small Heal", "Restores minor HP", Rarity::Common, 2, Element::Water, 5, 1.0f);
        card->generate_properties();
        add_card(std::move(card));
    } else if (random < 90) { // 10% chance for Buff Spell Card
        auto card = std::make_unique<Buff_Spell_Card>("Battle Cry", "Temporary attack boost", Rarity::Rare, 4, Element::Air, 2.0f);
        card->generate_properties();
        add_card(std::move(card));
    } else { // 10% chance for Defence Spell Card
        auto card = std::make_unique<Defence_Spell_Card>("Iron Skin", "Hardened defense", Rarity::Common, 2, Element::Earth, 3);
        card->generate_properties();
        add_card(std::move(card));
    }
}