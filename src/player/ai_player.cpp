/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/player/ai_player.h"
#include <algorithm>
#include <limits>

int AI_Player::calculate_card_value(const Card& card) const
{
    // For combat cards
    if (auto attack_spell = dynamic_cast<const Attack_Spell_Card*>(&card))
    {
        return attack_spell->get_base_damage() * get_cumulative_attack_multiplier();
    }
    if (auto beast = dynamic_cast<const Beast_Card*>(&card))
    {
        return beast->get_base_dmg() * get_cumulative_attack_multiplier();
    }
    if (auto creature = dynamic_cast<const Creature_Card*>(&card))
    {
        return (creature->get_base_dmg() + get_cumulative_weapon_bonus()) * get_cumulative_attack_multiplier();
    }

    // For medical cards
    if (auto heal_spell = dynamic_cast<const Heal_Spell_Card*>(&card))
    {
        return heal_spell->get_base_heal() * get_cumulative_heal_multiplier();
    }

    // For buff cards
    if (auto buff_spell = dynamic_cast<const Buff_Spell_Card*>(&card))
    {
        return buff_spell->get_multiplier() * 10;
    }
    if (auto artifact = dynamic_cast<const Artifact_Card*>(&card))
    {
        return artifact->get_multiplier() * artifact->get_multiplier() * 10;
    }
    if (auto buff = dynamic_cast<const Buff_Card*>(&card))
    {
        return buff->get_buff_amount() * 10;
    }
    if (auto weapon = dynamic_cast<const Weapon_Card*>(&card))
    {
        return (weapon->get_dmg_up() + get_cumulative_weapon_bonus())*5;
    }
    if (auto defence_spell = dynamic_cast<const Defence_Spell_Card*>(&card))
    {
        return defence_spell->get_base_def() * 7;
    }
    if (auto shield = dynamic_cast<const Shield_Card*>(&card))
    {
        return shield->get_usage() * 70;
    }

    return 0;
}

std::pair<int, int> AI_Player::find_best_combination() const
{
    std::vector<CardScore> cards;
    const int total_mana = get_mana();

    // We collect information about maps based on the actual values
    for(int i = 0; i < get_hand().get_amount(); ++i)
    {
        const auto& card = get_hand().get_card(i);
        cards.push_back(
        {
            i,
            calculate_card_value(card),
            card.get_mana_cost(),
            card.get_type()
        });
    }

    // Search for the main map based on the type
    auto is_combat_card = [](const CardScore& c)
    {
        return c.type == CardType::AttackSpell ||
               c.type == CardType::Beast ||
               c.type == CardType::Creature ||
               c.type == CardType::HealSpell;
    };

    auto best_main = std::max_element(cards.begin(), cards.end(),
                                      [&](const CardScore& a, const CardScore& b)
    {
        bool aCombat = is_combat_card(a);
        bool bCombat = is_combat_card(b);

        if(aCombat != bCombat) return aCombat < bCombat;
        if(a.value != b.value) return a.value < b.value;
        return a.mana_cost > b.mana_cost;
    });

    // Logic of selecting additional cards
    auto find_secondary = [&](int remaining_mana) -> int
    {
        std::vector<CardScore> candidates;

        for(const auto& c : cards)
        {
            const bool isBuffType = c.type == CardType::BuffSpell ||
            c.type == CardType::Artifact ||
            c.type == CardType::Buff;

            if(isBuffType && c.mana_cost <= remaining_mana)
            {
                candidates.push_back(c);
            }
        }

        if(!candidates.empty())
        {
            auto best = std::max_element(candidates.begin(), candidates.end(),
                                         [](const CardScore& a, const CardScore& b)
            {
                return a.value < b.value;
            });
            return best->index;
        }
        return -1;
    };

    // Implementation of the fallback logic
    auto find_fallback = [&]() -> int
    {
        for(const auto& c : cards)
        {
            if(c.mana_cost <= total_mana &&
                    !is_combat_card(c) &&
                    c.type != CardType::HealSpell)
            {
                return c.index;
            }
        }
        return -1;
    };

    // The basic logic of choice
    if(best_main != cards.end() && best_main->mana_cost <= total_mana)
    {
        int remaining_mana = total_mana - best_main->mana_cost;
        int secondary = find_secondary(remaining_mana);

        if(secondary == -1) secondary = find_fallback();

        return {best_main->index, secondary};
    }

    // Fallback: the first available map
    for(const auto& c : cards)
    {
        if(c.mana_cost <= total_mana)
        {
            return {c.index, -1};
        }
    }

    return {-1, -1};
}


