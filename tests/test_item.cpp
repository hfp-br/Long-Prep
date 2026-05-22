#include <gtest/gtest.h>
#include "item.h"

using namespace RPG;

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

TEST(ItemTest, ArmorGuardaDefesaCorretamente) {
    Armor armadura("Armadura", 5.0f, 4, true, false, 7, uncommon);

    EXPECT_EQ(armadura.getName(), "Armadura");
    EXPECT_EQ(armadura.getDefense(), 7);
    EXPECT_TRUE(armadura.isEquipable());
    EXPECT_EQ(armadura.getRarity(), uncommon);
}

TEST(ItemTest, OperatorMenorComparaRaridade) {
    Weapon comum("Comum", 1, 1, true, false, 5, 1, sword, 1, common);
    Weapon raro("Raro", 1, 1, true, false, 5, 1, sword, 1, rare);

    EXPECT_TRUE(comum < raro);
    EXPECT_FALSE(raro < comum);
}

TEST(ItemTest, PocoesRetornamEfeitoCorreto) {
    Potion_Health vida("Pocao vida", 1, 1);
    Potion_Speed velocidade("Pocao speed", 1, 1);
    Potion_Luck sorte("Pocao sorte", 1, 1);

    EXPECT_EQ(vida.EfeitoPocao(), 1);
    EXPECT_EQ(velocidade.EfeitoPocao(), 2);
    EXPECT_EQ(sorte.EfeitoPocao(), 3);
}