#include <iostream>
#include <fstream>
#include <memory>
#include <cstdint>
#include "StudentDAO.h"
#include "../models/Student.h"
#include "../utils/FileManager.h"

/**
 * @file StudentDAO.cpp
 * @brief Implementação do Data Access Object para Estudantes.
 * 
 * Este arquivo lida com a persistência de dados em arquivos binários.
 * O formato do arquivo consiste em um cabeçalho de 4 bytes (int32) para o último ID,
 * seguido por registros sequenciais de tamanho fixo (Student).
 */

StudentDAO::StudentDAO() {
    // Inicializa o arquivo se ele não existir
    FileManager::initFile(path);
}

bool StudentDAO::create(Student &s) {
    // Busca o último ID do cabeçalho
    auto lastId = FileManager::getLastId(path);
    s._id = lastId + 1;
    s.removed = false;

    // Abre em modo append para adicionar ao fim do arquivo
    std::ofstream file(path, std::ios::binary | std::ios::app);
    if (!file.is_open()) return false;

    // Escrita direta do bloco de memória (POD - Plain Old Data)
    file.write(reinterpret_cast<char*>(&s), sizeof(Student));
    file.close();

    // Atualiza o contador de IDs no cabeçalho
    FileManager::updateLastId(path, s._id);
    return true;
}

std::unique_ptr<Student> StudentDAO::read(int id) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return nullptr;

    // Pula o cabeçalho de metadados
    file.seekg(sizeof(std::int32_t));

    Student s;
    // Varredura linear (busca sequencial)
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s._id == id && !s.removed) {
            file.close();
            // Retorna um unique_ptr para garantir que a memória seja liberada automaticamente
            return std::make_unique<Student>(s);
        }
    }
    file.close();
    return nullptr; // Não encontrado
}

bool StudentDAO::remove(int id) {
    // Abre com flags in|out para permitir sobrescrita no meio do arquivo
    std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) return false;

    file.seekg(sizeof(std::int32_t));

    Student s;
    std::streampos pos;

    while (pos = file.tellg(), file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s._id == id && !s.removed) {
            // Exclusão lógica: apenas marca a flag e sobrescreve o registro
            s.removed = true;
            file.seekp(pos);
            file.write(reinterpret_cast<char*>(&s), sizeof(Student));
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void StudentDAO::listAll() {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return;

    file.seekg(sizeof(std::int32_t));

    Student s;
    std::cout << "\n--- LISTA DE ESTUDANTES ATIVOS ---\n";
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (!s.removed) {
            std::cout << "ID: " << s._id << " | Nome: " << s.name 
                      << " | Nascimento: " << s.birth_date << std::endl;
        }
    }
    file.close();
}
