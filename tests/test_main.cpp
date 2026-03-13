#include <iostream>
#include <cassert>
#include <filesystem>
#include <memory>
#include "../src/dao/StudentDAO.h"
#include "../src/models/Student.h"

/**
 * @file test_main.cpp
 * @brief Testes unitários simples para o StudentDAO.
 */

void test_create_and_read() {
    StudentDAO dao;
    Student s;
    std::strcpy(s.name, "Test Student");
    s.birth_date = 10102000;

    bool created = dao.create(s);
    assert(created);
    assert(s._id != -1);

    auto retrieved = dao.read(s._id);
    assert(retrieved != nullptr);
    assert(std::strcmp(retrieved->name, "Test Student") == 0);
    assert(retrieved->birth_date == 10102000);
    
    std::cout << "test_create_and_read passed!" << std::endl;
}

void test_remove() {
    StudentDAO dao;
    Student s;
    std::strcpy(s.name, "Remove Me");
    dao.create(s);

    auto retrieved = dao.read(s._id);
    assert(retrieved != nullptr);

    bool removed = dao.remove(s._id);
    assert(removed);

    auto retrieved_after = dao.read(s._id);
    assert(retrieved_after == nullptr); // Deve retornar nullptr pois foi removido logicamente

    std::cout << "test_remove passed!" << std::endl;
}

int main() {
    // Limpar dados de teste anteriores se existirem
    if (std::filesystem::exists("../data/students.dat")) {
        std::filesystem::remove("../data/students.dat");
    }

    try {
        test_create_and_read();
        test_remove();
        std::cout << "\nAll tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
