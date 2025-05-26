# Lab-work-2
## Author

Maxim Nelyubin 24.Б82-ММ

## Contacts

st132907@student.spbu.ru

## Description

Lab-work 2 - Card game

## Build

make  - for compiling main.cpp 

make test - for compiling test-card_app.cpp

## Run

./card_app - for running main()

./test-card_app - for running test-card_app()

## Additional Features

### Save/Load Progress
The game supports saving and loading player progress. Character data is serialized and saved to binary `.dat` files within the `saves` directory. This allows players to resume their game from a previously saved state.

Specifically, the following data is saved for each character:

**Common for all characters (from `Character` class):**
- Experience points to next level (`xp_to_next_lvl`)
- Current level (`lvl`)
- Current experience points (`xp`)
- Character name (`name`)
- Healing multiplier (`heal_mltpl`)
- Damage multiplier (`dmg_mltpl`)
- Armor multiplier (`armor_mltpl`)
- Character description (`description`)
- Number of ability uses (`ability_uses` - upon loading, this is set to the character's current level)

**Specific to `Healer_Character`:**
- Heal amount (`heal_amount` - calculated as `level * 10` during saving and loading)

**Specific to `Knight_Character`:**
- Base armor up value (`armor_up` - calculated as `level * 5 + 20` during saving and loading)
- Armored amount (`armored_amount` - reset to `0` during saving and loading)

**Specific to `Tank_Character`:**
- Shield add amount (`shield_add` - calculated as `level + 5` during saving and loading)
- Ability used flag (`was_ability_used` - reset to `false` during saving and loading)
