/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/player/knight_character.h"
#include "../../include/player/player.h"
#include <stdexcept>

Knight_Character::Knight_Character() 
    : Character(), armor_up(5), armored_amount(0) {}

Knight_Character::Knight_Character(int xp_to_next_lvl, int lvl, int xp, 
                                   const std::string& name, float heal_mltpl, float dmg_mltpl,
                                   float armor_mltpl, const std::string& description, 
                                   int ability_uses, int armor_up, int armored_amount)
    : Character(xp_to_next_lvl, lvl, xp, name, heal_mltpl, dmg_mltpl, armor_mltpl, description, ability_uses),
      armor_up(armor_up), armored_amount(armored_amount) {
    if (armor_up < 0) {
        throw std::invalid_argument("Armor up must be positive");
    }
    if (armored_amount < 0) {
        throw std::invalid_argument("Armored amount cannot be negative");
    }
}

int Knight_Character::get_armor_up() const {
    return armor_up;
}

void Knight_Character::set_armor_up(int value) {
    if (value < 0) {
        throw std::invalid_argument("Armor up must be positive");
    }
    armor_up = value;
}

int Knight_Character::get_armored_amount() const {
    return armored_amount;
}

void Knight_Character::set_armored_amount(int value) {
    if (value < 0) {
        throw std::invalid_argument("Armored amount cannot be negative");
    }
    armored_amount = value;
}

void Knight_Character::special_action(Player& player) {
    if (get_ability_uses() == 0) {
        throw std::runtime_error("No ability uses remaining");
    }
    
    int armor_to_add = armor_up * get_armor_multiplier();
    player.set_armor(player.get_armor() + armor_to_add - get_armored_amount());
    this->set_ability_uses(get_ability_uses() - 1);
    this->set_armored_amount(armored_amount + 1); // Увеличиваем armored_amount
}

void Knight_Character::special_action_info(){
    std::cout<<"Armor up amount: "<<get_armor_up()-get_armored_amount();
}


void Knight_Character::serialize(std::ostream& os) const {
    Character::serialize(os);
    int calculated_armor = get_level() * 5 + 20; // lvl *5 +20
    int reset_armored = 0; 
    os.write(reinterpret_cast<const char*>(&calculated_armor), sizeof(calculated_armor));
    os.write(reinterpret_cast<const char*>(&reset_armored), sizeof(reset_armored));
}

void Knight_Character::deserialize(std::istream& is) {
    Character::deserialize(is);
    is.read(reinterpret_cast<char*>(&armor_up), sizeof(armor_up));
    is.read(reinterpret_cast<char*>(&armored_amount), sizeof(armored_amount));
    armor_up = get_level() * 5 + 20;
    armored_amount = 0; 
}