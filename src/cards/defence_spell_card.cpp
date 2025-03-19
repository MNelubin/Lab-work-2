/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/defence_spell_card.h"
#include "../../include/player/player.h"
#include "../../include/player/character.h"

#include <stdexcept>
#include <iostream>

Defence_Spell_Card::Defence_Spell_Card(const std::string& name, const std::string& description,
                                       Rarity rarity, int mana_cost, Element elem,
                                       int base_def)
    : Spell_Card(name, description, rarity, mana_cost, elem),
      base_def(base_def)
{
    if (base_def <= 0)
    {
        throw std::invalid_argument("Base defense must be positive");
    }
}
Defence_Spell_Card::Defence_Spell_Card(const std::string& name, const std::string& description,
                                       Rarity rarity, int mana_cost, Element elem)
    : Spell_Card(name, description, rarity, mana_cost, elem),
      base_def(0) {}

// Default constructor implementation
Defence_Spell_Card::Defence_Spell_Card()
    : Spell_Card("Unnamed Defence Spell", "No description", Rarity::Common, 0, Element::Earth),
      base_def(2)
{
}

int Defence_Spell_Card::get_base_def() const
{
    return base_def;
}

void Defence_Spell_Card::set_base_def(int new_def)
{
    if (new_def <= 0)
    {
        throw std::invalid_argument("Base defense must be positive");
    }
    base_def = new_def;
}

void Defence_Spell_Card::use(Player& user, Player& target)
{
    /**
     * @brief Increase defense
     */
    int armor_amount=static_cast<int>(get_base_def() * user.get_character().get_armor_multiplier());
    user.set_armor(armor_amount + user.get_armor());
}

CardType Defence_Spell_Card::get_type() const
{
    return CardType::DefenceSpell;
}

/**
* @brief Generate random properties for Defence Spell card
*/
void Defence_Spell_Card::generate_properties()
{
    // Generate random rarity first
    Rarity random_rarity = generate_random_rarity();
    set_rarity(random_rarity);

    std::uniform_int_distribution<int> name_dist(0, defence_spell_names.size() - 1);
    std::uniform_int_distribution<int> desc_dist(0, defence_spell_descriptions.size() - 1);

    set_name(defence_spell_names[name_dist(rng)]);
    set_description(defence_spell_descriptions[desc_dist(rng)]);
    set_element(static_cast<Element>(rng() % 4));

    switch (get_rarity())
    {
    case Rarity::Common:
        base_def = 2 + static_cast<int>(rng() % 3);
        mana_cost = 1 + static_cast<int>(rng() % 2);
        break;
    case Rarity::Uncommon:
        base_def = 3 + static_cast<int>(rng() % 4);
        mana_cost = 1 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Rare:
        base_def = 5 + static_cast<int>(rng() % 5);
        mana_cost = 2 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Epic:
        base_def = 8 + static_cast<int>(rng() % 6);
        mana_cost = 2 + static_cast<int>(rng() % 5);
        break;
    }
}

void Defence_Spell_Card::print_key_info() const
{
    std::cout << "Base Defense: " << base_def;
}