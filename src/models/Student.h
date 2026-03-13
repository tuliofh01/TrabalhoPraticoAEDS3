#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>
#include <cstdint> // Tipos de largura fixa para consistência e economia de memória

/**
 * @struct Student
 * @brief Representa a entidade Estudante no sistema.
 * 
 * Otimizado para armazenamento binário com tipos de largura fixa.
 */
struct Student {
    bool removed;          // Flag de exclusão lógica (4 bytes na maioria dos sistemas, mas mantido bool)
    std::int32_t _id;      // ID único do registro (4 bytes)
    std::int32_t user_id;  // Referência ao usuário base (4 bytes)
    char name[50];         // Nome de tamanho fixo para facilitar I/O binário (50 bytes)
    std::uint32_t birth_date; // Data no formato DDMMYYYY (4 bytes)

    Student() {
        removed = false;
        _id = -1;
        user_id = -1;
        birth_date = 0;
        std::memset(name, 0, sizeof(name));    
    }
};

#endif
