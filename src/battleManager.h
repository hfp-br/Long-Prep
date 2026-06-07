#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "player.h"
#include "enemy.h"
#include <vector>
#include "box2d/id.h"

struct RunContext {
    int faseAtual = 0;
    int contadorfases = 0;
    InimigoComp* inimigo = nullptr;
    std::vector<b2BodyId> itensEquipadosIds;

    int playerHitsRestantes = 0;
    int enemyHitsRestantes = 0;

    bool turnoEmAndamento = false;
    bool Playerjaatacou = false;
    bool Enemyjaatacou = false;
    bool turnoInimigo = false;
    float timerPlayerAtacou = 0.0f;
    float timerEnemyAtacou  = 0.0f;
    const float duracaoFrameAtaque = 0.35f;
    Texture2D hitEffectTex;
    float hitEffectTimer   = 0.0f;
    const float hitEffectDuracao = 0.25f;

    bool skillAtiva = false;
    int bonusDamageSkill = 0;
    int bonusSorteSkill = 0;
    float bonusAttackSpeedSkill = 0.0f;
};

class AttackStrategy{
public:
    virtual int calcularDano(Player& player, Enemy& enemy)=0;
};

class GuerreiroAttack : public AttackStrategy{
public:
    virtual int calcularDano(Player& player, Enemy& enemy) override;
};

class MagoAttack : public AttackStrategy{
public:
    virtual int calcularDano(Player& player, Enemy& enemy) override;
};

class CurandeiroAttack : public AttackStrategy{
public:
    virtual int calcularDano(Player& player, Enemy& enemy) override;
};

class LadraoAttack : public AttackStrategy{
public:
    virtual int calcularDano(Player& player, Enemy& enemy) override;
};

void BattleManager(RunContext& runc,float dt,Player& player,Enemy& inimigo,AttackStrategy& attackStrategy,bool playerAtacar,bool playerSkill,int bonuspocaodano);

#endif