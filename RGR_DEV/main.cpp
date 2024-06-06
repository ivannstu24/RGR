#include <iostream>
#include <string>
#include <fstream>
#include "password.hpp"
#include "menu.hpp"
#include "encryption.hpp"
#include "tarabarska.hpp"
#include "atbash.hpp"


// 010635457
//  "/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/default_text1.txt"
// "/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/encrypted_text.txt"


using namespace std;

int main() {
    cout << "-------------------------CryptoStorm-------------------------" << endl;
    
    string password;
    bool passwordCorrect = false;
    
    do {
        cout << "Пароль:";
        cin >> password;
        
        // Проверка пароля
        if (!checkPassword(password)) {
            cout << "В доступе отказано. Попробуйте снова." << endl;
        } else {
            passwordCorrect = true;
        }
    } while (!passwordCorrect);
    
    displayMenu();
    
    int choice;
    do {
        
        cout << "Выберите шифр: ";
        cin >> choice;
        
        cin.ignore();
        
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
        }  } while (choice != 4);
        
        return 0;
    }

