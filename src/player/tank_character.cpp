/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/player/tank_character.h"
#include "../../include/player/player.h"
#include <stdexcept>

Tank_Character::Tank_Character() 
    : Character(), shield_add(2), was_ability_used(false) {}

Tank_Character::Tank_Character(int xp_to_next_lvl, int lvl, int xp, 
                               const std::string& name, float heal_mltpl, float dmg_mltpl,
                               float armor_mltpl, const std::string& description, 
                               int ability_uses, int shield_add)
    : Character(xp_to_next_lvl, lvl, xp, name, heal_mltpl, dmg_mltpl, armor_mltpl, description, ability_uses),
      shield_add(shield_add), was_ability_used(false) {
    if (shield_add <= 0) {
        throw std::invalid_argument("Shield amount must be positive");
    }
}

int Tank_Character::get_shield_add() const {
    return shield_add;
}

void Tank_Character::set_shield_add(int value) {
    if (value <= 0) {
        throw std::invalid_argument("Shield amount must be positive");
    }
    shield_add = value;
}

void Tank_Character::special_action(Player& player) {
    if (this->get_ability_uses() == 0) {
        throw std::runtime_error("No ability uses remaining");
    }
    
    player.set_shield_amount(player.get_shield_amount() + shield_add);
    this->set_ability_uses(this->get_ability_uses() - 1);
    was_ability_used = true; 
}

void Tank_Character::special_action_info(){
    std::cout<<"Shield amount: "<<get_shield_add();
}

void Tank_Character::serialize(std::ostream& os) const {
    Character::serialize(os);
    int calculated_shield = get_level() + 5; // lvl +5
    bool reset_ability_flag = false; 
    os.write(reinterpret_cast<const char*>(&calculated_shield), sizeof(calculated_shield));
    os.write(reinterpret_cast<const char*>(&reset_ability_flag), sizeof(reset_ability_flag));
}

void Tank_Character::deserialize(std::istream& is) {
    Character::deserialize(is);
    is.read(reinterpret_cast<char*>(&shield_add), sizeof(shield_add));
    is.read(reinterpret_cast<char*>(&was_ability_used), sizeof(was_ability_used));
    shield_add = get_level() + 5;
    was_ability_used = false; 
}