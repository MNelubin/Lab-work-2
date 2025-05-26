# General description of the system  
The game is a turn—based card RPG where human and AI players use cards to attack, defend, heal, and power up.  

### Main components:
- **Cards**: 12 types combined in an inheritance hierarchy (for example, `Attack_Spell_Card`, `Beast_Card`).  
- **Players**:
- `Human_Player`: User-controlled. This class is responsible for saving and loading player progress, specifically character statistics such as experience, name, and other relevant attributes, to `.dat` files in the `saves` directory.  
  - `AI_Player`: Automatically selects optimal moves via `find_best_combination()`.  
- **Characters**: 3 classes (`Healer_Character`, `Tank_Character`, `Knight_Character`) with unique abilities .  
- **Mechanics**:  
  - Mana and player lives.  
  - Character levels and multipliers (`Dmg_MLTPL`, `Heal_MLTPL`).  
  - Player interaction with cards (`Use_card()`, `Eat_card()`,`Throw_card_out()`).
