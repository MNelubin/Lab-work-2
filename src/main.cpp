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
    
    // Generate hands for both players
    player1.get_hand().generate(2);
    player2.get_hand().generate(3);

    bool game_over = false;
    std::cout << "\nMatch Started!\n";
    
    while (!game_over) {
        player1.set_mana(10);
        player2.set_mana(10);
        // Player 1's turn
        std::cout << "\n=== Player 1's Turn ===\n";
        
        

        player1.set_turn_active(false);
        while(!player1.is_turn_active() && player1.get_hand().get_amount() > 0){
        
	    player1.get_hand().sort_by_mana();
            player1.show_hand();
            std::cout << "Your mana: "<< player1.get_mana()<< "\n" <<"Choose a card to use (index): ";
            int card_index;
            std::cin >> card_index;
            try {
                player1.use_card(card_index, player2);
                std::cout << "Used card successfully!\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << '\n';
            }
            
            
            
            if (player1.get_mana() <= 0) {
                player1.set_turn_active(true); // No mana left
            }

            
        }
        std::cout << "Player 2's HP: " << player2.get_hp() << '\n';
        if (player2.get_hp() <= 0) {
            std::cout << "Player 1 wins!\n";
            game_over = true;
            break;
        }
        // Player 2's turn (AI)
        std::cout << "\n=== Player 2's Turn ===\n";
        std::cout << "AI is thinking...\n";

        player2.set_turn_active(false); // Begin the AI's turn

        while (!player2.is_turn_active() && player2.get_hand().get_amount() > 0) {
        
            player2.get_hand().sort_by_mana();
        
            //int ai_card_index = std::rand() % player2.get_hand().get_amount();
            
            try {
            	for (int i=player2.get_hand().get_amount()-1 ;(i>0 && !player2.is_turn_active() && player2.get_mana() > 0);i--){
            		const Card& selected_card = player2.get_hand().get_card(i);
                	std::cout << "AI used card: " << selected_card.get_name() << " - " << cardTypeToString(selected_card.get_type()) << " - " << selected_card.get_mana_cost()<< "\n"<< "AI mana: "<< player2.get_mana()-selected_card.get_mana_cost() << "\n";
                	if (selected_card.get_mana_cost()<=player2.get_mana()){
                		player2.use_card(i, player1);
                		i = player2.get_hand().get_amount()-1;
                	}
            	
            	}
            	
                player2.set_turn_active(true);
                
                
                
            } catch (...) {
                std::cout << "AI failed to use a card.\n";
                player2.set_turn_active(true);
            }
        }

        player2.end_turn();
            

        std::cout << "Player 1's HP: " << player1.get_hp() << '\n';
        if (player1.get_hp() <= 0) {
            std::cout << "Player 2 wins!\n";
            game_over = true;
        }

        // Option to end match or give new cards
        std::cout << "\nEnd match? (y/n): ";
        char end_choice;
        std::cin >> end_choice;
        if (end_choice == 'y' || end_choice == 'Y') {
            break;
        }
        std::cout << "\nGive new cards? (y/n): ";
       
        std::cin >> end_choice;
        if (end_choice == 'y' || end_choice == 'Y') {
        	int deck_index = std::rand() % 3 + 1;
        	player1.get_hand().generate(deck_index);
        	deck_index = std::rand() % 3 + 1;
        	player2.get_hand().generate(deck_index);
        }
        
    }

    std::cout << "Match ended.\n";
}
