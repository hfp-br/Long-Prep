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


//==================== ATRIBUTOS ====================//

// guarda os atributos principais do jogador
struct atributes{

    // aumenta dano fisico e capacidade de peso
	int forca;

    // influencia vida
	int constituicao;

    // influencia velocidade
	int destreza;

    // influencia efeitos de pocoes
	int inteligencia;

    // influencia chance, drops e efeitos aleatorios
	int sorte;
};


//==================== PLAYER ====================//

// classe principal do jogador
class Player final{
private:

    // nome do jogador
    std::string name;

    // vida atual
    int life;

    // vida maxima
    int life_max;

    // dano base do jogador
    int damage;

    // capacidade maxima de peso
    float weight_capacity;

    // verifica se o jogador possui mochila
    bool backpack;

    // verifica se o jogador esta vivo
    bool alive;

    // defesa base do jogador
    int defense;

    // velocidade de ataque atual
    float attackSpeed = 1.0f;

    // tempo desde o ultimo ataque
    float attackTimer = 0.0f;

    // atributos principais do jogador
    atributes atributos;

    // nivel atual do jogador
    int level=1;

    // xp atual do jogador
    int xp=0;

    // peso atualmente carregado
    float current_weight=0;

    // xp necessario para subir de nivel
    int xpfornextlevel=20;

    // pontos de atributo ainda nao gastos
    int unspentpoints=0;

    // pontos gastos em cada atributo
    int spentpoints[5]={0};

    // velocidade de ataque original antes de buffs/debuffs
    float baseAttackSpeed = 1.0f;

    // classe do jogador
    int classe;

public:

    // construtor do jogador
    Player(std::string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense,atributes atributos);
    

    //==================== GETTERS ====================//

    // retorna o nome do jogador
    std::string getName() const;

    // retorna a vida atual
    int getLife()const;

    // retorna a vida maxima
    int getLife_max()const;

    // retorna o dano base
    int getDamage()const;

    // retorna a capacidade maxima de peso
    float getWeight_Capacity()const;

    // verifica se o jogador possui mochila
    bool isBackpack()const;

    // verifica se o jogador esta vivo
    bool isAlive()const;

    // retorna a defesa base
    int getDefense()const;

    // retorna a velocidade de ataque atual
    float getAttackSpeed()const;

    // retorna o tempo acumulado desde o ultimo ataque
    float getAttackTimer()const;

    // retorna o nivel atual
    int getLevel()const;

    // retorna o xp atual
    int getXp()const;

    // retorna o peso atual carregado
    float getCurrent_weight()const;

    // retorna constituicao
    int getAtributoconstituicao()const;

    // retorna destreza
    int getAtributodestreza()const;

    // retorna forca
    int getAtributoforca()const;

    // retorna inteligencia
    int getAtributointeligencia()const;

    // retorna sorte
    int getAtributosorte()const;

    // retorna o xp necessario para o proximo nivel
    int getxpfornextlevel()const;

    // retorna os pontos ainda nao gastos
    int getunspentpoints()const;

    // retorna a velocidade de ataque base
    float getBaseAttackSpeed()const;

    // retorna a classe do jogador
    int getClasse()const;


    //==================== SETTERS ====================//

    // altera o nome do jogador
    void setName(std::string n);

    // altera a vida atual
    void setLife(int l);

    // altera a vida maxima
    void setLife_Max(int l);

    // altera o dano base
    void setDamage(int d);

    // altera a capacidade maxima de peso
    void setWeight_Capacity(float w);

    // define se o jogador possui mochila
    void setBackpack(bool b);

    // define se o jogador esta vivo
    void setAlive(bool a);

    // altera a defesa base
    void setDefense(int w);

    // altera a velocidade de ataque atual
    void setAttackSpeed(float s);

    // aumenta o timer de ataque
    void tickAttackTimer(float dt);

    // reseta o timer de ataque
    void resetAttackTimer();

    // altera o nivel
    void setlevel(int x);

    // altera o xp atual
    void setXp(int x);

    // altera o peso atual carregado
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

    // altera o xp necessario para subir de nivel
    void setxpfornextlevel(int x);

    // altera os pontos ainda nao gastos
    void setunspentpoints(int x);

    // altera a velocidade de ataque base
    void setBaseAttackSpeed(float s);

    // altera a classe do jogador
    void setClasse(int x);
};

#endif