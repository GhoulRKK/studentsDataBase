#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <limits>

using namespace std;

struct Student {
    string name;
    int age = 0;        // инициализировал
    string major;
    double gpa = 0.0;   // инициализировал
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
            return (int)i;  // исправил преобразование
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

    // Добавляем меню редактирования
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

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    vector<Student> database;
    int choice;

    do {
        cout << "=== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ===\n";
        cout << "1. Добавить студента\n";
        cout << "2. Вывести список студентов\n";
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