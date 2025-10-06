#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct Student {
    string name;
    int age = 0;
    string major;
    double gpa = 0.0;
};

// Объявления функций из main.cpp
void addStudent(vector<Student>& database);
void displayStudents(const vector<Student>& database);
int findStudentByName(const vector<Student>& database, const string& name);
void displayStudentInfo(const Student& student);
void editStudent(vector<Student>& database);

// Тестовый класс для студенческой базы данных
class StudentDatabaseTest : public ::testing::Test {
protected:
    vector<Student> database;
    
    void SetUp() override {
        // Начальная настройка перед каждым тестом
        database.clear();
    }
    
    void TearDown() override {
        // Очистка после каждого теста
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

// Тест 1: Добавление студента в базу данных
TEST_F(StudentDatabaseTest, AddStudentTest) {
    // Подготовка
    stringstream input;
    input << "Иван\n20\nИнформатика\n4.5\n";
    
    // Сохраняем оригинальный cin и подменяем его
    auto origCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());
    
    // Действие
    addStudent(database);
    
    // Восстанавливаем оригинальный cin
    cin.rdbuf(origCin);
    
    // Проверка
    ASSERT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Иван");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "Информатика");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.5);
}

// Тест 2: Поиск студента по имени
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

// Тест 3: Редактирование имени студента
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
    EXPECT_EQ(database[0].age, 20); // возраст не должен измениться
    EXPECT_EQ(database[0].major, "Биология"); // специальность не должна измениться
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.6); // GPA не должен измениться
}

// Тест 4: Редактирование всех полей студента
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

// Тест 5: Попытка редактирования несуществующего студента
TEST_F(StudentDatabaseTest, EditNonExistentStudentTest) {
    // Подготовка
    addTestStudent("Сергей", 23, "Физика", 4.4);
    
    stringstream input;
    input << "Александр\n"; // несуществующее имя
    
    // Сохраняем вывод для проверки
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
    
    // Проверка, что студент не изменился
    EXPECT_EQ(database[0].name, "Сергей");
    EXPECT_EQ(database[0].age, 23);
    EXPECT_EQ(database[0].major, "Физика");
    EXPECT_DOUBLE_EQ(database[0].gpa, 4.4);
    
    // Проверяем, что вывелось сообщение об ошибке
    string outputStr = output.str();
    EXPECT_TRUE(outputStr.find("не найден") != string::npos);
}

// Тест 6: Редактирование в пустой базе данных
TEST_F(StudentDatabaseTest, EditEmptyDatabaseTest) {
    // База данных пустая
    
    stringstream input;
    input << "ЛюбоеИмя\n";
    
    // Сохраняем вывод для проверки
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
    
    // Проверяем, что вывелось сообщение о пустой базе
    string outputStr = output.str();
    EXPECT_TRUE(outputStr.find("пуста") != string::npos);
}

// Тест 7: Отображение информации о студенте
TEST_F(StudentDatabaseTest, DisplayStudentInfoTest) {
    // Подготовка
    Student testStudent;
    testStudent.name = "Екатерина";
    testStudent.age = 20;
    testStudent.major = "Математика";
    testStudent.gpa = 4.9;
    
    // Сохраняем вывод
    stringstream output;
    auto origCout = cout.rdbuf();
    cout.rdbuf(output.rdbuf());
    
    // Действие
    displayStudentInfo(testStudent);
    
    // Восстанавливаем
    cout.rdbuf(origCout);
    
    // Проверка
    string outputStr = output.str();
    EXPECT_TRUE(outputStr.find("Екатерина") != string::npos);
    EXPECT_TRUE(outputStr.find("20") != string::npos);
    EXPECT_TRUE(outputStr.find("Математика") != string::npos);
    EXPECT_TRUE(outputStr.find("4.9") != string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}