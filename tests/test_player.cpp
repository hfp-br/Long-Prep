/**
 * @file test_player.cpp
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo realiza os Gtests para o player do Long Prep.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <gtest/gtest.h>
#include "player.h"


//==================== TESTES DO CONSTRUTOR ====================//

// testa se o construtor armazena corretamente todos os valores
TEST(PlayerTest, ConstrutorGuardaValoresCorretamente) {

    atributes atributos{5, 4, 3, 2, 1};

    Mago player("Heroi", 20, 20, 6, 30.0f, true, true, 2, atributos);

    EXPECT_EQ(player.getName(), "Heroi");
    EXPECT_EQ(player.getLife(), 20);
    EXPECT_EQ(player.getLifeMax(), 20);
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


//==================== TESTES DE VIDA ====================//

// testa se a vida nao ultrapassa a vida maxima
TEST(PlayerTest, VidaNaoPassaDoMaximo) {

    atributes atributos{1, 1, 1, 1, 1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setLife(25);

    EXPECT_EQ(player.getLife(), 10);
}

// testa se vida negativa vira zero
TEST(PlayerTest, VidaNegativaViraZero) {

    atributes atributos{1, 1, 1, 1, 1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setLife(-5);

    EXPECT_EQ(player.getLife(), 0);
}


//==================== TESTES DE ATTACK SPEED ====================//

// testa se velocidade de ataque invalida volta para o valor padrao
TEST(PlayerTest, AttackSpeedInvalidoViraPadrao) {

    atributes atributos{1, 1, 1, 1, 1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setAttackSpeed(-2.0f);

    EXPECT_FLOAT_EQ(player.getAttackSpeed(), 1.0f);
}

// testa se o timer de ataque acumula corretamente
TEST(PlayerTest, AttackTimerAcumulaEReseta) {

    atributes atributos{1,1,1,1,1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    // acumula tempo de ataque
    player.tickAttackTimer(0.5f);
    player.tickAttackTimer(0.3f);

    EXPECT_FLOAT_EQ(player.getAttackTimer(), 0.8f);

    // reseta o timer
    player.resetAttackTimer();

    EXPECT_FLOAT_EQ(player.getAttackTimer(), 0.0f);
}

// testa se a velocidade base de ataque atualiza corretamente
TEST(PlayerTest, BaseAttackSpeedAtualiza) {

    atributes atributos{1,1,1,1,1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setBaseAttackSpeed(0.8f);

    EXPECT_FLOAT_EQ(player.getBaseAttackSpeed(), 0.8f);
}

// testa se velocidade base invalida volta para o padrao
TEST(PlayerTest, BaseAttackSpeedInvalidoViraPadrao) {

    atributes atributos{1,1,1,1,1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setBaseAttackSpeed(-1.0f);

    EXPECT_FLOAT_EQ(player.getBaseAttackSpeed(), 1.0f);
}


//==================== TESTES DE ATRIBUTOS ====================//

// testa se os atributos atualizam corretamente
TEST(PlayerTest, AtributosAtualizam) {

    atributes atributos{1,1,1,1,1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setAtributoforca(10);
    player.setAtributodestreza(8);
    player.setAtributoconstituicao(6);
    player.setAtributointeligencia(4);
    player.setAtributosorte(2);

    EXPECT_EQ(player.getAtributoforca(), 10);
    EXPECT_EQ(player.getAtributodestreza(), 8);
    EXPECT_EQ(player.getAtributoconstituicao(), 6);
    EXPECT_EQ(player.getAtributointeligencia(), 4);
    EXPECT_EQ(player.getAtributosorte(), 2);
}


//==================== TESTES DE LEVEL E XP ====================//

// testa se level e xp atualizam corretamente
TEST(PlayerTest, LevelEXpAtualizam) {

    atributes atributos{1,1,1,1,1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setlevel(5);
    player.setXp(100);

    EXPECT_EQ(player.getLevel(), 5);
    EXPECT_EQ(player.getXp(), 100);
}

// testa se o xp necessario para o proximo level atualiza
TEST(PlayerTest, XpForNextLevelAtualiza) {

    atributes atributos{1,1,1,1,1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setxpfornextlevel(50);

    EXPECT_EQ(player.getxpfornextlevel(), 50);
}

// testa se os pontos nao gastos atualizam corretamente
TEST(PlayerTest, UnspentPointsAtualizam) {

    atributes atributos{1,1,1,1,1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setunspentpoints(3);

    EXPECT_EQ(player.getunspentpoints(), 3);
}


//==================== TESTES DE COMBATE ====================//

// testa se o dano atualiza corretamente
TEST(PlayerTest, SetDamageAtualiza) {

    atributes atributos{1,1,1,1,1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);
    
    player.setDamage(15);

    EXPECT_EQ(player.getDamage(), 15);
}

// testa se a defesa atualiza corretamente
TEST(PlayerTest, DefesaAtualiza) {

    atributes atributos{1,1,1,1,1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setDefense(10);

    EXPECT_EQ(player.getDefense(), 10);
}


//==================== TESTES DE INVENTARIO ====================//

// testa se o peso atual carregado atualiza corretamente
TEST(PlayerTest, PesoAtualiza) {

    atributes atributos{1,1,1,1,1};

    Mago player("Heroi", 10, 20, 5, 30.0f, true, true, 0, atributos);

    player.setcurrent_weight(7.5f);

    EXPECT_FLOAT_EQ(player.getCurrent_weight(), 7.5f);
}