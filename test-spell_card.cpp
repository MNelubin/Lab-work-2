/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include <gtest/gtest.h>
#include "spell_card.h"
#include "enums.h"

/**
 * @test Проверка корректности работы конструктора и геттеров
 * @brief Тестирует инициализацию параметров через конструктор
 * @pre Создание объекта Spell_Card с параметрами:
 *      - Имя: "Fireball"
 *      - Элемент: Fire
 *      - Стоимость маны: 5
 * @post Все параметры должны соответствовать заданным значениям
 */
TEST(SpellCardTest, ConstructorAndGetters) {
    // Arrange
    const std::string expected_name = "Fireball";
    const int expected_mana = 5;
    const Element expected_element = Element::Fire;
    
    // Act
    Spell_Card fireball(expected_name, "Deals 5 damage", 
                       Rarity::Epic, expected_mana, expected_element);
    
    // Assert
    EXPECT_EQ(fireball.get_name(), expected_name);
    EXPECT_EQ(fireball.get_element(), expected_element);
    EXPECT_EQ(fireball.get_mana_cost(), expected_mana);
}

/**
 * @test Тест модификатора элемента
 * @brief Проверяет корректность изменения элемента карты
 * @pre Исходный элемент: Water
 * @post После установки Air: элемент должен быть Air
 * @post После установки Earth: элемент не должен быть Fire
 */
TEST(SpellCardTest, ElementModification) {
    // Arrange
    Spell_Card spell("Basic", "Test", Rarity::Common, 2, Element::Water);
    
    // Act & Assert: Первое изменение
    spell.set_element(Element::Air);
    EXPECT_EQ(spell.get_element(), Element::Air);
    
    // Act & Assert: Второе изменение
    spell.set_element(Element::Earth);
    EXPECT_NE(spell.get_element(), Element::Fire);
}

/**
 * @brief Точка входа для Google Test
 * @param argc Количество аргументов
 * @param argv Аргументы командной строки
 * @return Результат выполнения всех тестов
 */
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 