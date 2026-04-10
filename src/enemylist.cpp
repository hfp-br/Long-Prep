#include <iostream>
#include <string>
#include "enemy.h"

Enemy Regular("Regular",40,40,0,0,15,1,1);
Enemy Fast("Fast",25,25,0,0,10,0.5,1);
Enemy Tank("Tank",150,150,0,0,5,1,1);
Enemy Juggernaut("Juggernaut",75,75,5,0,20,2,2);
Enemy Archer("Archer",30,30,0,1,25,1,2);
Enemy Ninja("Ninja",40,40,5,0,15,0.5,2);
Enemy Colossus("Colossus",300,300,0,0,20,3,3);
Enemy Knight("Knight",150,150,7,0,15,0.5,3);
Enemy Defender("Defender",150,150,0,0,15,1,3);
Enemy Dragon("Dragon",500,500,10,0,50,5,4);