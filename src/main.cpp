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
#include "../include/player/human_player.h"
#include "../include/player/ai_player.h"

#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <cstdlib>


// Function prototypes
void start_1v1_match();
void game_menu();
void clear_screen();
std::unique_ptr<Character> create_predefined_character(int choice);
std::unique_ptr<Character> create_predefined_character_ai(int choice);
std::unique_ptr<Character> create_ai_character();

/**
 * @brief Function for clearing terminal
 */
void clear_screen() {
    system("clear"); 
}


/**
 * @brief Main game menu with options to start a new game or exit.
 */
void game_menu() {
    
    std::cout << "1. Start New 1v1 Match\n";
    std::cout << "2. Exit\n";
    std::cout << "Enter your choice: ";
}

/**
 * @brief Main function to run the game.
 */
int main() {
    std::cout << "Welcome to the Card Game!\n";
    while (true) {
        game_menu();
        
        int choice;

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(); 
        
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
                100, 2, 0, "Aragorn", 1.4f, 0.9f, 1.0f, "Royal Healer", 3
            );
        }
        case 2: {
            return std::make_unique<Tank_Character>(
                150, 3, 0, "Gimli", 1.0f, 0.8f, 1.6f, "Stone Shield Bearer", 2, 5
            );
        }
        case 3: {
            return std::make_unique<Knight_Character>(
                120, 4, 0, "Legolas", 1.0f, 1.6f, 1.0f, "Rapid Striker", 3, 30, 0
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
                150, 1, 0, "!Gimli", 1.0f, 0.8f, 1.5f, "Stone Shield Bearer", 2, 5
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

int rarity_to_value(Rarity rarity) {
    return static_cast<int>(rarity) + 1;
}

/**
 * @brief Handles a player's turn with a menu-driven interface
 * 
 * This function provides a menu with the following options:
 * 1. Use a card from hand
 * 2. Use special ability
 * 3. Eat card
 * 4. Throw out card
 * 5. Show character characteristic
 * 6. End turn
 * 
 * The turn automatically ends when:
 * - Player has no mana left
 * - Player has no cards left
 * - Player chooses to end turn
 * 
 * @param player The human player taking the turn
 * @param enemy The opponent player
 */
void player_turn(Human_Player& player, Player& enemy) {
    player.set_turn_active(false);
    bool ability_used = false;
    player.get_hand().sort_by_mana();
    
    while(!player.is_turn_active() && player.get_hand().get_amount() > 0) {
        player.show_hand();

        // info output
        std::cout << "\n\033[34m=== Player Status ===\033[0m\n";
        std::cout << "HP: " << player.get_hp() 
                  << " | Mana: " << player.get_mana()
                  << " | Armor: " << player.get_armor()
                  << " | Shields: " << player.get_shield_amount()
                  << "\nAbility: ";
        player.get_special_action_info();
        std::cout << " Uses :" << enemy.get_character().get_ability_uses();
        std::cout << "\nMultipliers: "
                  << "ATK x" << player.get_cumulative_attack_multiplier()
                  << " | HEAL x" << player.get_cumulative_heal_multiplier()
                  << " | WEAPON +" << player.get_cumulative_weapon_bonus();

        std::cout << "\n\033[31m=== Enemy Status ===\033[0m\n";
        std::cout << "HP: " << enemy.get_hp() 
                  << " | Mana: " << enemy.get_mana()
                  << " | Armor: " << enemy.get_armor()
                  << " | Shields: " << enemy.get_shield_amount()
                  << "\nAbility: ";
        enemy.get_special_action_info();
        std::cout << " Uses :" << enemy.get_character().get_ability_uses();

        std::cout << "\nMultipliers: "
                  << "ATK x" << enemy.get_cumulative_attack_multiplier()
                  << " | HEAL x" << enemy.get_cumulative_heal_multiplier()
                  << " | WEAPON +" << enemy.get_cumulative_weapon_bonus();
        std::cout << "\n\033[36m=====================\033[0m\n";

        // Display action menu
        std::cout << "\n\033[35m=== Action Menu ===\033[0m"
                  << "\n1. Use card"
                  << "\n2. Use Special Ability"
                  << "\n3. Eat card"
                  << "\n4. Throw out card"
                  << "\n5. Show Character Characteristics"
                  << "\n6. End Turn"
                  << "\nChoice: ";
        
        int choice;
        std::cin >> choice;

        try {
            switch(choice) {
                case 1: {
                    std::cout << "Enter card index: ";
                    int index;
                    std::cin >> index;
                    player.use_card(index, enemy);

                    clear_screen();

                    break;
                }
                case 2: {
                    if(ability_used) throw std::runtime_error("Ability already used this turn!");
                    player.perform_special_action();
                    ability_used = true;

                    clear_screen();

                    std::cout << "Ability used! Remaining uses: " 
                             << player.get_character().get_ability_uses() << "\n";
                    break;
                }
                case 3: {
                    std::cout << "Enter card index to eat: ";
                    int index;
                    std::cin >> index;
                    player.eat_card(index);

                    clear_screen();

                    std::cout << "Card eaten! HP increased by " 
                             << (rarity_to_value(player.get_hand().get_card(index).get_rarity()) * 10)
                             << "\n";
                    break;
                }
                case 4: {
                    std::cout << "Enter card index to throw: ";
                    int index;
                    std::cin >> index;
                    player.throw_out(index);

                    clear_screen();

                    std::cout << "Card thrown out!\n";
                    break;
                }
                case 5: {
                    clear_screen();

                    std::cout << "\n\033[34m=== Your Status ===\033[0m"
                              << "\nHeal Multiplier X" << player.get_character().get_heal_multiplier()
                              << " | DMG multipler X" << player.get_character().get_dmg_multiplier()
                              << " | Armor Multiplier X" << player.get_character().get_armor_multiplier()
                              << "\nAbility: ";
                    player.get_special_action_info();
                    std::cout << "\n========================\n";
                    break;
                }
                case 6: {
                    player.set_turn_active(true);
                    clear_screen();
                    break;
                }
                default: {
                    clear_screen();

                    std::cout << "Invalid choice!\n";
                }
            }
        } 
        catch(const std::out_of_range& e) {
            clear_screen();
            std::cout << "\033[31mError: Invalid card index!\033[0m\n";
        }
        catch(const std::exception& e) {
            clear_screen();
            std::cout << "\033[31mError: " << e.what() << "\033[0m\n";
        }
        

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Auto-end turn if no resources left
        if(player.get_mana() <= 0 || player.get_hand().get_amount() == 0) {
            player.set_turn_active(true);
        }
        
    }
    
}

/**
 * @brief Runs a 1v1 match between two players with predefined characters and hands.
 */
void start_1v1_match() {

    clear_screen();

    std::string player_name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, player_name);
    
    std::string filename = "saves/"+player_name + ".dat";
    Human_Player player;

    player.load_characters(filename);

    if(player.get_characters().empty()) {
        std::cout << "No characters found. Creating starter pack...\n";
        
        // Healer
        player.add_character(std::make_unique<Healer_Character>(
            100, 1, 0, "Holy Priest", 
            1.2f, 0.9f, 1.0f, 
            "Basic healing class", 1
        ));
        
        // Tank
        player.add_character(std::make_unique<Tank_Character>(
            150, 1, 0, "Stone Guardian", 
            0.8f, 0.7f, 1.5f, 
            "Defensive tank class", 1, 3
        ));
        
        // Knight
        player.add_character(std::make_unique<Knight_Character>(
            120, 1, 0, "Silver Paladin", 
            1.0f, 1.1f, 1.2f, 
            "Balanced warrior class", 1, 20, 0
        ));
    }

    // Output characters
    std::cout << "\n=== Your Characters ===\n";

    player.show_characters();
    
    std::cout << "\nSelect character (1-" << player.get_characters().size() << "): ";
    
    int player_choice;
    std::cin >> player_choice;
    player_choice--;

    // set character to player
    auto& chars = player.get_characters(); 

    if (player_choice < 0 || static_cast<size_t>(player_choice) >= chars.size()) {
        throw std::out_of_range("Invalid character choice");
    }

    player.set_character(std::move(chars[player_choice]));


    chars.erase(chars.begin() + player_choice);

    Human_Player player1(100, 50, 0, player_name, std::move(player.release_character()));
    AI_Player player2(100, 50, 0, "Player 2", create_ai_character());
    
    // Generate initial hands for both players
    player1.get_hand().generate(4);
    player2.get_hand().generate(4);

    // Customization
    player1.customize_character(player1.get_character());

    bool game_over = false;

    clear_screen();

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
            player_turn(player1, player2);
        } else {
            std::cout << "Skipping Player 1's turn due to hand regeneration.\n";
        }

        // Check if Player 2 is defeated
        if (player2.get_hp() <= 0) {
            std::cout << "Player 1 wins!\n";
            int xp_gained = 100 + (player2.get_character().get_level() * 20);
            player1.get_character().add_xp(xp_gained);
            game_over = true;
            player1.end_turn();
            player2.end_turn();
            break;
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
            bool ability_used = false;
            if(player2.get_character().get_ability_uses() > 0 && !ability_used) {
                try{
                    player2.perform_special_action();
                    ability_used = true;
                } catch(...) {
                    // Skip if ability can't be used
                }
            }

            player2.set_turn_active(false);
            while (!player2.is_turn_active() && player2.get_hand().get_amount() > 0) {
                player2.get_hand().sort_by_mana();
                //////


                auto [second_card,first_card] = player2.find_best_combination();

                if ((first_card!=-1) && (second_card!=-1) && (second_card>first_card)){
                    second_card--;
                }

                try {
                    if(first_card != -1) {
                        player2.use_card(first_card, player2);
                        std::cout << "AI buffed with: " 
                                << player2.get_hand().get_card(first_card).get_name() << "\n";
                        
                        if(second_card != -1) {
                            player2.use_card(second_card, player1);
                            std::cout << "AI used: " 
                                    << player2.get_hand().get_card(second_card).get_name() << "\n";
                            }
                        }
                    } catch(...) {
                        std::cout<<"Very unexpected Error whem AI uses card"<<"/n";


                    }


                //////
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
        else {
            std::cout << "Skipping Player 2's turn due to hand regeneration.\n";
        }

        // Check if Player 1 is defeated
        if (player1.get_hp() <= 0) {
            std::cout << "Player 2 wins!\n";
            game_over = true;
            player1.end_turn();
            player2.end_turn();
            break;
        }

        char choice;

        // Option to give new cards
        std::cout << "\nGive new cards? (y/n): ";
        std::cin >> choice;
        clear_screen();
        if (choice == 'y' || choice == 'Y') {
            player1.get_hand().generate(4);
            player2.get_hand().generate(4);
        }
        
        player1.end_turn();
        player2.end_turn();
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (auto released = player1.release_character()) {
        player.add_character(std::move(released));
    }
    player.save_characters(filename);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Match ended.\n";
}