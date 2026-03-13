#ifndef STUDENTDAO_H
#define STUDENTDAO_H

#include "../models/Student.h"
#include "../utils/FileManager.h"
#include <string>
#include <memory> // For std::unique_ptr

class StudentDAO {
private:
    std::string path = "../data/students.dat"; // Relative to executable in builds/

public:
    StudentDAO();
    bool create(Student &s);
    std::unique_ptr<Student> read(int id); // Returns unique_ptr for clear ownership
    bool remove(int id);
    void listAll();
};

#endif // STUDENTDAO_H