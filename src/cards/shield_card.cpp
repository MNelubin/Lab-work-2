/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/shield_card.h"
#include "../../include/player/player.h"
#include <stdexcept>

Shield_Card::Shield_Card(const std::string& name, const std::string& description,
                         Rarity rarity, int mana_cost, int usage)
    : Card(name, description, rarity, mana_cost), usage(usage)
{
    if (usage <= 0)
    {
        throw std::invalid_argument("Usage must be positive");
    }
}

int Shield_Card::get_usage() const
{
    return usage;
}

void Shield_Card::set_usage(int new_usage)
{
    if (new_usage <= 0)
    {
        throw std::invalid_argument("Usage must be positive");
    }
    usage = new_usage;
}

void Shield_Card::use(Player& user, Player& target)
{
    /**
     * @brief Add shields to target
     */
    user.set_shield_amount(user.get_shield_amount()+get_usage());
}

CardType Shield_Card::get_type() const
{
    return CardType::Shield;
}
/**
* @brief Generate random properties for Shield card
*/
void Shield_Card::generate_properties()
{
    // Generate random rarity first
    Rarity random_rarity = generate_random_rarity();
    set_rarity(random_rarity);

    std::uniform_int_distribution<int> name_dist(0, shield_names.size() - 1);
    std::uniform_int_distribution<int> desc_dist(0, shield_descriptions.size() - 1);

    set_name(shield_names[name_dist(rng)]);
    set_description(shield_descriptions[desc_dist(rng)]);

    switch (get_rarity())
    {
    case Rarity::Common:
        usage = 2 + static_cast<int>(rng() % 3);
        mana_cost = 1 + static_cast<int>(rng() % 2);
        break;
    case Rarity::Uncommon:
        usage = 2 + static_cast<int>(rng() % 5);
        mana_cost = 1 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Rare:
        usage = 4 + static_cast<int>(rng() % 5);
        mana_cost = 2 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Epic:
        usage = 6 + static_cast<int>(rng() % 6);
        mana_cost = 2 + static_cast<int>(rng() % 5);
        break;
    }
}

// Default constructor implementation
Shield_Card::Shield_Card()
    : Card("Unnamed Shield", "No description", Rarity::Common, 0),
      usage(2)
{
}

void Shield_Card::print_key_info() const
{
    std::cout << "Usage: " << usage;
}