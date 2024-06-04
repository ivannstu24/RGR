#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "password.hpp"
#include "menu.hpp"
#include "encryption.hpp"
#include "tarabarska.hpp"





int main() {
    std::cout << "\"ШИФРАТОР 2000\"" << std::endl;

    std::string password;
    bool passwordCorrect = false;

    // Цикл для повторного ввода пароля в случае неправильного ввода
    do {
        // Ввод пароля
        std::cout << "Пароль:";
        std::cin >> password;

        // Проверка пароля
        if (!checkPassword(password)) {
            std::cout << "Неправильный пароль. Попробуйте снова." << std::endl;
        } else {
            passwordCorrect = true;
        }
    } while (!passwordCorrect);

    // Вывод меню
    displayMenu();

    int choice;
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    
    std::cin.ignore();

    // Обработка выбора
    switch (choice) {
        case 1: {
            
            std::string message;
            int rows, cols;
            int choice;

            std::cout << "Выберите источник сообщения: 1 - файл, 2 - ввод с консоли: ";
            std::cin >> choice;
            std::cin.ignore(); // Игнорируем оставшийся символ новой строки после ввода числа

            if (choice == 1) {
                std::ifstream infile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/default_text.txt");
                if (infile.is_open()) {
                    std::ostringstream ss;
                    ss << infile.rdbuf();
                    message = ss.str();
                    infile.close();
                    std::cout << "Сообщение успешно прочитано из файла default_message.txt." << std::endl;
                } else {
                    std::cerr << "Ошибка открытия файла default_message.txt." << std::endl;
                    break;
                }
            } else if (choice == 2) {
                std::cout << "Введите сообщение: ";
                std::getline(std::cin, message);
            } else {
                std::cerr << "Неверный выбор." << std::endl;
                break;
            }

            std::cout << "Введите количество строк: ";
            std::cin >> rows;

            std::cout << "Введите количество столбцов: ";
            std::cin >> cols;

            std::string cipherText = encrypt(message, rows, cols);
            std::string decryptedMessage = decrypt(cipherText, rows, cols);

            std::cout << "Зашифрованное сообщение: " << cipherText << std::endl;
            std::cout << "Расшифрованное сообщение: " << decryptedMessage << std::endl;

            // Запись зашифрованного сообщения в файл
            std::ofstream outfile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/encrypted_text.txt");
            if (outfile.is_open()) {
                outfile << cipherText;
                outfile.close();
                std::cout << "Зашифрованное сообщение успешно записано в файл encrypted_message.txt" << std::endl;
            } else {
                std::cerr << "Ошибка открытия файла для записи" << std::endl;
            }
            break;
        }
        case 2: {
            std::unordered_map<char, char> tarabarska_map = createTarabarskaMap();
                       std::string text;
                       int choice;
                       std::cout << "Выберите источник текста: 1 - файл, 2 - ввод с консоли: ";
                       std::cin >> choice;
                       std::cin.ignore(); // Игнорируем оставшийся символ новой строки после ввода числа

                       if (choice == 1) {
                           std::ifstream infile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/default_text.txt");
                           if (infile.is_open()) {
                               std::ostringstream ss;
                               ss << infile.rdbuf();
                               text = ss.str();
                               infile.close();
//                               std::cout << "Текст успешно прочитан из файла default_text.txt." << std::endl;
                           } else {
                               std::cerr << "Ошибка открытия файла default_text.txt." << std::endl;
                               break;
                           }
                       } else if (choice == 2) {
                           std::cout << "Введите текст для шифрования: ";
                           std::getline(std::cin, text);
                       } else {
                           std::cerr << "Неверный выбор." << std::endl;
                           break;
                       }

                       std::string encrypted_text = tarabarskaCipher(text, tarabarska_map);
                       std::string decrypted_text = tarabarskaCipher(encrypted_text, tarabarska_map);
//                       std::cout << "Исходный текст: " << text << std::endl;
                       std::cout << "Зашифрованный текст: " << encrypted_text << std::endl;
                       std::cout << "Расшифрованный текст: " << decrypted_text << std::endl;

                       // Запись зашифрованного текста в файл
                       std::ofstream outfile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/encrypted_text.txt");
                       if (outfile.is_open()) {
                           outfile << encrypted_text;
                           outfile.close();
                           std::cout << "Зашифрованный текст успешно записан в файл encrypted_text.txt" << std::endl;
                       } else {
                           std::cerr << "Ошибка открытия файла для записи" << std::endl;
                       }
                       break;
                }
        default:
            std::cout << "Некорректный выбор, попробуйте еще раз" << std::endl;
            break;
    }

    return 0;
}
