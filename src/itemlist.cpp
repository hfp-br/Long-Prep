#include "itemlist.h"
#include "item.h"
#include <vector>
#include <cstdlib>


//teste pra ver se ta criando o item direito

Weapon espadacurtaweapon("espada curta",5,3,true,false,5,5,1);
ItemData espadacurtaData = {&espadacurtaweapon};
physicalData espadacurtaPhysical = {4,2,0,false};

ItemTemplate espadacurta = {&espadacurtaData,espadacurtaPhysical};