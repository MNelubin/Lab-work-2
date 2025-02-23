# Brief system requirements

## Functional requirements
1. Maps:
   - Mana: 0-10, an integer
   - Damage: ≥1, integer
   - Rarity: Common/Uncommon/Rare/Epic

2. Characters:
   - Tank: 1 shield per battle (Shielding())
- Knight: Armoring() adds armor
- Healer: limited number of healings

3. Combat mechanics:
   - Damage is calculated as Base_DMG * multipliers
- Shields are added together

4. AI:
- Selects the card with maximum damage
- Takes into account the current mana

5. Save:
- Character levels
   - Leveling progress

## Usage Scenarios
1. The player uses an attacking spell
2. The AI selects the optimal card
3. Tank activates the shield
4. The healer treats himself
5. Saving progress between sessions