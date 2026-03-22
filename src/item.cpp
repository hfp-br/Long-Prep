#include <iostream>
#include <string>
#include <random>
using namespace std;

enum weaponType { sword = 1, polearm = 2, bow = 3 }; // enumeração para escolher o tipo de arma da classe weapon
enum potionType { support = 1, aggressive = 2, mystery = 3 }; // enumeração para escolher o tipo de poção da classe potion
enum amount { small = 1, medium = 2, big = 3 };

int gerarAleatorio(int x, int y) {
    // random_device fornece uma semente não-determinística
    std::random_device rd;
    // mt19937 é um motor de números aleatórios rápido e de boa qualidade
    std::mt19937 gen(rd());
    // Define a distribuição uniforme entre x e y
    std::uniform_int_distribution<> dis(x, y);

    return dis(gen);
}

class Item {

    private:                // Aqui estão as variáveis privadas da classe Item que não devem ser acessadas por qualquer um

        string name;        // Esse é o nome do item
        float weight;       // Esse é o peso do item
        int size;           // Esse é o tamanho do item
        bool equipable;     // Esse é um booleano que indica se o item pode ser equipado ou não
        bool consumable;    // Esse é um booleano que indica se o item pode ser consumido ou não
        string textura;     // Essa string é responsavel por armazenar a localizacão da textura do item

    public:                 // Aqui estão as funções públicas da classe Item que podem ser acessadas por qualquer um

        Item(string name, float weight, int size, bool equipable, bool consumable, string textura ) {
            this->name = name;
            this->weight = weight;
            this->size = size;
            this->equipable = equipable;
            this->consumable = consumable;
            this->textura = textura;
        }

        // Aqui eu deixei as funções relacionadas a pegar alguma informação do item

        string getName()    { return name; }        // função para pegar o nome do item
        float getWeight()   { return weight; }      // função para pegar o peso do item
        int getSize()       { return size; }        // função para pegar o tamanho do item
        bool isEquipable()  { return equipable; }   // função para saber se é equipável o item
        bool isConsumable() { return consumable; }  // função para saber se é consumível o item
        string getTextura() { return textura; }     // função para pegar a textura

        // Aqui eu deixei as funções relacionadas a atribuir algum valor para o item

        void setName(string n) {    // função para atribuir um nome para o item
            if (n.empty()) {
                cout << "Erro: Nome nao pode ser vazio" << endl;
                return;
            }
            if (n.length() > 20) {
                cout << "Erro: Seu nome ultrapassou o limite de 20 letras" << endl;
                return;
            }
            name = n;
        }

        void setWeight(float w) {   // função para atribuir um peso para o item
            if (w < 0) {
                cout << "Erro: Peso nao pode ser negativo" << endl;
                return;
            }
            weight = w;
        }

        void setSize(int s) {       // função para atribuir um tamanho para o item
            if (s < 0) {
                cout << "Erro: Tamanho nao pode ser negativo" << endl;
                return;
            }
            size = s;
        }

        void setEquipable(bool e) { // função para atribuir se o item é equipável ou não
            equipable = e;
        }

        void setConsumable(bool c) { // função para atribuir se o item é consumível ou não
            consumable = c;
        }

        void setTextura(string nomeArquivo, string extensaoArquivo) { // função para atribuir a textura do item
            textura = nomeArquivo + "." + extensaoArquivo; // por enquanto so coloquei para ser o nome do arquivo + a extensão dele
                                                           // porque não sei como a nosssa biblioteca grafica localiza as textura e as utiliza
        }

}; // classe do item

class Weapon : public Item {

    private:
        int damage;
        int range;
        int type;

        Weapon(string name, float weight, int size, bool equipable, bool consumable, string textura, int damage, int range, int type)
            : Item(name, weight, size, equipable, consumable, textura) {
            this->damage = damage;
            this->range = range;
            this->type = type;
        }

        int getDamage() { return damage; }  // função para pegar o dano da arma
        int getRange()  { return range; }   // função para pegar o alcance da arma
        int getType()   { return type; }    // função para pegar o tipo da arma

        void setDamage(int d) { // função para atribuir um dano para a arma
            if (d < 0) {
                cout << "Erro: Dano nao pode ser negativo" << endl;
                return;
            }
            damage = d;
        }

        void setRange(int r) { // função para atribuir um alcance para a arma
            if (r < 0) {
                cout << "Erro: O alcance nao pode ser negativo" << endl;
                return;
            }
            range = r;
        }

        void setType(int t) { // função para atribuir o tipo de arma usando Enum
            if (t != sword && t != polearm && t != bow) {
                cout << "Erro: O tipo de arma nao existe" << endl;
                return;
            }
            type = t;
        }

}; // classe das armas derivada do item

class Potion : public Item {

    private:
        int healing; // variavel para armazenar a quantidade de vida que a poção ira fornecer
        int damage;  // variavel para armazenar a quantidade de dano que a poção ira fornecer
        int type;    // variavel para definir o tipo de poção, usando um Enum

    public:
        Potion(string name, float weight, int size, bool equipable, bool consumable, string textura, int healing, int damage, int type)
            : Item(name, weight, size, equipable, consumable, textura) {
            this->healing = healing;
            this->damage = damage;
            this->type = type;
        }

        int getHealing() { return healing; }    // função para pegar a informação da cura da poção
        int getDamage()  { return damage; }     // função para pegar a informação do dano da poção
        int getType()    { return type; }       // função para pegar o tipo da poção

        void setHealing(int h) {    // função para setar a quantidade de vida que a poção dá
            healing = h;
        }

        void setDamage(int d) {     // função para setar a quantidade de dano que a poção dá
            damage = d;
        }

        void setType(int t) {       // função para setar o tipo de poção
            type = t;

            if (t == mystery) {     // Essa parte caso seja escolhido o tipo misterio os atributos da poção são atribuidos aleatoriamente entre uma das 3 possibilidades
                int n = gerarAleatorio(1, 3);

                switch (n) {
                    case 1:
                        healing = 25;
                        break;
                    case 2:
                        damage = 10;
                        break;
                    case 3:
                        healing = -10;
                        damage = 10;
                        break;
                }
            }
        }

}; // classe das poções