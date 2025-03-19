/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/cards/buff_spell_card.h"
#include "../../include/player/player.h"

#include <stdexcept>

Buff_Spell_Card::Buff_Spell_Card(const std::string& name, const std::string& description,
                                 Rarity rarity, int mana_cost, Element elem,
                                 float multiplier)
    : Spell_Card(name, description, rarity, mana_cost, elem),
      multiplier(multiplier)
{
    if (multiplier <= 0)
    {
        throw std::invalid_argument("Multiplier must be positive");
    }
}

float Buff_Spell_Card::get_multiplier() const
{
    return multiplier;
}

void Buff_Spell_Card::set_multiplier(float new_multiplier)
{
    if (new_multiplier <= 0)
    {
        throw std::invalid_argument("Multiplier must be positive");
    }
    multiplier = new_multiplier;
}

void Buff_Spell_Card::use(Player& user, Player& target)
{
    /**
     * @brief Apply temporary stat boost
     */
    user.apply_attack_multiplier(get_multiplier());
    user.apply_heal_multiplier(get_multiplier());
}

CardType Buff_Spell_Card::get_type() const
{
    return CardType::BuffSpell;
}




/**
* @brief Generate random properties for Buff Spell card
*/
void Buff_Spell_Card::generate_properties()
{
    // Generate random rarity first
    Rarity random_rarity = generate_random_rarity();
    set_rarity(random_rarity);

    std::uniform_int_distribution<int> name_dist(0, buff_spell_names.size() - 1);
    std::uniform_int_distribution<int> desc_dist(0, buff_spell_descriptions.size() - 1);

    set_name(buff_spell_names[name_dist(rng)]);
    set_description(buff_spell_descriptions[desc_dist(rng)]);
    set_element(static_cast<Element>(rng() % 4));

    switch (get_rarity())
    {
    case Rarity::Common:
        multiplier = 1.1f + static_cast<float>(rng() % 5) * 0.1f;
        mana_cost = 1 + static_cast<int>(rng() % 2);
        break;
    case Rarity::Uncommon:
        multiplier = 1.3f + static_cast<float>(rng() % 8) * 0.1f;
        mana_cost = 1 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Rare:
        multiplier = 1.6f + static_cast<float>(rng() % 11) * 0.1f;
        mana_cost = 2 + static_cast<int>(rng() % 3);
        break;
    case Rarity::Epic:
        multiplier = 2.0f + static_cast<float>(rng() % 16) * 0.1f;
        mana_cost = 2 + static_cast<int>(rng() % 5);
        break;
    }
}

void Buff_Spell_Card::print_key_info() const
{
    std::cout << "Multiplier: " << multiplier;
}
