# Complete Core System Requirements

## Basic map parameters
- **Name**: 3-50 characters (Latin/Cyrillic/numbers)
- **Mana**: integer 0-10 inclusive
- **Damage**: minimum value 1, integer
- **Rarity**: 4 variants (Common, Uncommon, Rare, Epic)
- **Special Types**:
- Attacking spells: Base_DMG ≥ 1
  - Shields: Stackable (cumulative)
- Treatment: Base_Heal ≥ 0

## Characters and abilities
- **Tank_Character**:
- Shielding() is available 1 time per battle
  - Shield_amount is combined with other shields
- **Knight_Character**:
  - Armoring() adds a fixed value to the armor
- The armor is valid until the end of the battle
- **Healer_Character**:
- Number of treatments = Character level
  - Heal_MLTPL increases with the level

## Combat mechanics
**Calculation formulas:**


```
# Armor
-adjusted damage efficie_dmg = max(0, (base_dmg * dmg_MLTPL) - total_armor)

# Treatment when using the card
heal_value = base_heal * heal_MLTPL * efficiency
```

**Validation of actions:**
```cpp
if (mana < mana_cost){
    raise NotEnoughManaError(f"Need {card_cost}, have {mana}")
}

if (!was_up){
    throw AbilityLockedError("Shield already used")
}

if (!was_armored){
    throw AbilityLockedError("Armor already used")
}
```

## The AI system
**Card selection algorithm:**
1. Filter by available mana
2. Sort by descending damage
3. Choosing the top 1 card
4. If the damage is equal, the priority of the cards is first

**Selection example:**
``
Cards in your hand: 
- Fireball (cost=3, dmg=5)
- Heal (cost=2, heal=3)
- Shield (cost=1, armor=2)

AI Selection: Fireball (max. damage)
``

## Saving progress (temporarily for json example)
**Saved data:**

```json
{
  "player_name": "Vova",
  "characters": {
    "healer": {
      "xp": 1200,
      "level": 3
    },
    "tank": {
      "xp": 800,
      "level": 2
    }
  }
}
```

## Test scenarios
**Mandatory checks:**
1. Creating a map with mana=10 → success
2. Creating a map with dmg=0 → error
3. Double use of Shielding() → error
4. Saving/loading level progress
5. Damage calculation for armor=5 dmg=8 and Dmg_MLTPL=1.0 → 3 damage

**Test example:**
```cpp
TEST(TankTest, ShieldLimit) {
    Tank_Character tank;
    tank.Shielding(); // OK
    ASSERT_THROW(tank.Shielding(), AbilityLimitReached);
}
```