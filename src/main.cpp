#include <iostream>
#include <string>
#include <memory>
#include "dao/StudentDAO.h"
#include "models/Student.h"

/**
 * @file main.cpp
 * @brief Ponto de entrada do sistema de matrícula acadêmica.
 * 
 * Demonstra o uso de CRUD básico para a entidade Estudante.
 */

using namespace std;

// Exibe o menu principal formatado
void menu() {
    cout << "\n--- SISTEMA DE MATRÍCULA ---" << endl;
    cout << "1. Cadastrar Estudante" << endl;
    cout << "2. Listar Todos" << endl;
    cout << "3. Buscar por ID" << endl;
    cout << "4. Atualizar Estudante (Não Implementado)" << endl;
    cout << "5. Excluir Estudante" << endl;
    cout << "0. Sair" << endl;
    cout << "Escolha: ";
}

int main() {
    StudentDAO dao;
    int option, id;

    do {
        menu();
        if (!(cin >> option)) break; // Proteção contra entrada inválida
        cin.ignore();

        switch (option) {
            case 1: { // Cadastrar Estudante
                Student s;
                cout << "Nome: ";
                cin.getline(s.name, 50);
                // Data como inteiro DDMMYYYY para economia de espaço
                cout << "Data Nascimento (DDMMYYYY): ";
                cin >> s.birth_date;
                
                if (dao.create(s)) {
                    cout << "Sucesso! ID do novo estudante: " << s._id << endl;
                }
                break;
            }
            case 2: { // Listar Todos
                dao.listAll();
                break;
            }
            case 3: { // Buscar por ID
                cout << "Digite o ID: ";
                cin >> id;
                // Uso de auto e unique_ptr para gerenciamento seguro de memória
                auto studentPtr = dao.read(id);
                if (studentPtr) {
                    cout << "Encontrado: " << studentPtr->name 
                         << " | Data: " << studentPtr->birth_date << endl;
                } else {
                    cout << "Estudante nao encontrado ou removido." << endl;
                }
                break;
            }
            case 4: {
                cout << "Funcionalidade ainda não implementada." << endl;
                break;
            }
            case 5: { // Excluir Estudante (Lógico)
                cout << "ID para excluir: ";
                cin >> id;
                // Uso de auto para dedução do tipo bool
                auto success = dao.remove(id);
                if (success) {
                    cout << "Estudante excluido logicamente com sucesso." << endl;
                } else {
                    cout << "Erro ao excluir: ID inexistente." << endl;
                }
                break;
            }
        }
    } while (option != 0);

    return 0;
}
