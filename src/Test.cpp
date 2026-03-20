#include <iostream>
#include <string>
#include "item.h"
#include "player.h"
using namespace std;

int action(Weapon w, Potion p){
	int numero = 0;

	// CORRIGIDO: condição do while estava errada (|| deve ser &&)
	// Com ||, a condição NUNCA seria falsa, causando loop infinito
	while(numero != 1 && numero != 2){
		cout << "Escolha uma das seguintes acoes" << endl;
		cout << "1. Usar a " << w.getName() << endl;
		cout << "2. Usar a " << p.getName() << endl;
		cin >> numero;
	}

	return numero;
}

int main() {

	int numero;
	int aleatorio;
	int dano;
	int vida;

	Player heroi("Felipe", 100, 100, 5, 60.0, false, true, false, false);
	Player vilao("Jhonatas", 100, 100, 5, 60.0, false, true, false, false);
	Weapon espadaHeroi("Fast Travel Rapier", 23.0, 2, true, false, 75, 1, sword);
	Weapon espadaVilao("Dark Nexus", 23.0, 2, true, false, 75, 1, sword);
	Potion pocao("Suprema", 5, 2, false, true, 50, 0, support);
	
	cout << "O  heroi "  << heroi.getName()     << " apareceu " << endl;
	cout << "A  espada " << espadaHeroi.getName()<< " apareceu " << endl;
	cout << "A  pocao "  << pocao.getName()      << " apareceu " << endl;

	cout << "Atencao o grande vilao " << vilao.getName() << " apareceu " << endl;

	cout << "Atencao o heroi " << heroi.getName() << " e o grande vilao " << vilao.getName() << " Entraram em uma batalha " << endl;

	// CORRIGIDO: isAlive() é uma função, precisa de () para chamá-la
	while(heroi.isAlive() == true && vilao.isAlive() == true){
		numero = action(espadaHeroi, pocao);
		switch(numero){
			case 1:
				cout << "O heroi " << heroi.getName() << " pegou a espada " << espadaHeroi.getName() << " e cortou o vilao " << vilao.getName() << endl;
				aleatorio = gerarAleatorio(0, 75);
				// CORRIGIDO: getDamage() e getLife() são funções, precisam de ()
				dano = heroi.getDamage() + espadaHeroi.getDamage() - aleatorio;
				vilao.setLife(vilao.getLife() - dano);
				// CORRIGIDO: verificar se o vilão morreu após receber dano
				if(vilao.getLife() <= 0){
					vilao.setLife(0);
					vilao.setAlive(false);
				}
				cout << "O heroi causou " << dano << " de dano" << endl;
				break;
			case 2:
				cout << "O heroi " << heroi.getName() << " pegou a pocao " << pocao.getName() << " e bebeu" << endl;
				aleatorio = gerarAleatorio(0, 20);
				// CORRIGIDO: getHealing() e getLife() são funções, precisam de ()
				vida = pocao.getHealing() - aleatorio;
				vida = vida + heroi.getLife();
				// CORRIGIDO: getLife_max() é função, precisa de ()
				if(vida > heroi.getLife_max()){
					vida = heroi.getLife_max();
				}
				heroi.setLife(vida);
				cout << "O heroi recuperou " << vida << " de vida" << endl;
				break;
		}

		// CORRIGIDO: getLife(), getLife_max() são funções, precisam de ()
		if(vilao.isAlive() && vilao.getLife() < (vilao.getLife_max() / 2))
		{
			cout << "O vilao " << vilao.getName() << " pegou a pocao " << pocao.getName() << " e bebeu" << endl;
			aleatorio = gerarAleatorio(0, 20);
			vida = pocao.getHealing() - aleatorio;
			vida = vida + vilao.getLife();
			if(vida > vilao.getLife_max()){
				vida = vilao.getLife_max();
			}
			vilao.setLife(vida);
			cout << "O vilao recuperou " << vida << " de vida" << endl;
		}
		else if(vilao.isAlive())
		{
			cout << "O vilao " << vilao.getName() << " pegou a espada " << espadaVilao.getName() << " e cortou o heroi " << heroi.getName() << endl;
			aleatorio = gerarAleatorio(0, 75);
			// CORRIGIDO: getDamage() e getLife() são funções, precisam de ()
			dano = vilao.getDamage() + espadaVilao.getDamage() - aleatorio;
			heroi.setLife(heroi.getLife() - dano);
			// CORRIGIDO: verificar se o herói morreu após receber dano
			if(heroi.getLife() <= 0){
				heroi.setLife(0);
				heroi.setAlive(false);
			}
			cout << "O vilao causou " << dano << " de dano" << endl;
		}
	}

	// CORRIGIDO: mostrar quem venceu a batalha
	if(heroi.isAlive()){
		cout << "O heroi " << heroi.getName() << " venceu a batalha!" << endl;
	} else {
		cout << "O vilao " << vilao.getName() << " venceu a batalha!" << endl;
	}
}