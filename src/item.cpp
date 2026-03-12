#include <iostream>
#include <string>
using namespace std;

Class Item{

	private:				// Aqui estão as variáveis privadas da classe Item que não devem ser acessadas por qualquer um

		string name;		// Esse é o nome do item
		float weight;		// Esse é o peso do item
		int size;			// Esse é o tamanho do item
		bool equipable;		// Esse é um booleano que indica se o item pode ser equipado ou não
		bool consumable		// Esse é um booleano que indica se o item pode ser consumido ou não

	public:						// Aqui estão as funções públicas da classe Item que podem ser acessadas por qualquer um

		item(string name, float weight, int size, bool equipable, bool consumable) {	// essa função serve para criar um item 
			this->name = name;
			this->weight = weight;
			this->size = size;
			this->equipable = equipable;
			this->consumable = consumable;
		}

		// Aqui eu deixei as funções relaciondas a pegar alguma informação do item

		string getName( ) { return name; }			// função para pegar o nome do item
		float getWeight( ) { return weight; }		// função para pegar o peso do item
		int getSize( ) { return size; }				// função para pegar o tamanho do item
		bool isEquipable( ) { return equipable; }	// função para saber se é quipavel o item
		bool isConsumable( ) { return Consumable; }	// função para saber se é consumivel o item

		// Aqui eu deixei as funções relacionadas a atribuir algum valor para o item

		void setName(string n) {	// função para atribuir um nome para o item
			if (n.empty( )) {
				cout << "Erro: Nome nao pode ser vazio" << endl;
				return;
			}
			if (n.length( ) > 20) {
				cout << "Erro: Seu nome ultrapassou o limite de 20 letras" << endl;
				return;
			}

			name = n;

		}

		void setWeight(float w) {	// função para atribuir um peso para o item
			if (w < 0) {
				cout << "Erro: Peso nao pode ser negativo" << endl;
				return;
			}
			weight = w;
		}

		void setSize(int s) {		// função para atribuir um tamanho para o item
			if (s < 0) {
				cout << "Erro: Tamanho nao pode ser negativo" << endl;
				return;
			}
			size = s;
		}

		void setEquipable(bool e) {	// função para atribuir se o item é equipavel ou não
			equipable = e;
		}

		void setConsumable(bool c) {// função para atribuir se o item é consumivel ou não
			consumable = c;
		}

}