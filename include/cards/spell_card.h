/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#ifndef SPELL_CARD_H
#define SPELL_CARD_H

#include "card.h"

/**
 * @brief Base class for spell cards
 *
 * Inherits from Card and adds elemental magic properties.
 */
class Spell_Card : public Card
{
protected:
    Element element; ///< Magical element type from enum

public:
    /**
     * @brief Construct a new Spell Card object
     *
     * @param name Card display name
     * @param description Effect description
     * @param rarity Rarity classification
     * @param mana_cost Required mana to cast
     * @param element Elemental affinity
     */
    Spell_Card(const std::string& name, const std::string& description,
               Rarity rarity, int mana_cost, Element element);

    virtual ~Spell_Card() = default;

    /**
     * @brief Get the element type
     * @return Current elemental affinity
     */
    Element get_element() const;

    /**
     * @brief Change elemental affinity
     * @param new_element New element to assign
     * @post get_element() == new_element
     */
    void set_element(Element new_element);
};

#endif