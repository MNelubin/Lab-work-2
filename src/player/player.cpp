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
    : hp(100), mana(50), armor(0), shield_amount(0),
      cumulative_attack_multiplier(1.0f), cumulative_heal_multiplier(1.0f),
      cumulative_weapon_adder(0), turn_active(true) {}

Player::Player(int hp, int mana, int armor, const std::string& name, 
               std::unique_ptr<Character> character, int shield_amount)
    : character(std::move(character)), hp(hp), mana(mana), armor(armor), name(name), 
      shield_amount(shield_amount), cumulative_attack_multiplier(1.0f),
      cumulative_heal_multiplier(1.0f), cumulative_weapon_adder(0),
      turn_active(true) {
    if (hp < 0 || mana < 0 || armor < 0 || shield_amount < 0) {
        throw std::invalid_argument("Player attributes cannot be negative");
    }
}

Player::Player(Player&& other) noexcept 
    : character(std::move(other.character)), hp(other.hp), mana(other.mana), 
      armor(other.armor), name(other.name), hand(std::move(other.hand)), 
      shield_amount(other.shield_amount), cumulative_attack_multiplier(other.cumulative_attack_multiplier),
      cumulative_heal_multiplier(other.cumulative_heal_multiplier),
      cumulative_weapon_adder(other.cumulative_weapon_adder),
      turn_active(other.turn_active) {}

Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        character = std::move(other.character);
        hp = other.hp;
        mana = other.mana;
        armor = other.armor;
        name = other.name;
        hand = std::move(other.hand);
        shield_amount = other.shield_amount;
        cumulative_attack_multiplier = other.cumulative_attack_multiplier;
        cumulative_heal_multiplier = other.cumulative_heal_multiplier;
        cumulative_weapon_adder = other.cumulative_weapon_adder;
        turn_active = other.turn_active;
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

    // Get the card from hand
    const Card& card = hand.get_card(index);

    // Get character's HP multiplier
    float hp_multiplier = get_character().get_heal_multiplier();

    // Calculate rarity value (Common=1, Uncommon=2, Rare=3, Epic=4)
    int rarity_value = static_cast<int>(card.get_rarity()) + 1;

    // Calculate HP increase with multiplier and convert to integer
    int hp_increase = static_cast<int>(rarity_value * 10 * hp_multiplier);

    // Update player's HP
    hp += hp_increase;

    // Remove the card from hand
    hand.remove_card(index);
}

void Player::use_card(int index, Player& target) {
    if (index < 0 || index >= hand.get_amount()) {
        throw std::out_of_range("Invalid card index");
    }

    // Get reference to the card before removal
    Card& card = hand.get_card(index);
    const CardType card_type = card.get_type();

    // Check mana cost
    int mana_cost = card.get_mana_cost();
    if (mana < mana_cost) {
        throw std::runtime_error("Not enough mana to use this card");
    }
    mana -= mana_cost;

    // Apply card effect
    card.use(*this, target);

    // Remove card from hand
    hand.remove_card(index);

    // Check if card type ends the player's turn
    if (card_type == CardType::AttackSpell ||
        card_type == CardType::HealSpell ||
        card_type == CardType::Beast) {
        this->end_turn();
    }
}

void Player::take_damage(int damage) {
    if (damage < 0) {
        throw std::invalid_argument("Damage cannot be negative");
    }

    int remaining_damage = damage;

    // Apply damage to shields first
    if (shield_amount > 0) {
        const int max_shield_absorb = shield_amount * 10;
        const int absorbed_by_shields = std::min(remaining_damage, max_shield_absorb);
        remaining_damage -= absorbed_by_shields;

        // Calculate number of shields used (ceiling division)
        const int shields_used = (absorbed_by_shields + 9) / 10;
        shield_amount = std::max(shield_amount - shields_used, 0);
    }

    if (remaining_damage <= 0) return;

    // Apply damage to armor next
    const int armor_absorb = std::min(remaining_damage, armor);
    remaining_damage -= armor_absorb;
    armor = std::max(armor - armor_absorb, 0);

    if (remaining_damage <= 0) return;

    // Apply remaining damage to HP
    hp = std::max(hp - remaining_damage, 0);
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

void Player::reset_turn() {
    cumulative_attack_multiplier = 1.0f;
    cumulative_heal_multiplier = 1.0f;
    cumulative_weapon_adder = 0;
    turn_active = true;
}

void Player::apply_attack_multiplier(float effect) {
    cumulative_attack_multiplier *= effect;
}

void Player::apply_heal_multiplier(float effect) {
    cumulative_heal_multiplier *= effect;
}

void Player::add_weapon_bonus(int effect) {
    cumulative_weapon_adder += effect;
}

void Player::end_turn() {
    reset_turn();
}

float Player::get_cumulative_attack_multiplier() const {
    return cumulative_attack_multiplier;
}

void Player::set_cumulative_attack_multiplier(float value) {
    if (value <= 0) {
        throw std::invalid_argument("Attack multiplier must be positive");
    }
    cumulative_attack_multiplier = value;
}

float Player::get_cumulative_heal_multiplier() const {
    return cumulative_heal_multiplier;
}

void Player::set_cumulative_heal_multiplier(float value) {
    if (value <= 0) {
        throw std::invalid_argument("Heal multiplier must be positive");
    }
    cumulative_heal_multiplier = value;
}

int Player::get_cumulative_weapon_bonus() const {
    return cumulative_weapon_adder;
}

void Player::set_cumulative_weapon_bonus(int value) {
    cumulative_weapon_adder = value;
}

bool Player::is_turn_active() const {
    return turn_active;
}

void Player::set_turn_active(bool value) {
    turn_active = value;
}

Hand& Player::get_hand() {
    return hand;
}

const Hand& Player::get_hand() const {
    return hand;
}

void Player::set_hand(Hand new_hand) {
    hand = std::move(new_hand);
}