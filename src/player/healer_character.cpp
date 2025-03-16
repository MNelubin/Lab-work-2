/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/player/healer_character.h"
#include "../../include/player/player.h"
#include <stdexcept>

Healer_Character::Healer_Character() 
    : Character() ,heal_amount(10) {}

Healer_Character::Healer_Character(const std::string& name, const std::string& description):
    Character(name,description),heal_amount(10){}

Healer_Character::Healer_Character(int xp_to_next_lvl, int lvl, int xp, const std::string& name, float heal_mltpl, float dmg_mltpl,
                     float armor_mltpl, const std::string& description, int ability_uses
                     ):
                     Character(xp_to_next_lvl, lvl,  xp,  name, heal_mltpl, dmg_mltpl,
                     armor_mltpl,  description,  ability_uses),heal_amount(10){}

Healer_Character::Healer_Character(int heal_amount,int xp_to_next_lvl, int lvl, int xp, const std::string& name, float heal_mltpl, float dmg_mltpl,
                     float armor_mltpl, const std::string& description, int ability_uses
                     )
    : Character(xp_to_next_lvl, lvl, xp, name, heal_mltpl, dmg_mltpl,
                      armor_mltpl,  description,  ability_uses
                     ) , heal_amount(heal_amount) {
    if (heal_amount <= 0) {
        throw std::invalid_argument("Heal amount must be positive");
    }
    if (this->get_ability_uses() < 0) {
        throw std::invalid_argument("Ability uses cannot be negative");
    }
}

int Healer_Character::get_heal_amount() const {
    return heal_amount;
}

void Healer_Character::set_heal_amount(int value) {
    if (value <= 0) {
        throw std::invalid_argument("Heal amount must be positive");
    }
    heal_amount = value;
}

void Healer_Character::special_action(Player& player) {
    if (this->get_ability_uses() == 0) {
        throw std::runtime_error("No ability uses remaining");
    }
    player.set_hp(player.get_hp() + heal_amount*this->get_heal_multiplier());
    this->set_ability_uses(this->get_ability_uses()-1);
}

void Healer_Character::special_action_info(){
    std::cout<<"Heal amount: "<<get_heal_amount();
}


void Healer_Character::serialize(std::ostream& os) const {
    Character::serialize(os);
    int calculated_heal = get_level() * 10; // lvl * 10
    os.write(reinterpret_cast<const char*>(&calculated_heal), sizeof(calculated_heal));
}

void Healer_Character::deserialize(std::istream& is) {
    Character::deserialize(is);

    is.read(reinterpret_cast<char*>(&heal_amount), sizeof(heal_amount));
    heal_amount = get_level() * 10;
}