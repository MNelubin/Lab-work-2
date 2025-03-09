/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/buff_card.h"
#include "../../include/player/player.h"

#include <stdexcept>
#include <iostream>

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

void Buff_Card::generate_properties() {
        // Generate random rarity first
        Rarity random_rarity = generate_random_rarity();
        set_rarity(random_rarity);
        
        std::uniform_int_distribution<int> name_dist(0, buff_names.size() - 1);
        std::uniform_int_distribution<int> desc_dist(0, buff_descriptions.size() - 1);
        
        set_name(buff_names[name_dist(rng)]);
        set_description(buff_descriptions[desc_dist(rng)]);
        
        switch (get_rarity()) {
            case Rarity::Common:
                buff_amount = 1.1f + static_cast<float>(rng() % 5) * 0.1f;
                mana_cost = 1 + static_cast<int>(rng() % 2);
                break;
            case Rarity::Uncommon:
                buff_amount = 1.3f + static_cast<float>(rng() % 8) * 0.1f;
                mana_cost = 1 + static_cast<int>(rng() % 3);
                break;
            case Rarity::Rare:
                buff_amount = 1.6f + static_cast<float>(rng() % 11) * 0.1f;
                mana_cost = 2 + static_cast<int>(rng() % 3);
                break;
            case Rarity::Epic:
                buff_amount = 2.0f + static_cast<float>(rng() % 16) * 0.1f;
                mana_cost = 2 + static_cast<int>(rng() % 5);
                break;
        }
    }

// Default constructor implementation
Buff_Card::Buff_Card()
    : Card("Unnamed Buff", "No description", Rarity::Common, 0), 
      buff_amount(1.0f) 
{
}

void Buff_Card::print_key_info() const {
    std::cout << "Buff Amount: " << buff_amount;
}