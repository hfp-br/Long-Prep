/**
 * @file test_item.cpp
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo realiza os Gtests para os itens do Long Prep.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <gtest/gtest.h>
#include "item.h"
#include <sstream>

using namespace RPG;


//==================== TESTES DE WEAPON ====================//

// testa se a arma guarda corretamente seus valores
TEST(ItemTest, WeaponGuardaValoresCorretamente) {
    Weapon espada("Espada", 2.5f, 3, true, false, 10, 1, sword, 1.2f, rare);

    EXPECT_EQ(espada.getName(), "Espada");
    EXPECT_FLOAT_EQ(espada.getWeight(), 2.5f);
    EXPECT_EQ(espada.getSize(), 3);
    EXPECT_TRUE(espada.isEquipable());
    EXPECT_FALSE(espada.isConsumable());
    EXPECT_EQ(espada.getDamage(), 10);
    EXPECT_EQ(espada.getRange(), 1);
    EXPECT_EQ(espada.getType(), sword);
    EXPECT_FLOAT_EQ(espada.getAttackSpeed(), 1.2f);
    EXPECT_EQ(espada.getRarity(), rare);
}


//==================== TESTES DE ARMOR ====================//

// testa se a armadura guarda corretamente sua defesa
TEST(ItemTest, ArmorGuardaDefesaCorretamente) {
    Armor armadura("Armadura", 5.0f, 4, true, false, 7, uncommon);

    EXPECT_EQ(armadura.getName(), "Armadura");
    EXPECT_EQ(armadura.getDefense(), 7);
    EXPECT_TRUE(armadura.isEquipable());
    EXPECT_EQ(armadura.getRarity(), uncommon);
}

// testa se a armadura nao e consumivel
TEST(ItemTest, ArmorNaoEConsumivel) {
    Armor armadura("Armadura", 5.0f, 4, true, false, 7, uncommon);
    EXPECT_FALSE(armadura.isConsumable());
}


//==================== TESTES DE OPERADORES ====================//

// testa se o operador < compara itens pela raridade
TEST(ItemTest, OperatorMenorComparaRaridade) {
    Weapon comum("Comum", 1, 1, true, false, 5, 1, sword, 1, common);
    Weapon raro("Raro", 1, 1, true, false, 5, 1, sword, 1, rare);

    EXPECT_TRUE(comum < raro);
    EXPECT_FALSE(raro < comum);
}

// testa se raridades iguais nao contam como menor
TEST(ItemTest, OperatorMenorIgualRaridadeNaoEMenor) {
    Weapon a("A", 1, 1, true, false, 5, 1, sword, 1, rare);
    Weapon b("B", 1, 1, true, false, 5, 1, sword, 1, rare);

    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

// testa se a ordem completa das raridades esta funcionando
TEST(ItemTest, RaridadeOrdemCompleta) {
    Weapon c("C", 1,1,true,false,5,1,sword,1, common);
    Weapon uc("UC",1,1,true,false,5,1,sword,1, uncommon);
    Weapon r("R", 1,1,true,false,5,1,sword,1, rare);
    Weapon ep("EP",1,1,true,false,5,1,sword,1, epic);
    Weapon l("L", 1,1,true,false,5,1,sword,1, legendary);

    EXPECT_TRUE(c  < uc);
    EXPECT_TRUE(uc < r);
    EXPECT_TRUE(r  < ep);
    EXPECT_TRUE(ep < l);
}

// testa se o operador << imprime informacoes importantes do item
TEST(ItemTest, OperatorStreamSaida) {
    Weapon espada("Espada", 2.5f, 3, true, false, 10, 1, sword, 1.0f, rare);

    std::ostringstream oss;
    oss << espada;
    std::string saida = oss.str();

    EXPECT_NE(saida.find("Espada"), std::string::npos);
    EXPECT_NE(saida.find("2.5"), std::string::npos);
}


//==================== TESTES DE POCOES ====================//

// testa se algumas pocoes retornam seus efeitos corretos
TEST(ItemTest, PocoesRetornamEfeitoCorreto) {
    Potion_Health vida("Pocao vida", 1, 1);
    Potion_Speed velocidade("Pocao speed", 1, 1);
    Potion_Luck sorte("Pocao sorte", 1, 1);

    EXPECT_EQ(vida.EfeitoPocao(), 1);
    EXPECT_EQ(velocidade.EfeitoPocao(), 2);
    EXPECT_EQ(sorte.EfeitoPocao(), 3);
}

// testa as pocoes restantes
TEST(ItemTest, TodasPocoesRetornamEfeitoCorreto) {
    Potion_Damage dano("Pocao dano", 1, 1);
    Potion_Mult mult("Pocao mult", 1, 1);

    EXPECT_EQ(dano.EfeitoPocao(), 0);
    EXPECT_EQ(mult.EfeitoPocao(), 4);
}


//==================== TESTES DE INGREDIENT ====================//

// testa se o ingrediente retorna o tipo de craft correto
TEST(ItemTest, IngredientGetCraftType) {
    Ingredient base(5, "Base", 0.2f, 1, false, true);
    Ingredient dano(0, "Dano", 0.4f, 1, false, true);

    EXPECT_EQ(base.getCraftType(), 5);
    EXPECT_EQ(dano.getCraftType(), 0);
}

// testa se o tipo de craft do ingrediente pode ser alterado
TEST(ItemTest, IngredientSetType) {
    Ingredient ing(0, "Ingrediente", 0.2f, 1, false, true);
    ing.setType(3);

    EXPECT_EQ(ing.getCraftType(), 3);
}


//==================== TESTES DE CONSUMO ====================//

// testa se arma nao e consumivel
TEST(ItemTest, WeaponNaoEConsumivel) {
    Weapon espada("Espada", 2.5f, 3, true, false, 10, 1, sword, 1.2f, rare);
    EXPECT_FALSE(espada.isConsumable());
}