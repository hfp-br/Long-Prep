/**
 * @file enemylist.cpp
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo cria os templates dos inimigos usados no jogo e atribui suas respectivas texturas.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <string>
#include "enemy.h"
#include "raylib.h"

//==================== TEMPLATES DOS INIMIGOS ====================//
// nome, hp, hpMax, defesa, range, dano, velocidade, tier, xp

// inimigo comum balanceado
Enemy Regular("Regular",40,40,0,0,15,1,1,10);

// inimigo rapido com pouco hp
Enemy Fast("Fast",25,25,0,0,10,(float)0.5,1,5);

// inimigo lento com bastante vida
Enemy Tank("Tank",150,150,0,0,5,1,1,15);

// inimigo pesado com mais dano
Enemy Juggernaut("Juggernaut",75,75,5,0,20,2,2,35);

// inimigo ranged focado em ataque a distancia
Enemy Archer("Archer",30,30,0,1,25,1,2,25);

// inimigo rapido com defesa adicional
Enemy Ninja("Ninja",40,40,5,0,15,(float)0.5,2,40);

// inimigo gigante com muito hp
Enemy Colossus("Colossus",300,300,0,0,20,3,3,60);

// inimigo defensivo com armadura alta
Enemy Knight("Knight",150,150,7,0,15,(float)0.5,3,70);

// inimigo focado em defesa e sustain
Enemy Defender("Defender",150,150,0,0,15,1,3,50);

// boss final com status elevados
Enemy Dragon("Dragon",500,500,10,0,50,5,4,250);


//==================== COMPONENTES DOS INIMIGOS ====================//
// estrutura que junta o template do inimigo com suas texturas

InimigoComp RegularComp{Regular,{0},{0},{0}};
InimigoComp FastComp{Fast,{0},{0},{0}};
InimigoComp TankComp{Tank,{0},{0},{0}};
InimigoComp JuggernautComp{Juggernaut,{0},{0},{0}};
InimigoComp ArcherComp{Archer,{0},{0},{0}};
InimigoComp NinjaComp{Ninja,{0},{0},{0}};
InimigoComp ColossusComp{Colossus,{0},{0},{0}};
InimigoComp KnightComp{Knight,{0},{0},{0}};
InimigoComp DefenderComp{Defender,{0},{0},{0}};
InimigoComp DragonComp{Dragon,{0},{0},{0}};


//==================== CARREGAMENTO DAS TEXTURAS ====================//

void InitEnemyList() {

    //==================== REGULAR ====================//

    // textura parada
    RegularComp.texturaP = LoadTexture("images/enemy/comumP.png");

    // textura tomando dano
    RegularComp.texturaD = LoadTexture("images/enemy/comumD.png");

    // textura atacando
    RegularComp.texturaA = LoadTexture("images/enemy/comumA.png");


    //==================== FAST ====================//

    // textura parada
    FastComp.texturaP=LoadTexture("images/enemy/ladraoP.png");

    // textura tomando dano
    FastComp.texturaD=LoadTexture("images/enemy/ladraoD.png");

    // textura atacando
    FastComp.texturaA=LoadTexture("images/enemy/ladraoA.png");
    

    //==================== TANK ====================//

    // textura parada
    TankComp.texturaP=LoadTexture("images/enemy/tankP.png");

    // textura tomando dano
    TankComp.texturaD=LoadTexture("images/enemy/tankD.png");

    // textura atacando
    TankComp.texturaA=LoadTexture("images/enemy/tankA.png");
    

    //==================== JUGGERNAUT ====================//

    // textura parada
    JuggernautComp.texturaP=LoadTexture("images/enemy/juggernautP.png");

    // textura tomando dano
    JuggernautComp.texturaD=LoadTexture("images/enemy/juggernautD.png");

    // textura atacando
    JuggernautComp.texturaA=LoadTexture("images/enemy/juggernautA.png");
    

    //==================== ARCHER ====================//

    // textura parada
    ArcherComp.texturaP=LoadTexture("images/enemy/archerP.png");

    // textura tomando dano
    ArcherComp.texturaD=LoadTexture("images/enemy/archerD.png");

    // textura atacando
    ArcherComp.texturaA=LoadTexture("images/enemy/archerA.png");
    

    //==================== NINJA ====================//

    // textura parada
    NinjaComp.texturaP=LoadTexture("images/enemy/ninjaP.png");

    // textura tomando dano
    NinjaComp.texturaD=LoadTexture("images/enemy/ninjaD.png");

    // textura atacando
    NinjaComp.texturaA=LoadTexture("images/enemy/ninjaA.png");
    

    //==================== COLOSSUS ====================//

    // textura parada
    ColossusComp.texturaP=LoadTexture("images/enemy/ColossusP.png");

    // textura tomando dano
    ColossusComp.texturaD=LoadTexture("images/enemy/colossusD.png");

    // textura atacando
    ColossusComp.texturaA=LoadTexture("images/enemy/colossusA.png");
    

    //==================== KNIGHT ====================//

    // textura parada
    KnightComp.texturaP=LoadTexture("images/enemy/knightP.png");

    // textura tomando dano
    KnightComp.texturaD=LoadTexture("images/enemy/knightD.png");

    // textura atacando
    KnightComp.texturaA=LoadTexture("images/enemy/knightA.png");
    

    //==================== DEFENDER ====================//

    // textura parada
    DefenderComp.texturaP=LoadTexture("images/enemy/defenderP.png");

    // textura tomando dano
    DefenderComp.texturaD=LoadTexture("images/enemy/defenderD.png");

    // textura atacando
    DefenderComp.texturaA=LoadTexture("images/enemy/defenderA.png");


    //==================== DRAGON ====================//

    // textura parada
    DragonComp.texturaP=LoadTexture("images/enemy/dragonP.png");

    // textura tomando dano
    DragonComp.texturaD=LoadTexture("images/enemy/dragonD.png");

    // textura atacando
    DragonComp.texturaA=LoadTexture("images/enemy/dragonA.png");
}