/**
 * @file saveManager.cpp
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo preenche as funcoes de salvar e carregar do long prep, utilizando SQLite para criar tabelas e utiliza-las como arquivos de save.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "saveManager.h"
#include "player.h"
#include "itemlist.h"
#include "box2d/id.h"
#include <box2d/box2d.h>
#include <iostream>
#include <stdexcept>

//==================== SINGLETON ====================//

// retorna a unica instancia do save manager
SaveManager& SaveManager::getInstance() {

    // instancia estatica criada apenas uma vez
    static SaveManager instance;

    return instance;
}

//==================== LIMPEZA DOS ITENS ====================//

// remove todos os itens antigos do banco antes de salvar novamente
void SaveManager::limparItens() {

    // comando sql para apagar todos os itens
    const char* sql = "DELETE FROM itens;";

    // executa o comando
    int save = sqlite3_exec(db, sql, nullptr, nullptr, nullptr);

    // verifica se ocorreu erro
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao limpar itens antigos");
    }
}

//==================== CONSTRUTOR ====================//

// inicializa o banco de dados e cria as tabelas
SaveManager::SaveManager() {

    // abre/cria o banco de dados
    int save = sqlite3_open("save.db", &db);

    // verifica se houve erro ao abrir
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao abrir banco");
    } else {
        std::cout << "Banco criado com sucesso" << std::endl;
    }

    // cria as tabelas necessarias
    criarTabelaPlayer();
    criarTabelaFase();
    criarTabelaItens();
}

//==================== DESTRUTOR ====================//

// fecha o banco ao destruir o save manager
SaveManager::~SaveManager() {
    sqlite3_close(db);
}

//==================== TABELA PLAYER ====================//

// cria a tabela do player caso ela nao exista
void SaveManager::criarTabelaPlayer() {

    // sql de criacao da tabela do jogador
    const char* criarTabelaPlayer = R"(
        CREATE TABLE IF NOT EXISTS player (
            id INTEGER PRIMARY KEY,
            life INTEGER NOT NULL,
            level INTEGER NOT NULL,
            xp INTEGER NOT NULL,
            atributoForca INTEGER NOT NULL,
            atributoDestreza INTEGER NOT NULL,
            atributoConstituicao INTEGER NOT NULL,
            atributoInteligencia INTEGER NOT NULL,
            bonusMult INTEGER NOT NULL,
            bonusSorte INTEGER NOT NULL,
            bonusSpeed INTEGER NOT NULL,
            bonusDano INTEGER NOT NULL,
            atributoSorte INTEGER NOT NULL,
            unspentpoints INTEGER
        );
    )";

    // executa o comando sql
    int save = sqlite3_exec(db, criarTabelaPlayer, nullptr, nullptr, nullptr);

    // verifica se ocorreu erro
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao criar tabela player");
    } else {
        std::cout << "tabela Player criada com sucesso" << std::endl;
    }    
}

//==================== SALVAMENTO DO PLAYER ====================//

// salva os dados do jogador no banco
void SaveManager::salvarPlayer(const Player& player, int bonusMult, int bonusSorte, int bonusSpeed, int bonusDano, int unspentPoints){

    // ponteiro para o statement sql
    sqlite3_stmt* stmt;

    // comando sql para inserir/substituir os dados do jogador
    const char* salvarPlayer = R"(
        INSERT OR REPLACE INTO player (id, life, level, xp, atributoForca, atributoDestreza, atributoConstituicao, atributoInteligencia, bonusMult, bonusSorte, bonusSpeed, bonusDano, atributoSorte, unspentPoints)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    )";

    // prepara o statement sql
    int save = sqlite3_prepare_v2(db, salvarPlayer, -1, &stmt, nullptr);

    // verifica se ocorreu erro ao preparar
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao preparar salvamento do player");
    }

    // associa os valores aos parametros do sql
    sqlite3_bind_int(stmt, 1, 1);
    sqlite3_bind_int(stmt, 2, player.getLife());
    sqlite3_bind_int(stmt, 3, player.getLevel());
    sqlite3_bind_int(stmt, 4, player.getXp());
    sqlite3_bind_int(stmt, 5, player.getAtributoforca());
    sqlite3_bind_int(stmt, 6, player.getAtributodestreza());
    sqlite3_bind_int(stmt, 7, player.getAtributoconstituicao());
    sqlite3_bind_int(stmt, 8, player.getAtributointeligencia());
    sqlite3_bind_int(stmt, 9, bonusMult);
    sqlite3_bind_int(stmt, 10, bonusSorte);
    sqlite3_bind_int(stmt, 11, bonusSpeed);
    sqlite3_bind_int(stmt, 12, bonusDano);
    sqlite3_bind_int(stmt, 13, player.getAtributosorte());
    sqlite3_bind_int(stmt, 14, unspentPoints);

    // executa o salvamento
    save = sqlite3_step(stmt);

    // verifica se houve erro
    if (save != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("erro ao salvar player");
    }

    // libera memoria do statement
    sqlite3_finalize(stmt);
}

//==================== TABELA FASE ====================//

// cria a tabela que guarda a fase atual
void SaveManager::criarTabelaFase(){

    const char* criarTabelaFase = R"(
        CREATE TABLE IF NOT EXISTS fase (
            id INTEGER PRIMARY KEY,
            faseatual INTEGER NOT NULL
        );
    )";

    // executa o sql
    int save = sqlite3_exec(db, criarTabelaFase, nullptr, nullptr, nullptr);

    // verifica se houve erro
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao criar tabela fase");
    }
}

// salva a fase atual no banco de dados
void SaveManager::salvarFase(int fase){
    sqlite3_stmt* stmt;

    // comando sql para inserir ou substituir a fase salva
    const char* salvarFase = R"(
    INSERT OR REPLACE INTO fase (id, faseatual)
    VALUES (?, ?);
    )";

    // prepara o comando sql
    int save = sqlite3_prepare_v2(db, salvarFase, -1, &stmt, nullptr);

    // verifica se o comando foi preparado corretamente
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao preparar salvamento da fase");
    }

    // id fixo 1, pois so existe uma fase atual salva
    sqlite3_bind_int(stmt, 1, 1);

    // salva o numero da fase atual
    sqlite3_bind_int(stmt, 2, fase);

    // executa o comando sql
    save = sqlite3_step(stmt);

    // verifica se a fase foi salva corretamente
    if (save != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("erro ao salvar fase");
    }

    // libera o statement da memoria
    sqlite3_finalize(stmt);
}


// cria a tabela responsavel por armazenar os itens salvos
void SaveManager::criarTabelaItens(){

    // comando sql para criar a tabela de itens caso ela ainda nao exista
    const char* criarTabelaItens = R"(CREATE TABLE IF NOT EXISTS itens (
            saveId INTEGER PRIMARY KEY,
            itemId INTEGER NOT NULL,
            posX DOUBLE NOT NULL,
            posY DOUBLE NOT NULL,
            rotation REAL NOT NULL,
            isEquipped INTEGER NOT NULL,
            deveriaApagar INTEGER NOT NULL
        );
    )";

    // executa o comando de criacao da tabela
    int save = sqlite3_exec(db, criarTabelaItens, nullptr, nullptr, nullptr);

    // verifica se a tabela foi criada corretamente
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao criar tabela Itens");
    } else {
        std::cout << "tabela Itens criada com sucesso" << std::endl;
    } 
}


// salva os dados de um item fisico no banco de dados
void SaveManager::salvarItens(int saveId, int itemId, const physicalObject& item, bool deveriaApagar){
    sqlite3_stmt* stmt;

    // comando sql para inserir ou substituir um item salvo
    const char* salvarItens = R"(
        INSERT OR REPLACE INTO itens (
            saveId, itemId, posX, posY, rotation, isEquipped, deveriaApagar
        )
        VALUES (?, ?, ?, ?, ?, ?, ?);
    )";

    // prepara o comando sql
    int save = sqlite3_prepare_v2(db, salvarItens, -1, &stmt, nullptr);

    // verifica se o comando foi preparado corretamente
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao preparar salvamento dos itens");
    }

    // salva o id unico do item no save
    sqlite3_bind_int(stmt, 1, saveId);

    // salva o id do tipo/template do item
    sqlite3_bind_int(stmt, 2, itemId);

    // salva a posicao x do corpo fisico do item
    sqlite3_bind_double(stmt, 3, b2Body_GetPosition(item.bodyId).x);

    // salva a posicao y do corpo fisico do item
    sqlite3_bind_double(stmt, 4, b2Body_GetPosition(item.bodyId).y);

    // salva a rotacao atual do item
    sqlite3_bind_double(stmt, 5, b2Rot_GetAngle(b2Body_GetRotation(item.bodyId)));

    // salva se o item esta equipado
    sqlite3_bind_int(stmt, 6, item.isEquipped ? 1 : 0);

    // salva se o item deveria ser apagado ao carregar
    sqlite3_bind_int(stmt, 7, deveriaApagar ? 1 : 0);

    // executa o comando sql
    save = sqlite3_step(stmt);

    // verifica se o item foi salvo corretamente
    if (save != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("erro ao salvar itens");
    }

    // libera o statement da memoria
    sqlite3_finalize(stmt);
}

// carrega a fase atual salva no banco de dados
int SaveManager::carregarFase() {
    sqlite3_stmt* stmt;

    // comando sql para buscar a fase salva
    const char* carregarFase = R"(
        SELECT faseatual
        FROM fase
        WHERE id = ?;
    )";

    // prepara o comando sql
    int save = sqlite3_prepare_v2(db, carregarFase, -1, &stmt, nullptr);

    // verifica se o comando foi preparado corretamente
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao preparar carregamento da fase");
    }

    // busca sempre o save principal, usando id 1
    sqlite3_bind_int(stmt, 1, 1);

    // executa a busca
    save = sqlite3_step(stmt);

    // verifica se encontrou uma fase salva
    if (save != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("nenhum save de fase encontrado");
    }

    // pega o valor da fase atual retornado pelo banco
    int fase = sqlite3_column_int(stmt, 0);

    // libera o statement da memoria
    sqlite3_finalize(stmt);

    // retorna a fase carregada
    return fase;
}


// carrega os dados salvos do jogador e dos bonus temporarios
void SaveManager::carregarPlayer(Player& player, int& bonusmult, int& bonussorte, int& bonusSpeed, int& bonusdano){
    sqlite3_stmt* stmt;

    // comando sql para buscar os dados salvos do jogador
    const char* carregarPlayer = R"(
        SELECT life, level, xp, atributoForca, atributoDestreza, atributoConstituicao, atributoInteligencia, bonusMult, bonusSorte, bonusSpeed, bonusDano, atributoSorte, unspentPoints
        FROM player
        WHERE id = ?;
    )";

    // prepara o comando sql
    int save = sqlite3_prepare_v2(db, carregarPlayer, -1, &stmt, nullptr);

    // verifica se o comando foi preparado corretamente
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao preparar carregamento do player");
    }

    // busca sempre o player principal, usando id 1
    sqlite3_bind_int(stmt, 1, 1);

    // executa a busca
    save = sqlite3_step(stmt);

    // verifica se encontrou dados salvos do player
    if (save != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("nenhum save do player encontrado");
    }


    // carrega a vida atual do player
    int life = sqlite3_column_int(stmt, 0);
    player.setLife(life);

    // carrega o level do player
    int level = sqlite3_column_int(stmt, 1);
    player.setlevel(level);

    // carrega o xp atual do player
    int xp = sqlite3_column_int(stmt, 2);
    player.setXp(xp);

    // carrega o atributo forca
    int forca = sqlite3_column_int(stmt, 3);
    player.setAtributoforca(forca);

    // carrega o atributo destreza
    int destreza = sqlite3_column_int(stmt, 4);
    player.setAtributodestreza(destreza);

    // carrega o atributo constituicao
    int constituicao = sqlite3_column_int(stmt, 5);
    player.setAtributoconstituicao(constituicao);

    // carrega o atributo inteligencia
    int inteligencia = sqlite3_column_int(stmt, 6);
    player.setAtributointeligencia(inteligencia);

    // carrega os bonus temporarios das pocoes
    bonusmult = sqlite3_column_int(stmt, 7);
    bonussorte = sqlite3_column_int(stmt, 8);
    bonusSpeed = sqlite3_column_int(stmt, 9);
    bonusdano = sqlite3_column_int(stmt, 10);

    // carrega o atributo sorte
    int sorte = sqlite3_column_int(stmt, 11);
    player.setAtributosorte(sorte);

    // carrega os pontos de atributo ainda nao gastos
    int unspentPoints = sqlite3_column_int(stmt,12);
    player.setunspentpoints(unspentPoints);

    // libera o statement da memoria
    sqlite3_finalize(stmt);
}


// carrega todos os itens salvos no banco de dados
std::vector<ItemSaveData> SaveManager::carregarItens(){
    sqlite3_stmt* stmt;

    // comando sql para buscar todos os itens salvos
    const char* carregarItem = R"(
        SELECT saveId, itemId, posX, posY, rotation, isEquipped, deveriaApagar
        FROM itens;
    )";

    // prepara o comando sql
    int save = sqlite3_prepare_v2(db, carregarItem, -1, &stmt, nullptr);

    // verifica se o comando foi preparado corretamente
    if (save != SQLITE_OK) {
        throw std::runtime_error("erro ao preparar carregamento do Item");
    }

    // vetor que armazenara os dados dos itens carregados
    std::vector<ItemSaveData> DataItens;

    // percorre todas as linhas retornadas pela tabela
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        ItemSaveData novoItem;

        // carrega o id unico do item no save
        novoItem.saveId = sqlite3_column_int(stmt, 0);

        // carrega o id do tipo/template do item
        novoItem.itemId = sqlite3_column_int(stmt,1);

        // carrega a posicao x salva
        novoItem.posX = sqlite3_column_double(stmt, 2);

        // carrega a posicao y salva
        novoItem.posY = sqlite3_column_double(stmt, 3);

        // carrega a rotacao salva
        novoItem.rotation = sqlite3_column_double(stmt, 4);

        // carrega se o item estava equipado
        novoItem.isEquipped = sqlite3_column_int(stmt, 5);

        // carrega se o item deveria ser apagado ao carregar
        novoItem.deveriaApagar = sqlite3_column_int(stmt, 6);

        // adiciona o item carregado no vetor
        DataItens.push_back(novoItem);
    }

    // libera o statement da memoria
    sqlite3_finalize(stmt);

    // retorna todos os itens carregados
    return DataItens;
}