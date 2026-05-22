#include <gtest/gtest.h>
#include "player.h"

TEST(PlayerTest, ConstrutorGuardaValoresCorretamente) {
    atributes atributos{5, 4, 3, 2, 1};

    Player player("Heroi", 20, 20, 6, 30.0f, true, true, 2, atributos);

    EXPECT_EQ(player.getName(), "Heroi");
    EXPECT_EQ(player.getLife(), 20);
    EXPECT_EQ(player.getLife_max(), 20);
    EXPECT_EQ(player.getDamage(), 6);
    EXPECT_FLOAT_EQ(player.getWeight_Capacity(), 30.0f);
    EXPECT_TRUE(player.isBackpack());
    EXPECT_TRUE(player.isAlive());
    EXPECT_EQ(player.getDefense(), 2);

    EXPECT_EQ(player.getAtributoforca(), 5);
    EXPECT_EQ(player.getAtributoconstituicao(), 4);
    EXPECT_EQ(player.getAtributodestreza(), 3);
    EXPECT_EQ(player.getAtributointeligencia(), 2);
    EXPECT_EQ(player.getAtributosorte(), 1);
}

TEST(PlayerTest, VidaNaoPassaDoMaximo) {
    atributes atributos{1, 1, 1, 1, 1};

    Player player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setLife(25);

    EXPECT_EQ(player.getLife(), 10);
}

TEST(PlayerTest, VidaNegativaViraZero) {
    atributes atributos{1, 1, 1, 1, 1};

    Player player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setLife(-5);

    EXPECT_EQ(player.getLife(), 0);
}

TEST(PlayerTest, AttackSpeedInvalidoViraPadrao) {
    atributes atributos{1, 1, 1, 1, 1};

    Player player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setAttackSpeed(-2.0f);

    EXPECT_FLOAT_EQ(player.getAttackSpeed(), 1.0f);
}