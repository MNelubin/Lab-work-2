/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/player/player.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "../../include/player/character.h"
#include "../../include/player/tank_character.h"
#include "../../include/player/healer_character.h"
#include "../../include/player/knight_character.h"

Player::Player() 
    : hp(100), mana(50), armor(0), shield_amount(0) {}

Player::Player(int hp, int mana, int armor, const std::string& name, 
               std::unique_ptr<Character> character, int shield_amount)
    : character(std::move(character)),hp(hp), mana(mana), armor(armor), name(name), 
       shield_amount(shield_amount) {
    if (hp < 0 || mana < 0 || armor < 0 || shield_amount < 0) {
        throw std::invalid_argument("Player attributes cannot be negative");
    }
}

Player::Player(Player&& other) noexcept 
    : character(std::move(other.character)), hp(other.hp), mana(other.mana), 
      armor(other.armor), name(other.name), hand(std::move(other.hand)), 
      shield_amount(other.shield_amount) {}

Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        character = std::move(other.character);
        hp = other.hp;
        mana = other.mana;
        armor = other.armor;
        name = other.name;
        hand = std::move(other.hand);
        shield_amount = other.shield_amount;
    }
    return *this;
}

Player::~Player() {}

void Player::set_character(std::unique_ptr<Character> new_character) {
    character = std::move(new_character);
}

Character& Player::get_character() const {
    if (!character) {
        throw std::runtime_error("Character not set");
    }
    return *character;
}

void Player::perform_special_action() {
    if (!character) {
        throw std::runtime_error("Character not set");
    }
    character->special_action(*this);
}

void Player::show_hand() {
    std::cout << "Player's Hand:" << std::endl;
    for (int i = 0; i < hand.get_amount(); ++i) {
        const auto& card = hand.get_card(i);
        std::cout << "[" << i << "] " << card.get_name() << " (" 
                  << card.get_mana_cost() << " mana)" << std::endl;
    }
}

void Player::eat_card(int index) {
    if (index < 0 || index >= hand.get_amount()) {
        throw std::out_of_range("Invalid card index");
    }
    hand.remove_card(index);
    // Additional logic for "eating" a card can be added here
}

void Player::use_card(Player& target, int index) {
    if (index < 0 || index >= hand.get_amount()) {
        throw std::out_of_range("Invalid card index");
    }
    const auto& card = hand.get_card(index);
    // Add logic to apply the card's effect to the target player
    // This is a placeholder for actual card effect implementation
    std::cout << "Using card " << card.get_name() << " on " << target.get_name() << std::endl;
}

void Player::take_damage(int amount) {
    if (amount < 0) {
        throw std::invalid_argument("Damage amount cannot be negative");
    }
    ///REWrite
    hp -= amount;
    if (hp < 0) {
        hp = 0;
    }
}

void Player::throw_out(int index) {
    if (index < 0 || index >= hand.get_amount()) {
        throw std::out_of_range("Invalid card index");
    }
    hand.remove_card(index);
}

int Player::get_hp() const {
    return hp;
}

void Player::set_hp(int value) {
    if (value < 0) {
        throw std::invalid_argument("HP cannot be negative");
    }
    hp = value;
}

int Player::get_mana() const {
    return mana;
}

void Player::set_mana(int value) {
    if (value < 0) {
        throw std::invalid_argument("Mana cannot be negative");
    }
    mana = value;
}

int Player::get_armor() const {
    return armor;
}

void Player::set_armor(int value) {
    if (value < 0) {
        throw std::invalid_argument("Armor cannot be negative");
    }
    armor = value;
}

std::string Player::get_name() const {
    return name;
}

void Player::set_name(const std::string& Name) {
    if (Name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
    name = Name;
}

int Player::get_shield_amount() const {
    return shield_amount;
}

void Player::set_shield_amount(int value) {
    if (value < 0) {
        throw std::invalid_argument("Shield amount cannot be negative");
    }
    shield_amount = value;
}

std::string Player::get_character_statistics() const {
    if (!character) {
        throw std::runtime_error("Character not set");
    }
    std::stringstream ss;
    ss << "Character Statistics:\n"
       << "Name: " << character->get_name() << "\n"
       << "Level: " << character->get_level() << "\n"
       << "XP: " << character->get_xp() << "\n"
       << "Heal Multiplier: " << std::fixed << std::setprecision(2) << character->get_heal_multiplier() << "\n"
       << "Damage Multiplier: " << std::fixed << std::setprecision(2) << character->get_dmg_multiplier() << "\n"
       << "Armor Multiplier: " << std::fixed << std::setprecision(2) << character->get_armor_multiplier() << "\n"
       << "Description: " << character->get_description() << "\n"
       << "XP to Next Level: " << character->get_xp_to_next_lvl();
    return ss.str();
}