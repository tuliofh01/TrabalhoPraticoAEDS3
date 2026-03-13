# Modern C++ Programming Guide
## Writing Clean, Safe, and Efficient Code

This guide provides tips for writing modern C++ (C++11 and later) code that avoids C-like patterns while maintaining readability and performance.

### 1. Prefer RAII Over Manual Resource Management

**Instead of:**
```cpp
FILE* file = fopen("data.txt", "r");
// ... use file ...
fclose(file); // Easy to forget!
```

**Use RAII (Resource Acquisition Is Initialization):**
```cpp
#include <fstream>
std::ifstream file("data.txt");
// File automatically closed when file goes out of scope
```

### 2. Use Smart Pointers Instead of Raw Pointers

**Instead of:**
```cpp
Student* s = new Student();
// ... use s ...
delete s; // Must remember to delete!
```

**Use smart pointers:**
```cpp
#include <memory>
auto s = std::make_unique<Student>(); // or std::make_shared<Student>
// Automatically deleted when out of scope
```

### 3. Prefer Containers Over C-Arrays

**Instead of:**
```cpp
int numbers[100];
// Manual size tracking, no bounds checking
```

**Use standard containers:**
```cpp
#include <vector>
#include <array>
std::vector<int> numbers; // Dynamic size
std::array<int, 100> fixedNumbers; // Fixed size with bounds checking
```

### 4. Use Range-Based For Loops

**Instead of:**
```cpp
for (size_t i = 0; i < vec.size(); ++i) {
    // Process vec[i]
}
```

**Use range-based for:**
```cpp
for (const auto& element : vec) {
    // Process element
}
// Or if you need to modify:
for (auto& element : vec) {
    // Modify element
}
```

### 5. Prefer auto for Type Deduction

**Instead of:**
```cpp
std::vector<std::string>::iterator it = vec.begin();
```

**Use auto:**
```cpp
auto it = vec.begin(); // Compiler deduces the type
// Also works with lambdas:
auto process = [](const Student& s) { return s.getId(); };
```

### 6. Use nullptr Instead of NULL or 0

**Instead of:**
```cpp
Student* s = NULL; // or 0
```

**Use nullptr:**
```cpp
Student* s = nullptr; // Type-safe null pointer
```

### 7. Prefer Enum Classes Over Plain Enums

**Instead of:**
```cpp
enum Color { RED, GREEN, BLUE };
// Can implicitly convert to int, pollutes namespace
```

**Use enum class:**
```cpp
enum class Color { RED, GREEN, BLUE };
// Strongly typed, scoped, no implicit conversions
```

### 8. Use constexpr for Compile-Time Computation

**Instead of:**
```cpp
const int size = 10 * 20; // Runtime constant
```

**Use constexpr:**
```cpp
constexpr int size = 10 * 20; // Compile-time constant
// Can be used in array sizes, template parameters, etc.
```

### 9. Prefer Lambda Functions Over Function Pointers or Functors

**Instead of:**
```cpp
bool compareById(const Student& a, const Student& b) {
    return a.getId() < b.getId();
}
// ...
std::sort(students.begin(), students.end(), compareById);
```

**Use lambda:**
```cpp
std::sort(students.begin(), students.end(),
          [](const Student& a, const Student& b) {
              return a.getId() < b.getId();
          });
```

### 10. Use std::optional for Values That May Be Absent

**Instead of:**
```cpp
Student findStudent(int id) {
    // ... if not found, return default-constructed Student?
    // Or throw exception? Or use output parameter?
}
```

**Use std::optional:**
```cpp
#include <optional>
std::optional<Student> findStudent(int id) {
    // ... if found, return student;
    // ... if not found, return std::nullopt;
}

// Usage:
if (auto student = findStudent(id)) {
    // Use *student
}
```

### 11. Prefer Structured Binding for Multiple Return Values

**Instead of:**
```cpp
std::pair<int, std::string> result = getStudentInfo(id);
int id = result.first;
std::string name = result.second;
```

**Use structured binding:**
```cpp
auto [id, name] = getStudentInfo(id); // C++17
```

### 12. Use std::variant for Type-Safe Unions

**Instead of:**
```cpp
union Data {
    int i;
    double d;
    // No way to know which is active!
};
```

**Use std::variant:**
```cpp
#include <variant>
using Data = std::variant<int, double, std::string>;
// Safe access with std::get or std::visit
```

### 13. Prefer std::format Over printf/iostreams for Formatting (C++20)

**Instead of:**
```cpp
printf("ID: %d, Name: %s\n", id, name.c_str());
// Or: std::cout << "ID: " << id << ", Name: " << name << '\n';
```

**Use std::format:**
```cpp
#include <format>
std::cout << std::format("ID: {}, Name: {}\n", id, name);
```

### 14. Use Concepts for Better Template Error Messages (C++20)

**Instead of:**
```cpp
template<typename T>
T add(T a, T b) { return a + b; }
// Cryptic errors if T doesn't support +
```

**Use concepts:**
```cpp
#include <concepts>
template<std::regular T>
requires std::totally_ordered<T>
T add(T a, T b) { return a + b; }
// Clear error messages when requirements not met
```

### 15. Prefer Parallel Algorithms When Appropriate (C++17/20)

**Instead of:**
```cpp
std::transform(vec.begin(), vec.end(), vec.begin(), [](int x){ return x*2; });
```

**Use parallel algorithms:**
```cpp
#include <execution>
std::transform(std::execution::par, vec.begin(), vec.end(), vec.begin(),
               [](int x){ return x*2; });
```

### 16. Use Minimalist Syntax Where Clear

**Instead of verbose declarations:**
```cpp
std::vector<int> v = std::vector<int>();
```

**Use auto or direct initialization:**
```cpp
auto v = std::vector<int>{}; 
// or
std::vector v{1, 2, 3}; // Template Argument Deduction for Class Templates (CTAD)
```

**Simplified Function Syntax (C++11/14):**
```cpp
auto add(int x, int y) -> int { return x + y; } // Trailing return type
auto sub(int x, int y) { return x - y; } // Return type deduction (C++14)
```

### 17. Use 'Using' Over 'Typedef'

**Instead of:**
```cpp
typedef void (*Handler)(int);
```

**Use using (more readable, supports templates):**
```cpp
using Handler = void (*)(int);
template <typename T> using List = std::vector<T>;
```

### 18. Aggregate Initialization

For simple structs, avoid custom constructors to keep them as "Aggregates":
```cpp
struct Point { double x, y; };
Point p{1.0, 2.0}; // Minimalist and efficient
```

### Key Principles:
1. **Safety first**: Let the compiler help you catch errors
2. **Zero-overhead abstraction**: Modern features shouldn't cost you performance
3. **Readability**: Code should express intent clearly
4. **Maintainability**: Easy to modify and extend
5. **Simplicity**: Prefer the simplest syntax that is safe and expressive. Avoid "clever" code that is hard to read.

These practices will help you write C++ code that is safer, more readable, and easier to maintain while taking full advantage of modern language features.