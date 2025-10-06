#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <sstream>
#include <gtest/gtest.h>

using namespace std;

struct Student {
    string name;
    int age = 0;
    string major;
    double gpa = 0.0;
};

// Функция для добавления студента
void addStudent(vector<Student>& database) {
    Student student;
    cout << "Введите имя студента: ";
    cin >> student.name;
    cout << "Введите возраст студента: ";
    cin >> student.age;
    cout << "Введите специальность студента: ";
    cin >> student.major;
    cout << "Введите средний балл студента: ";
    cin >> student.gpa;

    database.push_back(student);
    cout << "Студент добавлен в базу данных.\n";
}

// Функция для вывода всех студентов
void displayStudents(const vector<Student>& database) {
    if (database.empty()) {
        cout << "База данных пуста.\n";
        return;
    }

    cout << "Список студентов:\n";
    for (size_t i = 0; i < database.size(); ++i) {
        cout << "ID: " << i + 1 << "\n";
        cout << "Имя: " << database[i].name << "\n";
        cout << "Возраст: " << database[i].age << "\n";
        cout << "Специальность: " << database[i].major << "\n";
        cout << "Средний балл: " << database[i].gpa << "\n\n";
    }
}

// Функция для поиска студента по имени
int findStudentByName(const vector<Student>& database, const string& name) {
    for (size_t i = 0; i < database.size(); ++i) {
        if (database[i].name == name) {
            return (int)i;
        }
    }
    return -1;
}

// Функция для отображения информации о конкретном студенте
void displayStudentInfo(const Student& student) {
    cout << "=== ИНФОРМАЦИЯ О СТУДЕНТЕ ===\n";
    cout << "Имя: " << student.name << "\n";
    cout << "Возраст: " << student.age << "\n";
    cout << "Специальность: " << student.major << "\n";
    cout << "Средний балл: " << student.gpa << "\n";
    cout << "==============================\n";
}

// Функция для редактирования информации о студенте
void editStudent(vector<Student>& database) {
    if (database.empty()) {
        cout << "База данных пуста. Нечего редактировать.\n";
        return;
    }

    string searchName;
    cout << "Введите имя студента для редактирования: ";
    cin >> searchName;

    int studentIndex = findStudentByName(database, searchName);

    if (studentIndex == -1) {
        cout << "Студент с именем '" << searchName << "' не найден.\n";
        return;
    }

    cout << "\n=== РЕДАКТИРОВАНИЕ СТУДЕНТА ===\n";
    displayStudentInfo(database[studentIndex]);

    int editChoice;
    do {
        cout << "\nЧто вы хотите отредактировать?\n";
        cout << "1. Имя\n";
        cout << "2. Возраст\n";
        cout << "3. Специальность\n";
        cout << "4. Средний балл\n";
        cout << "0. Завершить редактирование\n";
        cout << "Выберите поле для редактирования: ";
        cin >> editChoice;

        switch (editChoice) {
        case 1:
            cout << "Введите новое имя: ";
            cin >> database[studentIndex].name;
            cout << "Имя обновлено.\n";
            break;
        case 2:
            cout << "Введите новый возраст: ";
            cin >> database[studentIndex].age;
            cout << "Возраст обновлен.\n";
            break;
        case 3:
            cout << "Введите новую специальность: ";
            cin >> database[studentIndex].major;
            cout << "Специальность обновлена.\n";
            break;
        case 4:
            cout << "Введите новый средний балл: ";
            cin >> database[studentIndex].gpa;
            cout << "Средний балл обновлен.\n";
            break;
        case 0:
            cout << "Редактирование завершено.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (editChoice != 0);
}

// ==================== ТЕСТЫ ====================

// Тестовый класс
class StudentDatabaseTest : public ::testing::Test {
protected:
    vector<Student> database;
    
    void SetUp() override {
        database.clear();
    }
    
    void TearDown() override {
        database.clear();
    }
    
    // Вспомогательная функция для добавления тестового студента
    void addTestStudent(const string& name, int age, const string& major, double gpa) {
        Student student;
        student.name = name;
        student.age = age;
        student.major = major;
        student.gpa = gpa;
        database.push_back(student);
    }
};

// Тест 1: Поиск студента по имени
TEST_F(StudentDatabaseTest, FindStudentByNameTest) {
    // Подготовка
    addTestStudent("Петр", 21, "Математика", 4.7);
    addTestStudent("Мария", 19, "Физика", 4.3);
    addTestStudent("Алексей", 22, "Химия", 4.1);
    
    // Действие и проверка
    EXPECT_EQ(findStudentByName(database, "Мария"), 1);
    EXPECT_EQ(findStudentByName(database, "Петр"), 0);
    EXPECT_EQ(findStudentByName(database, "Алексей"), 2);
    EXPECT_EQ(findStudentByName(database, "Несуществующий"), -1);
}

// Тест 2: Редактирование имени студента
TEST_F(StudentDatabaseTest, EditStudentNameTest) {
    // Подготовка
    addTestStudent("Ольга", 20, "Биология", 4.6);
    
    stringstream input;
    input << "Ольга\n1\nАнна\n0\n";
    
    auto origCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());
    
    // Действие
    editStudent(database);
    
    // Восстанавливаем
    cin.rdbuf(origCin);
    
    // Проверка
    EXPECT_EQ(database[0].name, "Анна");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "Биология");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.6);
}

