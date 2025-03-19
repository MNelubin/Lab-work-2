/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/beast_card.h"
#include "../../include/player/player.h"

#include <stdexcept>
#include <iostream>

Beast_Card::Beast_Card(const std::string& name, const std::string& description,
                       Rarity rarity, int mana_cost, int base_dmg, Tribe tribe)
    : Card(name, description, rarity, mana_cost), base_dmg(base_dmg), tribe(tribe)
{
    if (base_dmg <= 0)
    {
        throw std::invalid_argument("Base damage must be positive");
    }
}

// Default constructor implementation
Beast_Card::Beast_Card()
    : Card("Unnamed Beast", "No description", Rarity::Common, 0),
      base_dmg(3), tribe(Tribe::North)
{
}

int Beast_Card::get_base_dmg() const
{
    return base_dmg;
}

void Beast_Card::set_base_dmg(int new_dmg)
{
    if (new_dmg <= 0)
    {
        throw std::invalid_argument("Base damage must be positive");
    }
    base_dmg = new_dmg;
}

Tribe Beast_Card::get_tribe() const
{
    return tribe;
}

void Beast_Card::set_tribe(Tribe new_tribe)
{
    tribe = new_tribe;
}

void Beast_Card::use(Player& user, Player& target)
{
    /**
     * @brief Deal damage to target
     * @throws std::runtime_error If card is already used
     */
    target.take_damage(get_base_dmg()*user.get_cumulative_attack_multiplier());
    user.end_turn();
}

CardType Beast_Card::get_type() const
{
    return CardType::Beast;
}

/**
* @brief Generate random properties for Beast card
*/
void Beast_Card::generate_properties()
{
    // Generate random rarity first
    Rarity random_rarity = generate_random_rarity();
    set_rarity(random_rarity);

    std::uniform_int_distribution<int> name_dist(0, beast_names.size() - 1);
    std::uniform_int_distribution<int> desc_dist(0, beast_descriptions.size() - 1);

    set_name(beast_names[name_dist(rng)]);
    set_description(beast_descriptions[desc_dist(rng)]);
    set_tribe(static_cast<Tribe>(rng() % 4));

    switch (get_rarity())
    {
    case Rarity::Common:
        base_dmg = 2 + static_cast<int>(rng() % 3);
        mana_cost = 1 + static_cast<int>(rng() % 2);
        break;
    case Rarity::Uncommon:
        base_dmg = 3 + static_cast<int>(rng() % 4);
        mana_cost = 1 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Rare:
        base_dmg = 5 + static_cast<int>(rng() % 5);
        mana_cost = 2 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Epic:
        base_dmg = 8 + static_cast<int>(rng() % 6);
        mana_cost = 2 + static_cast<int>(rng() % 5);
        break;
    }
}

void Beast_Card::print_key_info() const
{
    std::cout << "Base Damage: " << base_dmg << ", Tribe: " << tribeToString(tribe);
}