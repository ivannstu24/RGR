#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "password.hpp"
#include "menu.hpp"
#include "encryption.hpp"
#include "tarabarska.hpp"
#include "atbash.hpp"

using namespace std;

int main() {
    cout << "-------------------------CryptoStorm-------------------------" << endl;

    string password;
    bool passwordCorrect = false;

    // Цикл для повторного ввода пароля в случае неправильного ввода
    do {
        // Ввод пароля
        cout << "Пароль:";
        cin >> password;

        // Проверка пароля
        if (!checkPassword(password)) {
            cout << "В доступе отказано. Попробуйте снова." << endl;
        } else {
            passwordCorrect = true;
        }
    } while (!passwordCorrect);

    // Вывод меню
    displayMenu();

    int choice;
    cout << "Выберите шифр: ";
    cin >> choice;
    
    cin.ignore();

    // Обработка выбора
    switch (choice) {
        case 1: {
            SimpleTable();
            break;
        }
        case 2: {
            Tarabara();
            break;
                }
        case 3:{
            atbash();
            break;
            
        }
        case 4:{
            cout << "Завершение работы..." << endl;
            break;
        }
        default:
            cout << "Некорректный выбор, попробуйте еще раз" << endl;
            break;
            
    }

    return 0;
}
