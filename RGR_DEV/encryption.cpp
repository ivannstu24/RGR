//
//  encryption.cpp
//  RGR_DEV
//
//  Created by Иван Мерзов on 30.05.2024.
//

#include "encryption.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;




void SimpleTable(){
    
    string message;
    int rows, cols;
    int choice;
    cout << "-------------------------CryptoStorm-------------------------" << endl;

    cout << "Выберите источник сообщения: 1 - файл, 2 - ввод с консоли: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        ifstream infile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/default_text.txt");
        if (infile.is_open()) {
            ostringstream ss;
            ss << infile.rdbuf();
            message = ss.str();
            infile.close();
            cout << "текст успешно прочитано из файла default_message.txt." << endl;
        } else {
            cout << "Ошибка открытия файла default_message.txt." << endl;
        }
    } else if (choice == 2) {
        cout << "Введите текст: ";
        getline(cin, message);
    } else {
        cout << "Неверный выбор." << endl;
    }

    cout << "Введите количество строк: ";
    cin >> rows;

    cout << "Введите количество столбцов: ";
    cin >> cols;

    string cipherText = encrypt(message, rows, cols);
    string decryptedMessage = decrypt(cipherText, rows, cols);

    cout << "Зашифрованное текст: " << cipherText << endl;
    cout << "Расшифрованное текст: " << decryptedMessage << endl;

    // Запись зашифрованного сообщения в файл
    ofstream outfile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/encrypted_text.txt");
    if (outfile.is_open()) {
        outfile << cipherText;
        outfile.close();
        cout << "Зашифрованный текст успешно записан в файл encrypted_message.txt" << endl;
    } else {
        cout << "Ошибка открытия файла для записи зашифрованного текста" << endl;
    }
    cout << "Нажмите Enter для выбора другого шифра" << endl;
    cin.ignore();
    main();
}






string padMessage(const string& message, int rows, int cols) {
    string paddedMessage = message;
       int totalChars = rows * cols;
       while (paddedMessage.size() < totalChars) {
           paddedMessage += ' ';
       }
       return paddedMessage;
}

string encrypt(const string& message, int rows, int cols) {
    string paddedMessage = padMessage(message, rows, cols);
        vector<vector<char>> table(rows, vector<char>(cols, ' '));

        int index = 0;
        for (int col = 0; col < cols; ++col) {
            for (int row = 0; row < rows; ++row) {
                if (index < paddedMessage.size()) {
                    table[row][col] = paddedMessage[index++];
                }
            }
        }

        string cipherText;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                cipherText += table[row][col];
            }
        }
        return cipherText;
}

string decrypt(const string& cipherText, int rows, int cols) {
    vector<vector<char>> table(rows, vector<char>(cols, ' '));

       int index = 0;
       for (int row = 0; row < rows; ++row) {
           for (int col = 0; col < cols; ++col) {
               if (index < cipherText.size()) {
                   table[row][col] = cipherText[index++];
               }
           }
       }

       string message;
       for (int col = 0; col < cols; ++col) {
           for (int row = 0; row < rows; ++row) {
               message += table[row][col];
           }
       }

       while (!message.empty() && isspace(message.back())) {
           message.pop_back();
       }

       return message;
    
}
