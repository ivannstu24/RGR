#include "encryption.hpp"

#include <iostream>
#include <sstream>

#include <fstream>
#include <vector>
#include <string>

using namespace std;
namespace fs = std::filesystem;


void SimpleTable() {
    string message;
    int rows, cols;
    int choice;
    cout << "-------------------------CryptoStorm-------------------------" << endl;

    cout << "Выберите источник сообщения: 1 - файл, 2 - ввод с консоли: ";
    cin >> choice;
    
    if (choice > 2){
        cout << "Неверынй выбор. Попробуйте еще раз! \n";
        SimpleTable();
    }
    
    cin.ignore();

    std::string filePath;

    if (choice == 1) {
        while (true) {
            cout << "Введите путь к файлу который будем шифровать: ";
            getline(cin, filePath);

            ifstream infile(filePath);
            if (infile.is_open()) {
                ostringstream ss;
                ss << infile.rdbuf();
                message = ss.str();
                infile.close();
                cout << "Текст успешно прочитан из файла " << filePath << endl;
                break;
            } else {
                cout << "Ошибка открытия файла. Пожалуйста, попробуйте снова." << endl;
            }
        }
    } else if (choice == 2) {
        cout << "Введите текст: ";
        getline(cin, message);
    } else {
        cout << "Неверный выбор." << endl;
        return;
    }
      char input[100]; // Массив для ввода пользовательских данных

      cout << "Введите количество строк: ";
      cin.getline(input, 100); // Считываем строку с помощью getline()

      // Проверяем каждый символ в строке на то, является ли он цифрой
      bool allDigits = true;
      for (int i = 0; input[i] != '\0'; ++i) {
          if (!isdigit(input[i])) {
              allDigits = false;
              break;
          }
      }

      if (!allDigits) {
          cout << "Ошибка! Введено не число для количества строк." << endl;
          SimpleTable(); // Завершаем программу с ошибкой
      }

      rows = atoi(input); // Преобразуем строку в целое число

      if (rows >= 35) {
          cout << "Внимание! Слишком большое количество строк!" << endl;
          SimpleTable(); // Завершаем программу с ошибкой
      }

      cout << "Введите количество столбцов: ";
      cin.getline(input, 100); // Считываем строку с помощью getline()

      // Проверяем каждый символ в строке на то, является ли он цифрой
      allDigits = true;
      for (int i = 0; input[i] != '\0'; ++i) {
          if (!isdigit(input[i])) {
              allDigits = false;
              break;
          }
      }

      if (!allDigits) {
          cout << "Ошибка! Введено не число для количества столбцов." << endl;
          SimpleTable(); // Завершаем программу с ошибкой
      }

      cols = atoi(input); // Преобразуем строку в целое число

      if (cols >= 35) {
          cout << "Внимание! Слишком большое количество столбцов!" << endl;
          SimpleTable(); // Завершаем программу с ошибкой
      }


    string cipherText = encrypt(message, rows, cols);
    string decryptedMessage = decrypt(cipherText, rows, cols);

    cout << "Зашифрованное текст: " << cipherText << endl;
    cout << "Расшифрованное текст: " << decryptedMessage << endl;

    
    
    std::string filePath2;
        while (true) {
            // Запись зашифрованного сообщения в файл
            cout << "Введите путь к файлу, в который нужно записать зашифрованный текст: ";
            cin.ignore(); // Очищаем буфер ввода, чтобы не было мусора
            getline(cin, filePath2); // Читаем всю строку, включая пробелы

            fs::path dirPath = fs::path(filePath2).parent_path();
            if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
                ofstream outfile(filePath2);
                if (outfile.is_open()) {
                    outfile << cipherText;
                    outfile.close();
                    cout << "Зашифрованный текст успешно записан в файл " << filePath2 << endl;
                    break;
                } else {
                    cout << "Ошибка открытия файла для записи. Пожалуйста, попробуйте снова." << endl;
                }
            } else {
                cout << "Неверный путь. Введите еще раз " << endl;
            }
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

