/**
 * @file player.h
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo declara os metodos e atributos do player.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include "../Entity.h"

//==================== ATRIBUTOS ====================//

// guarda os atributos principais do jogador
struct atributes{

    // aumenta dano fisico e capacidade de peso
	int forca;

    // influencia vida
	int constituicao;

    // influencia velocidade de ataque
	int destreza;

    // influencia habilidades e pocoes
	int inteligencia;

    // influencia drops e eventos aleatorios
	int sorte;
};


//==================== PLAYER ====================//

// classe base para todos os tipos de jogador
class Player : public Entity{
private:

    // capacidade maxima de peso
    float weight_capacity;

    // verifica se possui mochila
    bool backpack;

    // verifica se esta vivo
    bool alive;

    // atributos principais
    atributes atributos;

    // nivel atual
    int level = 1;

    // experiencia atual
    int xp = 0;

    // peso atualmente carregado
    float current_weight = 0;

    // xp necessario para subir de nivel
    int xpfornextlevel = 20;

    // pontos de atributo disponiveis
    int unspentpoints = 0;

    // controle de pontos gastos por atributo
    int spentpoints[5] = {0};

    // velocidade de ataque original
    float baseAttackSpeed = 1.0f;

    // contador usado para habilidades especiais
    int contadorSkill = 0;

public:
    Player(std::string name, int life, int life_max, int damage,
           float weight_capacity, bool backpack, bool alive,
           int defense, atributes atributos);

        //==================== GETTERS ====================//

    // retorna a capacidade maxima de peso
    float getWeight_Capacity() const;

    // verifica se possui mochila
    bool isBackpack() const;

    // verifica se esta vivo
    bool isAlive() const;

    // retorna o nivel atual
    int getLevel() const;

    // retorna o xp atual
    int getXp() const;

    // retorna o peso carregado
    float getCurrent_weight() const;

    // retorna constituicao
    int getAtributoconstituicao() const;

    // retorna destreza
    int getAtributodestreza() const;

    // retorna forca
    int getAtributoforca() const;

    // retorna inteligencia
    int getAtributointeligencia() const;

    // retorna sorte
    int getAtributosorte() const;

    // retorna xp necessario para subir de nivel
    int getxpfornextlevel() const;

    // retorna pontos disponiveis
    int getunspentpoints() const;

    // retorna velocidade base de ataque
    float getBaseAttackSpeed() const;

    // retorna contador da habilidade
    int getContadorSkill() const;

        //==================== SETTERS ====================//

    // altera capacidade maxima de peso
    void setWeight_Capacity(float w);

    // altera estado da mochila
    void setBackpack(bool b);

    // altera estado de vida
    void setAlive(bool a);

    // altera nivel
    void setlevel(int x);

    // altera xp
    void setXp(int x);

    // altera peso atual
    void setcurrent_weight(float x);

    // altera constituicao
    void setAtributoconstituicao(int x);

    // altera destreza
    void setAtributodestreza(int x);

    // altera forca
    void setAtributoforca(int x);

    // altera inteligencia
    void setAtributointeligencia(int x);

    // altera sorte
    void setAtributosorte(int x);

    // altera xp necessario para subir de nivel
    void setxpfornextlevel(int x);

    // altera pontos disponiveis
    void setunspentpoints(int x);

    // altera velocidade base de ataque
    void setBaseAttackSpeed(float s);

    // altera contador da habilidade
    void setContadorSkill(int c);

    // habilidade especial de cada classe
    virtual void usarHabilidade() = 0;
    virtual void desfazerHabilidade() = 0;
};

class Guerreiro final: public Player{
    public:
        Guerreiro(std::string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense, atributes atributos) 
        : Player(name, life, life_max, damage, weight_capacity, backpack, alive, defense, atributos){};

        void usarHabilidade() override;
        void desfazerHabilidade() override;
};

class Mago final: public Player{
    public:
        Mago(std::string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense, atributes atributos) 
        : Player(name, life, life_max, damage, weight_capacity, backpack, alive, defense, atributos){};

        void usarHabilidade() override;
        void desfazerHabilidade() override;
};

class Curandeiro final: public Player{
    public:
        Curandeiro(std::string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense, atributes atributos) 
        : Player(name, life, life_max, damage, weight_capacity, backpack, alive, defense, atributos){};

        void usarHabilidade() override;
        void desfazerHabilidade() override;
};

class Ladrao final: public Player{
    public:
        Ladrao(std::string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense, atributes atributos) 
        : Player(name, life, life_max, damage, weight_capacity, backpack, alive, defense, atributos){};

        void usarHabilidade() override;
        void desfazerHabilidade() override;
};

class PlayerFactory {
    public:
        static std::unique_ptr<Player> criarPlayer(int classeEscolhida);
};

#endif