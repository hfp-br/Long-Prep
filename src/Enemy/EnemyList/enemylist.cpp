#include <string>
#include "enemy.h"
#include "raylib.h"

Enemy Regular("Regular",40,40,0,0,15,1,1,10);
Enemy Fast("Fast",25,25,0,0,10,(float)0.5,1,5);
Enemy Tank("Tank",150,150,0,0,5,1,1,15);
Enemy Juggernaut("Juggernaut",75,75,5,0,20,2,2,35);
Enemy Archer("Archer",30,30,0,1,25,1,2,25);
Enemy Ninja("Ninja",40,40,5,0,15,(float)0.5,2,40);
Enemy Colossus("Colossus",300,300,0,0,20,3,3,60);
Enemy Knight("Knight",150,150,7,0,15,(float)0.5,3,70);
Enemy Defender("Defender",150,150,0,0,15,1,3,50);
Enemy Dragon("Dragon",500,500,10,0,50,5,4,250);

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


void InitEnemyList() {
    //REGULAR
    RegularComp.texturaP = LoadTexture("images/enemy/comumP.png");
    RegularComp.texturaD = LoadTexture("images/enemy/comumD.png");
    RegularComp.texturaA = LoadTexture("images/enemy/comumA.png");

    //FAST
    FastComp.texturaP=LoadTexture("images/enemy/ladraoP.png");
    FastComp.texturaD=LoadTexture("images/enemy/ladraoD.png");
    FastComp.texturaA=LoadTexture("images/enemy/ladraoA.png");
    
    //TANK
    TankComp.texturaP=LoadTexture("images/enemy/tankP.png");
    TankComp.texturaD=LoadTexture("images/enemy/tankD.png");
    TankComp.texturaA=LoadTexture("images/enemy/tankA.png");
    
    //JUGGERNAUT
    JuggernautComp.texturaP=LoadTexture("images/enemy/juggernautP.png");
    JuggernautComp.texturaD=LoadTexture("images/enemy/juggernautD.png");
    JuggernautComp.texturaA=LoadTexture("images/enemy/juggernautA.png");
    
    //ARCHER
    ArcherComp.texturaP=LoadTexture("images/enemy/archerP.png");
    ArcherComp.texturaD=LoadTexture("images/enemy/archerD.png");
    ArcherComp.texturaA=LoadTexture("images/enemy/archerA.png");
    
    //NINJA
    NinjaComp.texturaP=LoadTexture("images/enemy/ninjaP.png");
    NinjaComp.texturaD=LoadTexture("images/enemy/ninjaD.png");
    NinjaComp.texturaA=LoadTexture("images/enemy/ninjaA.png");
    
    //COLOSSUS
    ColossusComp.texturaP=LoadTexture("images/enemy/ColossusP.png");
    ColossusComp.texturaD=LoadTexture("images/enemy/colossusD.png");
    ColossusComp.texturaA=LoadTexture("images/enemy/colossusA.png");
    
    //KNIGHT
    KnightComp.texturaP=LoadTexture("images/enemy/knightP.png");
    KnightComp.texturaD=LoadTexture("images/enemy/knightD.png");
    KnightComp.texturaA=LoadTexture("images/enemy/knightA.png");
    
    //DEFENDER
    DefenderComp.texturaP=LoadTexture("images/enemy/defenderP.png");
    DefenderComp.texturaD=LoadTexture("images/enemy/defenderD.png");
    DefenderComp.texturaA=LoadTexture("images/enemy/defenderA.png");

    //DRAGON
    DragonComp.texturaP=LoadTexture("images/enemy/dragonP.png");
    DragonComp.texturaD=LoadTexture("images/enemy/dragonD.png");
    DragonComp.texturaA=LoadTexture("images/enemy/dragonA.png");
}