// Тест 3: Редактирование всех полей студента
TEST_F(StudentDatabaseTest, EditAllStudentFieldsTest) {
    // Подготовка
    addTestStudent("Дмитрий", 21, "Информатика", 4.2);
    
    stringstream input;
    input << "Дмитрий\n1\nДенис\n2\n22\n3\nПрограммирование\n4\n4.8\n0\n";
    
    auto origCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());
    
    // Действие
    editStudent(database);
    
    // Восстанавливаем
    cin.rdbuf(origCin);
    
    // Проверка
    EXPECT_EQ(database[0].name, "Денис");
    EXPECT_EQ(database[0].age, 22);
    EXPECT_EQ(database[0].major, "Программирование");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.8);
}

// Тест 4: Попытка редактирования несуществующего студента
TEST_F(StudentDatabaseTest, EditNonExistentStudentTest) {
    // Подготовка
    addTestStudent("Сергей", 23, "Физика", 4.4);
    
    stringstream input;
    input << "Александр\n";
    
    stringstream output;
    auto origCout = cout.rdbuf();
    cout.rdbuf(output.rdbuf());
    
    auto origCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());
    
    // Действие
    editStudent(database);
    
    // Восстанавливаем
    cin.rdbuf(origCin);
    cout.rdbuf(origCout);
    
    // Проверка
    EXPECT_EQ(database[0].name, "Сергей");
    EXPECT_EQ(database[0].age, 23);
    EXPECT_EQ(database[0].major, "Физика");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.4);
    
    string outputStr = output.str();
    EXPECT_TRUE(outputStr.find("не найден") != string::npos);
}

// Тест 5: Редактирование в пустой базе данных
TEST_F(StudentDatabaseTest, EditEmptyDatabaseTest) {
    // База данных пустая
    
    stringstream input;
    input << "ЛюбоеИмя\n";
    
    stringstream output;
    auto origCout = cout.rdbuf();
    cout.rdbuf(output.rdbuf());
    
    auto origCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());
    
    // Действие
    editStudent(database);
    
    // Восстанавливаем
    cin.rdbuf(origCin);
    cout.rdbuf(origCout);
    
    // Проверка
    EXPECT_TRUE(database.empty());
    
    string outputStr = output.str();
    EXPECT_TRUE(outputStr.find("пуста") != string::npos);
}

// ==================== ОСНОВНАЯ ПРОГРАММА ====================

int main(int argc, char **argv) {
    // Если переданы аргументы командной строки, запускаем тесты
    if (argc > 1 && string(argv[1]) == "--test") {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    
    // Иначе запускаем обычную программу
    vector<Student> database;
    int choice;

    do {
        cout << "=== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ===\n";
        cout << "1. Добавить студента\n";
        cout << "2. Вывести список студентов\n";
        cout << "3. Редактировать информацию о студенте\n";
        cout << "4. Запустить тесты\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent(database);
            break;
        case 2:
            displayStudents(database);
            break;
        case 3:
            editStudent(database);
            break;
        case 4:
            // Запуск тестов из меню
            {
                cout << "Запуск тестов...\n";
                int test_argc = 2;
                char* test_argv[] = {(char*)"program", (char*)"--test", nullptr};
                ::testing::InitGoogleTest(&test_argc, test_argv);
                int result = RUN_ALL_TESTS();
                cout << "Тесты завершены с результатом: " << (result == 0 ? "УСПЕХ" : "НЕУДАЧА") << "\n";
            }
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
        cout << "\n";
    } while (choice != 0);

    return 0;
}