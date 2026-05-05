#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct{
	int forca;
	int constituicao;
	int destreza;
	int inteligencia;
	int sorte;
} atributes;

class Player final{

	private:
		string name;			//Variavel para armazenar o nome do player
		int life;				//Variavel para armazenar a vida atual do player
		int life_max;			//Variavel para armazenar a vida maxima do player
		int damage;				//Variavel para armazenar o dano base do player
		float weight_capacity;  //Variavel para armazenar a capacidade de peso que o player consegue carregar
		bool backpack;			//Booleana para saber se o player esta com a mochila aberta
		bool alive;				//Booleana para saber se o player esta vivo ou morto
		int defense;
		atributes atributos;

	public:

		// CORRIGIDO: construtor deve ter o mesmo nome da classe (Player, não Craftplayer)
		Player(string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense, atributes atributos){		//função para criar um player
			this->name = name;
			this->life = life;
			this->life_max = life_max;
			this->damage = damage;
			this->weight_capacity = weight_capacity;
			this->backpack = backpack;
			this->alive = alive;
			this->defense = defense;
			this->atributos = atributos;
		};

		string getName() { return name; }						//função para pegar o nome do player
		int getLife() { return life; }							//função para pegar a vida do player
		int getLife_max() { return life_max; }					//função para pegar o vida maxima do player
		int getDamage() { return damage; }						//função para pegar o dano base do player
		float getWeight_Capacity() { return weight_capacity; }	//função para pegar a capacidade de peso do player
		bool isBackpack() { return backpack; }					//função para verificar se a mochila esta aberta
		bool isAlive() { return alive; }						//função para verificar se o player esta vivo
		int getDefense() {return defense;}

		void setName(string n){				//função para definir o nome do player
			name = n;
		}

		void setLife(int l){				//função para definir a vida do player
			// CORRIGIDO: a comparação deve usar o parâmetro 'l', não a variável 'life'
			if(l > life_max){
				cout << "Erro: A vida maxima nao pode ser excedida" <<endl;
				return;
			}
			life = l;
		}

		void setLife_Max(int l){			//função para definir a vida maxima do player
			// CORRIGIDO: deve atribuir à life_max, não à life
			life_max = l;
		}

		void setDamage(int d){				//função para definir o dano base do player
			damage = d;
		}

		void setWeight_Capacity(float w){	// CORRIGIDO: parâmetro deve ser float para bater com o tipo de weight_capacity
			weight_capacity = w;
		}

		void setBackpack(bool b){			//função para definir se a machila esta aberta ou fechada
			backpack = b;
		}

		void setAlive(bool a){				//função para definir se o player esta vivo ou morto
			alive = a;
		}

		void setDefense(int w){
			defense = w;
		}

};