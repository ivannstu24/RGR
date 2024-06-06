#include "Check.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>





// Функция для записи зашифрованного сообщения в файл
void writeEncryptedTextToFile() {
    std::string filePath2;
    std::string cipherText; // Замените на ваш зашифрованный текст
    bool fileExists = false;

        // Запись зашифрованного сообщения в файл
        std::cout << "Введите путь к файлу, в который нужно записать зашифрованный текст: ";
        std::cin.ignore(); // Очищаем буфер ввода, чтобы не было мусора
        std::getline(std::cin, filePath2); // Читаем всю строку, включая пробелы

        // Проверяем, существует ли файл
        fileExists = std::filesystem::exists(filePath2);

        if (fileExists) {
            std::ofstream outfile(filePath2);
            if (outfile.is_open()) {
                outfile << cipherText;
                outfile.close();
                std::cout << "Зашифрованный текст успешно записан в файл " << filePath2 << std::endl;
            } else {
                std::cout << "Ошибка открытия файла." << std::endl;
            }
        } else {
            std::cout << "Файл не существует. Введите путь еще раз:" << std::endl;
        }
   
}
