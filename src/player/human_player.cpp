/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include "../../include/player/character.h"
#include "../../include/player/tank_character.h"
#include "../../include/player/healer_character.h"
#include "../../include/player/knight_character.h"
#include "../../include/player/human_player.h"
#include <fstream>
#include <iostream>


Human_Player::Human_Player()
    : Player(100, 50, 0, "Player", nullptr, 0) {}

Human_Player::Human_Player(int hp, int mana, int armor, const std::string& name,
                           std::unique_ptr<Character> character, int shield_amount)
    : Player(hp, mana, armor, name, std::move(character), shield_amount) {}





void Human_Player::save_characters(const std::string& filename) const
{
    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to create save file.\n";
        return;
    }


    int num_chars = characters.size();
    file.write(reinterpret_cast<const char*>(&num_chars), sizeof(num_chars));


    for (const auto& char_ptr : characters)
    {
        const std::string type_name = typeid(*char_ptr).name();
        size_t name_len = type_name.size();
        file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        file.write(type_name.c_str(), name_len);
        char_ptr->serialize(file);
    }
}


void Human_Player::load_characters(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cout << "No save data found.\n";
        return;
    }

    int num_chars;
    file.read(reinterpret_cast<char*>(&num_chars), sizeof(num_chars));


    for (int i = 0; i < num_chars; ++i)
    {
        size_t name_len;
        file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        std::string type_name(name_len, '\0');
        file.read(&type_name[0], name_len);

        std::unique_ptr<Character> character;
        if (type_name == typeid(Healer_Character).name())
        {
            auto healer = std::make_unique<Healer_Character>();
            healer->deserialize(file);
            character = std::move(healer);
        }
        else if (type_name == typeid(Knight_Character).name())
        {
            auto knight = std::make_unique<Knight_Character>();
            knight->deserialize(file);
            character = std::move(knight);
        }
        else if (type_name == typeid(Tank_Character).name())
        {
            auto tank = std::make_unique<Tank_Character>();
            tank->deserialize(file);
            character = std::move(tank);
        }
        else
        {
            std::cerr << "Unknown character type: " << type_name << "\n";
            continue;
        }

        characters.push_back(std::move(character));
    }
}


void Human_Player::add_character(std::unique_ptr<Character> character)
{
    characters.push_back(std::move(character));
}



std::vector<std::unique_ptr<Character>>& Human_Player::get_characters()
{
    return characters;
}

void Human_Player::show_characters() const
{
    std::cout << "\nAvailable characters:\n";
    for(size_t i = 0; i < characters.size(); ++i)
    {
        const auto& c = *characters[i];
        std::cout << "[" << i+1 << "] " << c.get_name()
                  << " (Level " << c.get_level()
                  << " | XP: " << c.get_xp() << "/" << c.get_xp_to_next_lvl() << ") | "
                  << "Class: " << c.get_class_name() << " | "
                  << "Heal MTLPR: " << c.get_heal_multiplier() << " | "
                  << "DMG MTLPR: " << c.get_dmg_multiplier() << " | "
                  << "Armor MTLPR: " << c.get_armor_multiplier() << " | "
                  << "Description: " << c.get_description() << "\n";
    }
}


void Human_Player::customize_character(Character& character)
{
    char choice;
    std::cout << "\nDo you want to customize this character? (y/n): ";
    std::cin >> choice;
    std::cin.ignore(); // Очистка буфера

    if(tolower(choice) != 'y') return;

    while(true)
    {
        std::cout << "\n=== Customization Menu ==="
                  << "\n1. Change name"
                  << "\n2. Change description"
                  << "\n3. Finish customization"
                  << "\nChoose option: ";

        int option;
        std::cin >> option;
        std::cin.ignore(); // Очистка буфера

        switch(option)
        {
        case 1:
        {
            std::cout << "Enter new name (max 50 chars): ";
            std::string new_name;
            std::getline(std::cin, new_name);
            character.set_name(new_name);
            break;
        }
        case 2:
        {
            std::cout << "Enter new description (max 200 chars): ";
            std::string new_desc;
            std::getline(std::cin, new_desc);
            character.set_description(new_desc);
            break;
        }
        case 3:
            std::cout << "Final character stats:\n"
                      << character.get_character_statistics() << "\n";
            return;
        default:
            std::cout << "Invalid option!\n";
        }
    }
}

std::unique_ptr<Character> Human_Player::release_character()
{
    return std::move(character);
}