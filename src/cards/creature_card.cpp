/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/creature_card.h"
#include "../../include/player/player.h"
#include "../../include/player/character.h"

#include <stdexcept>
#include <iostream>

Creature_Card::Creature_Card(const std::string& name, const std::string& description,
                             Rarity rarity, int mana_cost, int base_dmg, float weapon_multiplier)
    : Card(name, description, rarity, mana_cost), base_dmg(base_dmg), weapon_multiplier(weapon_multiplier)
{
    if (base_dmg <= 0)
    {
        throw std::invalid_argument("Base damage must be positive");
    }
    if (weapon_multiplier <= 0)
    {
        throw std::invalid_argument("Weapon multiplier must be positive");
    }
}

int Creature_Card::get_base_dmg() const
{
    return base_dmg;
}

void Creature_Card::set_base_dmg(int new_dmg)
{
    if (new_dmg <= 0)
    {
        throw std::invalid_argument("Base damage must be positive");
    }
    base_dmg = new_dmg;
}

float Creature_Card::get_weapon_multiplier() const
{
    return weapon_multiplier;
}

void Creature_Card::set_weapon_multiplier(float new_multiplier)
{
    if (new_multiplier <= 0)
    {
        throw std::invalid_argument("Weapon multiplier must be positive");
    }
    weapon_multiplier = new_multiplier;
}

void Creature_Card::use(Player& user, Player& target)
{
    /**
     * @brief Summons creature
     */
    int total_power = static_cast<int>((get_base_dmg() +(get_weapon_multiplier() * user.get_cumulative_weapon_bonus()))*user.get_cumulative_attack_multiplier());
    target.take_damage(total_power);

    user.end_turn();


}

CardType Creature_Card::get_type() const
{
    return CardType::Creature;
}


void Creature_Card::generate_properties()
{
    // Generate random rarity first
    Rarity random_rarity = generate_random_rarity();
    set_rarity(random_rarity);

    std::uniform_int_distribution<int> name_dist(0, creature_names.size() - 1);
    std::uniform_int_distribution<int> desc_dist(0, creature_descriptions.size() - 1);

    set_name(creature_names[name_dist(rng)]);
    set_description(creature_descriptions[desc_dist(rng)]);

    switch (get_rarity())
    {
    case Rarity::Common:
        base_dmg = 2 + static_cast<int>(rng() % 3);
        weapon_multiplier = 1.0f + static_cast<float>(rng() % 3) * 0.1f;
        mana_cost = 1 + static_cast<int>(rng() % 2);
        break;
    case Rarity::Uncommon:
        base_dmg = 3 + static_cast<int>(rng() % 4);
        weapon_multiplier = 1.2f + static_cast<float>(rng() % 5) * 0.1f;
        mana_cost = 1 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Rare:
        base_dmg = 5 + static_cast<int>(rng() % 5);
        weapon_multiplier = 1.5f + static_cast<float>(rng() % 7) * 0.1f;
        mana_cost = 2 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Epic:
        base_dmg = 8 + static_cast<int>(rng() % 6);
        weapon_multiplier = 1.8f + static_cast<float>(rng() % 11) * 0.1f;
        mana_cost = 2 + static_cast<int>(rng() % 5);
        break;
    }
}

void Creature_Card::print_key_info() const
{
    std::cout << "Base Damage: " << base_dmg << ", Weapon Multiplier: " << weapon_multiplier;
}