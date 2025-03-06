/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/buff_card.h"
#include "../../include/player/player.h"

#include <stdexcept>

Buff_Card::Buff_Card(const std::string& name, const std::string& description,
                     Rarity rarity, int mana_cost, float buff_amount)
    : Card(name, description, rarity, mana_cost), buff_amount(buff_amount) 
{
    if (buff_amount <= 0) {
        throw std::invalid_argument("Buff amount must be positive");
    }
}

float Buff_Card::get_buff_amount() const {
    return buff_amount;
}

void Buff_Card::set_buff_amount(float new_buff_amount) {
    if (new_buff_amount <= 0) {
        throw std::invalid_argument("Buff amount must be positive");
    }
    buff_amount = new_buff_amount;
} 

void Buff_Card::use(Player& user, Player& target) {
    /**
     * @brief Apply attack/defense multiplier
     */
    user.apply_attack_multiplier(get_buff_amount());
    user.apply_heal_multiplier(get_buff_amount());
}

CardType Buff_Card::get_type() const {
    return CardType::Buff;
}