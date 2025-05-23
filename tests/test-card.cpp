/* Maxim Nelyubin st132907@student.spbu.ru
    Lab-2
*/
#include <gtest/gtest.h>
#include <sstream>
#include "cards/card.h"
#include "cards/spell_card.h"
#include "cards/enums.h"
#include "cards/attack_spell_card.h"
#include "cards/heal_spell_card.h"
#include "cards/buff_spell_card.h"
#include "cards/defence_spell_card.h"
#include "cards/beast_card.h"
#include "cards/creature_card.h"
#include "cards/weapon_card.h"
#include "cards/artifact_card.h"
#include "cards/shield_card.h"
#include "cards/buff_card.h"
#include "player/hand.h"
#include "player/player.h"
#include "player/character.h"
#include "player/tank_character.h"
#include "player/healer_character.h"
#include "player/knight_character.h"
#include "player/ai_player.h"
#include "player/human_player.h"

/**
 * @test Sanity Check: Verify basic functionality of the project
 * @addtogroup SanityCheck
 */
TEST(SanityCheck, BasicFunctionality) {

    EXPECT_EQ(1, 1);

}