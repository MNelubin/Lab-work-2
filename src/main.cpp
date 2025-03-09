/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/

#include "../include/cards/card.h"
#include "../include/cards/enums.h"
#include "../include/cards/spell_card.h"
#include "../include/cards/attack_spell_card.h"
#include "../include/cards/heal_spell_card.h"
#include "../include/cards/buff_spell_card.h"
#include "../include/cards/defence_spell_card.h"
#include "../include/cards/beast_card.h"
#include "../include/cards/creature_card.h"
#include "../include/cards/weapon_card.h"
#include "../include/cards/artifact_card.h"
#include "../include/cards/shield_card.h"
#include "../include/cards/buff_card.h"
#include "../include/player/player.h"
#include "../include/player/character.h"
#include "../include/player/healer_character.h"
#include "../include/player/tank_character.h"
#include "../include/player/knight_character.h"
#include "../include/player/hand.h"

#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function prototypes
void start_1v1_match();
void game_menu();
std::unique_ptr<Character> create_predefined_character(int choice);
std::unique_ptr<Character> create_predefined_character_ai(int choice);
std::unique_ptr<Character> create_ai_character();

/**
 * @brief Main game menu with options to start a new game or exit.
 */
void game_menu() {
    std::cout << "Welcome to the Card Game!\n";
    std::cout << "1. Start New 1v1 Match\n";
    std::cout << "2. Exit\n";
    std::cout << "Enter your choice: ";
}

/**
 * @brief Main function to run the game.
 */
