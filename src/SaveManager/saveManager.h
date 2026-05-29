/**
 * @file saveManager.h
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo declara os metodos e atributos do sistema de save e load do Long Prep.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <sqlite3.h>
#include "player.h"
#include "itemlist.h"
#include <vector>


//==================== DADOS SALVOS DOS ITENS ====================//

// struct usada para guardar os dados carregados de um item salvo
struct ItemSaveData {

    // id unico do item dentro do save
    int saveId;

    // id do tipo/template do item
    int itemId;

    // posicao x salva do item
    float posX;

    // posicao y salva do item
    float posY;

    // rotacao salva do item
    float rotation;

    // indica se o item estava equipado
    bool isEquipped;

    // indica se o item deveria ser apagado ao carregar
    bool deveriaApagar;

    // indice do slot onde o item estava equipado
    int slotIndex;
};


//==================== SAVE MANAGER ====================//

// classe singleton responsavel por salvar e carregar o jogo
class SaveManager {
private:
    // ponteiro para o banco de dados sqlite
    sqlite3* db;

    // construtor privado para impedir criacao externa
    SaveManager();

    // cria a tabela do player no banco
    void criarTabelaPlayer();

    // cria a tabela da fase atual no banco
    void criarTabelaFase();

    // cria a tabela dos itens no banco
    void criarTabelaItens();

public:
    // fecha o banco de dados ao destruir o save manager
    ~SaveManager();

    // impede copia do singleton
    SaveManager(const SaveManager&) = delete;

    // impede atribuicao/copia do singleton
    SaveManager& operator=(const SaveManager&) = delete;

    // retorna a unica instancia do save manager
    static SaveManager& getInstance();

    // salva os dados principais do player e bonus temporarios
    void salvarPlayer(const Player& player, int bonusMult, int bonusSorte, int bonusSpeed, int bonusDano, int unspentPoints);

    // salva a fase atual
    void salvarFase(int fase);

    // salva um item fisico no banco de dados
    void salvarItens(int saveId, int itemId, const physicalObject& item, bool deveriaApagar);

    // carrega a fase atual salva
    int carregarFase();

    // carrega os dados do player e dos bonus temporarios
    void carregarPlayer(Player& player, int& bonusmult, int& bonussorte, int& bonusSpeed, int& bonusdano);

    // carrega todos os itens salvos
    std::vector<ItemSaveData> carregarItens();

    // limpa os itens salvos no banco
    void limparItens();
};


#endif