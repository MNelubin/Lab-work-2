/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/weapon_card.h"
#include "../../include/player/player.h"

#include <stdexcept>

Weapon_Card::Weapon_Card(const std::string& name, const std::string& description,
                         Rarity rarity, int mana_cost, int dmg_up)
    : Card(name, description, rarity, mana_cost), dmg_up(dmg_up)
{
    if (dmg_up <= 0)
    {
        throw std::invalid_argument("Damage increase must be positive");
    }
}

Weapon_Card::Weapon_Card(const std::string& name, const std::string& description,
                         Rarity rarity, int mana_cost)
    : Card(name, description, rarity, mana_cost), dmg_up(0) {}

// Default constructor implementation
Weapon_Card::Weapon_Card()
    : Card("Unnamed Weapon", "No description", Rarity::Common, 0),
      dmg_up(2)
{
}

int Weapon_Card::get_dmg_up() const
{
    return dmg_up;
}

void Weapon_Card::set_dmg_up(int new_dmg_up)
{
    if (new_dmg_up <= 0)
    {
        throw std::invalid_argument("Damage increase must be positive");
    }
    dmg_up = new_dmg_up;
}

void Weapon_Card::use(Player& user, Player& target)
{
    /**
     * @brief Deal enhanced damage
     */
    user.add_weapon_bonus(get_dmg_up());
}

CardType Weapon_Card::get_type() const
{
    return CardType::Weapon;
}


/**
* @brief Generate random properties for Weapon card
*/
void Weapon_Card::generate_properties()
{
    // Generate random rarity first
    Rarity random_rarity = generate_random_rarity();
    set_rarity(random_rarity);

    std::uniform_int_distribution<int> name_dist(0, weapon_names.size() - 1);
    std::uniform_int_distribution<int> desc_dist(0, weapon_descriptions.size() - 1);

    set_name(weapon_names[name_dist(rng)]);
    set_description(weapon_descriptions[desc_dist(rng)]);

    switch (get_rarity())
    {
    case Rarity::Common:
        dmg_up = 2 + static_cast<int>(rng() % 3);
        mana_cost = 1 + static_cast<int>(rng() % 2);
        break;
    case Rarity::Uncommon:
        dmg_up = 3 + static_cast<int>(rng() % 4);
        mana_cost = 1 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Rare:
        dmg_up = 5 + static_cast<int>(rng() % 5);
        mana_cost = 2 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Epic:
        dmg_up = 8 + static_cast<int>(rng() % 6);
        mana_cost = 2 + static_cast<int>(rng() % 5);
        break;
    }
}

void Weapon_Card::print_key_info() const
{
    std::cout << "Damage Increase: " << dmg_up;
}