int main() {
    while (true) {
        game_menu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                start_1v1_match();
                break;
            case 2:
                std::cout << "Thanks for playing!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}

/**
 * @brief Creates a predefined character based on the choice.
 * @param choice 1 for healer, 2 for tank, 3 for knight
 * @return Unique pointer to the created character
 */
std::unique_ptr<Character> create_predefined_character(int choice) {
    switch (choice) {
        case 1: {
            return std::make_unique<Healer_Character>(
                100, 1, 0, "Aragorn", 1.2f, 0.9f, 1.0f, "Royal Healer", 3
            );
        }
        case 2: {
            return std::make_unique<Tank_Character>(
                150, 1, 0, "Gimli", 1.0f, 0.8f, 1.5f, "Stone Shield Bearer", 2, 50
            );
        }
        case 3: {
            return std::make_unique<Knight_Character>(
                120, 1, 0, "Legolas", 1.0f, 1.2f, 1.0f, "Rapid Striker", 3, 30, 0
            );
        }
        default:
            return std::make_unique<Healer_Character>(
                100, 1, 0, "Default Healer", 1.0f, 1.0f, 1.0f, "Basic Healer", 1
            );
    }
}

std::unique_ptr<Character> create_predefined_character_ai(int choice) {
    switch (choice) {
        case 1: {
            return std::make_unique<Healer_Character>(
                100, 1, 0, "!Aragorn", 1.2f, 0.9f, 1.0f, "Royal Healer", 3
            );
        }
        case 2: {
            return std::make_unique<Tank_Character>(
                150, 1, 0, "!Gimli", 1.0f, 0.8f, 1.5f, "Stone Shield Bearer", 2, 50
            );
        }
        case 3: {
            return std::make_unique<Knight_Character>(
                120, 1, 0, "!Legolas", 1.0f, 1.2f, 1.0f, "Rapid Striker", 3, 30, 0
            );
        }
        default:
            return std::make_unique<Healer_Character>(
                100, 1, 0, "!Default Healer", 1.0f, 1.0f, 1.0f, "Basic Healer", 1
            );
    }
}

/**
 * @brief Creates a random AI character.
 * @return Unique pointer to the created character
 */
std::unique_ptr<Character> create_ai_character() {
    std::srand(static_cast<unsigned>(std::time(0)));
    int choice = std::rand() % 3 + 1;
    return create_predefined_character(choice);
}

/**
 * @brief Runs a 1v1 match between two players with predefined characters and hands.
 */
void start_1v1_match() {
    // Create predefined characters
    std::cout << "Select your character:\n";
    std::cout << "1. Healer - Aragorn\n";
    std::cout << "2. Tank - Gimli\n";
    std::cout << "3. Knight - Legolas\n";
    int player_choice;
    std::cin >> player_choice;

    Player player1(100, 50, 0, "Player 1", create_predefined_character(player_choice));
    Player player2(100, 50, 0, "Player 2", create_ai_character());
    
    // Generate initial hands for both players
    player1.get_hand().generate(4);
    player2.get_hand().generate(4);

    bool game_over = false;

    std::cout << "\nMatch Started!\n";
    
    while (!game_over) {
        bool skip_turn_p1 = false;
        bool skip_turn_p2 = false;

        // Reset mana at the start of each turn
        player1.set_mana(10);
        player2.set_mana(10);

        // Player 1's turn
        std::cout << "\n=== Player 1's Turn ===\n";
        
        // Check if player has playable cards or needs to regenerate hand
        bool has_playable_cards = false;
        int min_mana_cost = 100;
        bool has_playable = false;
        for (int i = 0; i < player1.get_hand().get_amount(); ++i) {
            if (player1.get_hand().get_card(i).get_type() == CardType::Beast ||
                 player1.get_hand().get_card(i).get_type() == CardType::Creature ||
                 player1.get_hand().get_card(i).get_type() == CardType::AttackSpell||
                 player1.get_hand().get_card(i).get_type() == CardType::HealSpell ) {
                has_playable = true;
                 }
            min_mana_cost = std::min(min_mana_cost,player1.get_hand().get_card(i).get_mana_cost());
            if (min_mana_cost<=player1.get_mana() && has_playable){
                has_playable_cards = true;
                break;
            }
        }

        if (!has_playable_cards || player1.get_hand().get_amount() == 0) {
            std::cout << "No playable cards or empty hand. Regenerating hand and skipping turn.\n";
            player1.get_hand().generate(4);
            skip_turn_p1 = true;
        }

        if (!skip_turn_p1) {
            player1.set_turn_active(false);
            while (!player1.is_turn_active() && player1.get_hand().get_amount() > 0) {
                player1.get_hand().sort_by_mana();
                player1.show_hand();

                // Display player statistics after showing hand
                std::cout << "\nYour Status:\n";
                std::cout << "HP: " << player1.get_hp() 
                          << " | Mana: " << player1.get_mana() 
                          << " | Armor: " << player1.get_armor() 
                          << " | Shield: " << player1.get_shield_amount() 
                          << " | Atk Multiplier: " << player1.get_cumulative_attack_multiplier() 
                          << " | Heal Multiplier: " << player1.get_cumulative_heal_multiplier() 
                          << " | Weapon Adder: " << player1.get_cumulative_weapon_bonus();

                // Display player statistics after showing hand
                std::cout << "\nEnemy Stat.:\n";
                std::cout << "HP: " << player2.get_hp() 
                          << " | Mana: " << player2.get_mana() 
                          << " | Armor: " << player2.get_armor() 
                          << " | Shield: " << player2.get_shield_amount() 
                          << " | Atk Multiplier: " << player2.get_cumulative_attack_multiplier() 
                          << " | Heal Multiplier: " << player2.get_cumulative_heal_multiplier() 
                          << " | Weapon Adder: " << player2.get_cumulative_weapon_bonus() << "\n\n";

                std::cout << "Choose a card to use (index): ";
                int card_index;
                std::cin >> card_index;

                try {
                    player1.use_card(card_index, player2);
                    std::cout << "Used card successfully!\n";
                    std::cout << "Player 2's HP: " << player2.get_hp() << '\n';
                } catch (...) {
                    std::cout << "Error using card.\n";
                }

                // Check if player has no mana left or no playable cards
                has_playable_cards = false;
                min_mana_cost = 100;
                has_playable = false;
                for (int i = 0; i < player1.get_hand().get_amount(); ++i) {
                    if (player1.get_hand().get_card(i).get_type() == CardType::Beast ||
                        player1.get_hand().get_card(i).get_type() == CardType::Creature ||
                        player1.get_hand().get_card(i).get_type() == CardType::AttackSpell||
                        player1.get_hand().get_card(i).get_type() == CardType::HealSpell ) {
                        has_playable = true;
                        }
                    min_mana_cost = std::min(min_mana_cost,player1.get_hand().get_card(i).get_mana_cost());
                    if (min_mana_cost<=player1.get_mana() && has_playable){
                        has_playable_cards = true;
                        break;
                    }
                }

                if (!has_playable_cards) {std::cout<<"No playable cards\n";}
                if (player1.get_mana() <= 0) {std::cout<<"No mana\n";}
                if (player1.get_hand().get_amount() == 0) {std::cout<<"No cards in hand\n";}

                if (!has_playable_cards || player1.get_mana() <= 0 || player1.get_hand().get_amount() == 0) {
                    player1.set_turn_active(true);
                }
            }
        } else {
            std::cout << "Skipping Player 1's turn due to hand regeneration.\n";
        }

        // Check if Player 2 is defeated
        if (player2.get_hp() <= 0) {
            std::cout << "Player 1 wins!\n";
            game_over = true;
            continue;
        }

        // Player 2's turn (AI)
        std::cout << "\n=== Player 2's Turn ===\n";
        std::cout << "AI is thinking...\n";

         // Check if player has no mana left or no playable cards
        has_playable_cards = false;
        min_mana_cost = 100;
        has_playable = false;
        for (int i = 0; i < player2.get_hand().get_amount(); ++i) {
            if (player2.get_hand().get_card(i).get_type() == CardType::Beast ||
                player2.get_hand().get_card(i).get_type() == CardType::Creature ||
                player2.get_hand().get_card(i).get_type() == CardType::AttackSpell||
                player2.get_hand().get_card(i).get_type() == CardType::HealSpell ) {
                has_playable = true;
                }
                min_mana_cost = std::min(min_mana_cost,player2.get_hand().get_card(i).get_mana_cost());
            if (min_mana_cost<=player2.get_mana() && has_playable){
                has_playable_cards = true;
                break;
            }
        }

        if (!has_playable_cards) {std::cout<<"No playable cards\n";}
        if (player1.get_mana() <= 0) {std::cout<<"No mana\n";}
        if (player1.get_hand().get_amount() == 0) {std::cout<<"No cards in hand\n";}


        if (!has_playable_cards || player2.get_hand().get_amount() == 0) {
            std::cout << "No playable cards or empty hand. Regenerating hand and skipping turn.\n";
            player2.get_hand().generate(4);
            skip_turn_p2 = true;
        }

        if (!skip_turn_p2) {
            player2.set_turn_active(false);
            while (!player2.is_turn_active() && player2.get_hand().get_amount() > 0) {
                player2.get_hand().sort_by_mana();
                
                // Simple AI logic
                if (!player2.get_hand().get_amount() ==0) {
                    int ai_card_index = std::rand() % player2.get_hand().get_amount();
                    if (player2.get_hand().get_card(ai_card_index).get_mana_cost()<=player2.get_mana()){
                        try {
                            std::cout << "AI used card: " << player2.get_hand().get_card(ai_card_index).get_name() << "\n";
                            player2.use_card(ai_card_index, player1);
                            std::cout << "Player 1's HP: " << player1.get_hp() << '\n';
                        } catch (...) {
                            std::cout << "AI failed to use a card.\n";
                        }
                    }
                }
                // Check if player has no mana left or no playable cards
                has_playable_cards = false;
                min_mana_cost = 100;
                has_playable = false;
                for (int i = 0; i < player2.get_hand().get_amount(); ++i) {
                    if (player2.get_hand().get_card(i).get_type() == CardType::Beast ||
                        player2.get_hand().get_card(i).get_type() == CardType::Creature ||
                        player2.get_hand().get_card(i).get_type() == CardType::AttackSpell||
                        player2.get_hand().get_card(i).get_type() == CardType::HealSpell ) {
                        has_playable = true;
                    }
                    min_mana_cost = std::min(min_mana_cost,player2.get_hand().get_card(i).get_mana_cost());
                    if (min_mana_cost<=player2.get_mana() && has_playable){
                        has_playable_cards = true;
                        break;
                    }
                }

                if (!has_playable_cards || player2.get_mana() <= 0 || player2.get_hand().get_amount() == 0) {
                    player2.set_turn_active(true);
                }
            }
        } else {
            std::cout << "Skipping Player 2's turn due to hand regeneration.\n";
        }

        // Check if Player 1 is defeated
        if (player1.get_hp() <= 0) {
            std::cout << "Player 2 wins!\n";
            game_over = true;
            continue;
        }

        // Ask if players want to continue
        char choice;
        std::cout << "Continue? (y/n): ";
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
        }

        // Option to give new cards
        std::cout << "\nGive new cards? (y/n): ";
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            player1.get_hand().generate(4);
            player2.get_hand().generate(4);
        }
        
        player1.end_turn();
        player2.end_turn();
    }

    std::cout << "Match ended.\n";
}