/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/player/character.h"

Character::Character() 
    : xp_to_next_lvl(100), lvl(1), xp(0), name(""), heal_mltpl(1.0f), dmg_mltpl(1.0f), armor_mltpl(1.0f),
      description(""), ability_uses(3)  {}

Character::Character(const std::string& name, const std::string& description) {
    set_name(name);
    set_description(description);
    xp_to_next_lvl = 100;
    lvl = 1;
    xp = 0;
    heal_mltpl = 1.0f;
    dmg_mltpl = 1.0f;
    armor_mltpl = 1.0f;
    ability_uses =3;
    
}

Character::Character(int xp_to_next_lvl, int lvl, int xp, const std::string& name, float heal_mltpl, float dmg_mltpl,
                     float armor_mltpl, const std::string& description, int ability_uses
                     ) {
    set_xp_to_next_lvl(xp_to_next_lvl);
    set_level(lvl);
    set_xp(xp);
    set_name(name);
    set_heal_multiplier(heal_mltpl);
    set_dmg_multiplier(dmg_mltpl);
    set_armor_multiplier(armor_mltpl);
    set_description(description);
    set_ability_uses(ability_uses);
    
}

void Character::lvl_up() {
    lvl += 1;
    xp -= xp_to_next_lvl;
    heal_mltpl += 0.05f;
    dmg_mltpl += 0.05f;
    armor_mltpl += 0.05f;
    xp_to_next_lvl = static_cast<int>(xp_to_next_lvl * 1.2);
    
    if (xp >= xp_to_next_lvl) {
        lvl_up();
    }
}

int Character::get_xp() const { 
    return xp; 
}

void Character::set_xp(int value) {
    if (value < 0) {
        throw std::invalid_argument("XP cannot be negative");
    }
    xp = value;
    if (xp >= xp_to_next_lvl) {
        lvl_up();
    }
}

std::string Character::get_name() const {
    return name;
}

void Character::set_name(const std::string& value) {
    if (value.length() > 50) {
        throw std::invalid_argument("Name cannot be longer than 50 characters");
    }
    name = value;
}

float Character::get_heal_multiplier() const {
    return heal_mltpl;
}

void Character::set_heal_multiplier(float value) {
    if (value <= 0) {
        throw std::invalid_argument("Healing multiplier must be greater than 0");
    }
    heal_mltpl = value;
}

float Character::get_dmg_multiplier() const {
    return dmg_mltpl;
}

void Character::set_dmg_multiplier(float value) {
    if (value <= 0) {
        throw std::invalid_argument("Damage multiplier must be greater than 0");
    }
    dmg_mltpl = value;
}

float Character::get_armor_multiplier() const {
    return armor_mltpl;
}

void Character::set_armor_multiplier(float value) {
    if (value <= 0) {
        throw std::invalid_argument("Armor multiplier must be greater than 0");
    }
    armor_mltpl = value;
}

std::string Character::get_description() const {
    return description;
}

void Character::set_description(const std::string& value) {
    if (value.length() > 200) {
        throw std::invalid_argument("Description cannot be longer than 200 characters");
    }
    description = value;
}

int Character::get_xp_to_next_lvl() const {
    return xp_to_next_lvl;
}

void Character::set_xp_to_next_lvl(int value) {
    if (value <= 0) {
        throw std::invalid_argument("XP to next level must be greater than 0");
    }
    xp_to_next_lvl = value;
}

int Character::get_level() const {
    return lvl;
}

void Character::set_level(int value) {
    if (value <= 0) {
        throw std::invalid_argument("Level must be greater than 0");
    }
    lvl = value;
}

void Character::add_xp(int amount) {
    if (amount < 0) {
        throw std::invalid_argument("XP amount to add cannot be negative");
    }
    set_xp(get_xp() + amount);
}

int Character::get_ability_uses() const {
    return ability_uses;
}

void Character::set_ability_uses(int value) {
    if (value < 0) {
        throw std::invalid_argument("Ability uses cannot be negative");
    }
    ability_uses = value;
}



