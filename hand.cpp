/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "hand.h"
#include "shield_card.h"
#include "buff_card.h"
#include <stdexcept>
#include <algorithm>

Hand::Hand() : amount(0) {}

void Hand::add_card(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
    amount++;
}

void Hand::remove_card(int index) {
    if (index < 0 || index >= amount) {
        throw std::out_of_range("Invalid card index");
    }
    cards.erase(cards.begin() + index);
    amount--;
}

Card& Hand::get_card(int index) const {
    if (index < 0 || index >= amount) {
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
    add_card(std::make_unique<Shield_Card>("Basic Shield", "Provides basic protection", 
              Rarity::Common, 2, 3));
    add_card(std::make_unique<Buff_Card>("Power Boost", "Increases attack power", 
              Rarity::Common, 3, 1.5f));
}

void Hand::create_standard_hand_2() {
    add_card(std::make_unique<Shield_Card>("Advanced Shield", "Strong protection", 
              Rarity::Rare, 4, 5));
    add_card(std::make_unique<Buff_Card>("Mega Boost", "Greatly increases power", 
              Rarity::Rare, 5, 2.5f));
    add_card(std::make_unique<Shield_Card>("Basic Shield", "Provides basic protection", 
              Rarity::Common, 2, 3));
}

void Hand::create_standard_hand_3() {
    add_card(std::make_unique<Buff_Card>("Ultra Boost", "Massive power increase", 
              Rarity::Epic, 6, 3.5f));
    add_card(std::make_unique<Buff_Card>("Ultra Boost", "Massive power increase", 
              Rarity::Epic, 6, 3.5f));
    add_card(std::make_unique<Shield_Card>("Legendary Shield", "Best protection", 
              Rarity::Uncommon, 7, 10));
} 