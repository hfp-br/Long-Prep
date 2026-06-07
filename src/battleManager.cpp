#include "player.h"
#include "enemy.h"
#include "battleManager.h"

using namespace std;

int GuerreiroAttack::calcularDano (Player& player, Enemy& enemy){
    return player.getDamage() +
            player.getAtributoforca() -
            enemy.getDefense();
}

int MagoAttack::calcularDano(Player& player, Enemy& enemy){
    return player.getDamage() +
            player.getAtributointeligencia() -
            enemy.getDefense()/2;
}

int CurandeiroAttack::calcularDano(Player& player, Enemy& enemy){
    return player.getDamage() -
            enemy.getDefense();
}

int LadraoAttack::calcularDano(Player& player, Enemy& enemy){
    return player.getDamage() +
            player.getAtributodestreza() -
            enemy.getDefense();
}

static void atualizarTimers(RunContext& runc, float dt, Player& player, Enemy& inimigo){
player.tickAttackTimer(dt);
inimigo.tickAttackTimer(dt);

    if(runc.timerPlayerAtacou > 0.0f){
        runc.timerPlayerAtacou -= dt;

        if(runc.timerPlayerAtacou <= 0.0f){
            runc.Playerjaatacou = false;
        }
    }

    if(runc.timerEnemyAtacou > 0.0f){
        runc.timerEnemyAtacou -= dt;

        if(runc.timerEnemyAtacou <= 0.0f){
            runc.Enemyjaatacou = false;
        }
    }

    if(runc.hitEffectTimer > 0.0f){
        runc.hitEffectTimer -= dt;
    }
}

static void iniciarTurnoPlayer(RunContext& runc, Player& player, Enemy& inimigo){
    runc.playerHitsRestantes = max(1, (int)(1.0f / player.getAttackSpeed()));
    runc.enemyHitsRestantes = max(1, (int)(1.0f / inimigo.getAttackSpeed()));

    runc.turnoEmAndamento = true;
    runc.turnoInimigo = false;

    runc.Playerjaatacou = false;
    runc.Enemyjaatacou = false;

    runc.timerPlayerAtacou = 0.0f;
    runc.timerEnemyAtacou = 0.0f;

    player.resetAttackTimer();
    inimigo.resetAttackTimer();
}

static void processarAtaquePlayer(RunContext& runc,Player& player,Enemy& inimigo,AttackStrategy& attackStrategy,int bonuspocaodano){
    if(player.getAttackTimer() < 0.25f){
        return;
    }

    int dano = attackStrategy.calcularDano(player, inimigo) + bonuspocaodano;
    dano = max(0, dano);
    if(player.getContadorSkill() > 0){
        player.setContadorSkill(player.getContadorSkill() - 1);
    }

    inimigo.setLife(inimigo.getLife() - dano);

    runc.Playerjaatacou = true;
    runc.Enemyjaatacou = false;

    runc.timerPlayerAtacou = runc.duracaoFrameAtaque;
    runc.timerEnemyAtacou = 0.0f;

    runc.hitEffectTimer = runc.hitEffectDuracao;

    runc.playerHitsRestantes--;
    player.resetAttackTimer();

    if(inimigo.getLife() <= 0){
        runc.turnoEmAndamento = false;
        return;
    }

    if(runc.playerHitsRestantes <= 0){
        runc.turnoInimigo = true;
        inimigo.resetAttackTimer();
    }
}

static void processarAtaqueInimigo(RunContext& runc, Player& player, Enemy& inimigo){
    if(inimigo.getAttackTimer() < 0.35f){
        return;
    }

    float def = (float)(player.getDefense() + player.getAtributoconstituicao());
    float reducao = def / (def + 33.3f);

    int dano = max(1, (int)(inimigo.getDamage() * (1.0f - reducao)));

    player.setLife(player.getLife() - dano);

    runc.Enemyjaatacou = true;
    runc.Playerjaatacou = false;

    runc.timerEnemyAtacou = runc.duracaoFrameAtaque;
    runc.timerPlayerAtacou = 0.0f;

    runc.enemyHitsRestantes--;
    inimigo.resetAttackTimer();

    if(player.getLife() <= 0){
        runc.turnoEmAndamento = false;
        return;
    }

    if(runc.enemyHitsRestantes <= 0){
        runc.turnoEmAndamento = false;
        runc.turnoInimigo = false;
    }
}


void BattleManager(RunContext& runc,float dt,Player& player,Enemy& inimigo,AttackStrategy& attackStrategy,bool playerAtacar,bool playerSkill,int bonuspocaodano){
    atualizarTimers(runc, dt, player, inimigo);

    if(!runc.turnoEmAndamento && playerAtacar){
        iniciarTurnoPlayer(runc, player, inimigo);
    }

    if(!runc.turnoEmAndamento && playerSkill && player.getContadorSkill()<=0){
        player.usarHabilidade();
        player.setContadorSkill(3);
        runc.skillAtiva = true;
        runc.turnoEmAndamento = true;
        runc.turnoInimigo = true;
        player.resetAttackTimer();
        inimigo.resetAttackTimer();
    }

    if(!runc.turnoEmAndamento){
        return;
    }

    if(!runc.turnoInimigo){
        processarAtaquePlayer(runc, player, inimigo, attackStrategy, bonuspocaodano);
        return;
    }

    processarAtaqueInimigo(runc, player, inimigo);
}