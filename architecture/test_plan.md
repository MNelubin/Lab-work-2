# Core Test Plan

## 1. Types of tests
**Unit tests** (90% coverage):
- Validation of card attributes (mana, damage, rarity)
- Checking ability limits (Shielding(), Armoring())
- Calculating damage/healing formulas
- Save/load game progress

**Integration tests** (10% coverage):
- AI's work with different types of maps

## 2. Tools and environment
- **Framework**: Google Test (gtest)
- **OS**: Ubuntu 22.04 LTS
- **Compiler**: GCC 11+
- **CI**: Existing system with preinstalled:
``yaml
- name: Setup environment
      run: |
        sudo apt-get update
        sudo apt-get install -y g++-11 make libgtest-dev
        sudo ln -sf /usr/bin/g++-11 /usr/bin/g++
  ```

##3. Critical components

### 3.1 Card Validation
**Test cases:**
```cpp
TEST(CardTest, InvalidMana) {
    Card card;
    ASSERT_THROW(card.Set_Mana_Cost(11), InvalidCardException);
}

TEST(CardTest, MinimumDamage) {
    Attack_Spell_Card card;
    ASSERT_THROW(card.Set_Base_DMG(0), InvalidDamageValue);
}
```

### 3.2 Combat Mechanics
**Sample data:**
```cpp
vector<Card> test_deck = {
    Attack_Spell_Card("Fireball", 3, 5),
    Shield_Card("Iron Shield", 2, 3)
};
```

**Test cases:**
1. Damage 5 vs Armor 3 → 2 damage
2. Double shield (3+3) → armor 6
3. Attempt to re-Shielding() → error

### 3.3 The AI System
**Logic of choice:**
```cpp
TEST(AITest, BestCardSelection) {
    
    vector<Card> hand = {
        {mana: 3, dmg: 5},
        {mana: 2, dmg: 3}
    };
    AI_Player ai(hand);
    ASSERT_EQ(ai.count_best(), 0); // Selecting the first card
}
``

###3.4 Saving Progress
**File format:**
```json
{
  "player_name": "Vova",
  "characters": {
    "tank": {"xp": 300, "level": 1}
  }
}
```

## 4. Integration with CI
**Configuration:**
```yaml
jobs:
  build-and-test:
    runs-on: ubuntu-latest

    steps:
    - name: Checkout code
      uses: actions/checkout@v4

    - name: Setup environment
      run: |
        sudo apt-get update
        sudo apt-get install -y g++-11 make libgtest-dev
        sudo ln -sf /usr/bin/g++-11 /usr/bin/g++

    - name: Build tests
      run: |
        make test

    - name: Execute tests
      run: |
        ./test-card_app

    - name: Build release
      run: |
        make clean
        make

    - name: Cleanup
      run: |
        make cleanall 
```

## 5. Success criteria
- All tests are error-free
- 100% coverage of critical scenarios

##6. Reporting
- Notifications about test crashes in CI