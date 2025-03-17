## 1. Types of Tests
**Unit Tests** (90% coverage):
- Card class functionality (constructors, getters/setters)
- Spell cards (Attack, Heal, Buff, Defence)
- Creature cards (Beast, Creature)
- Weapon and Shield cards
- Character class and derived classes (Healer, Tank, Knight)
- Hand class operations
- Player class interactions

**Integration Tests** (10% coverage):
- AI player decision making
- Human player interactions
- Card usage in game context
- Character abilities integration

## 2. Tools and Environment
- **Framework**: Google Test (gtest)
- **OS**: Ubuntu 22.04 LTS
- **Compiler**: GCC 11+
- **CI/CD**: GitHub Actions

## 3. Critical Components

### 3.1 Card Class Validation
**Test Cases:**
- Constructor validation for all card types
- Getter and setter functionality
- Rarity distribution verification
- Type detection through polymorphism
- Pure virtual method implementation

### 3.2 Spell Cards Functionality
**Test Cases:**
- Attack spell damage calculation
- Heal spell recovery validation
- Buff spell multiplier application
- Defence spell shield application
- Mana cost validation
- Special abilities implementation

### 3.3 Character Class Functionality
**Test Cases:**
- Level-up mechanics
- Experience management
- Ability uses tracking
- Special actions implementation
- Character statistics formatting

### 3.4 Player Class Interactions
**Test Cases:**
- Hand management
- Card usage and effects
- Damage and healing calculations
- Turn management
- Special action execution

### 3.5 AI Player Decision Making
**Test Cases:**
- Best card combination selection
- Combat card prioritization
- Mana management
- Strategy implementation

### 3.6 Human Player Features
**Test Cases:**
- Character management
- Save/load functionality
- Customization interface
- Input validation

## 4. Integration with CI/CD
**Configuration:**
```yaml
name: C++ CI

on: [push, pull_request]

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

## 5. Success Criteria
- All unit tests pass
- Integration tests demonstrate correct system behavior
- Test coverage meets requirements
- No crashes

## 6. Reporting
- Detailed test results in CI/CD pipeline