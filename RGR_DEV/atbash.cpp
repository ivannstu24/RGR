//
//  atbash.cpp
//  RGR_DEV
//
//  Created by Иван Мерзов on 05.06.2024.
//

#include "atbash.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;



string atbashEncryptDecrypt(const string& text, const string& alphabet) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            bool isLower = islower(c);
            char base = isLower ? tolower(alphabet[0]) : alphabet[0];
            int idx = alphabet.find(toupper(c));
            result += isLower ? tolower(alphabet[alphabet.size() - 1 - idx]) : alphabet[alphabet.size() - 1 - idx];
        } else {
            result += c;
        }
    }
    return result;
}


void atbash() {
    int languageChoice, inputChoice;
      string text, filename;

      string ALPHABET_engl = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      string ALPHABET_rus = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

      while (true) {
          do {
              cout << "1)RUS \n2)ENG \nLANGUAGE: ";
              cin >> languageChoice;
          } while (languageChoice != 1 && languageChoice != 2);

          do {
              cout << "Выберите источник текста: 1 - ввод с консоли, 2 - файл: ";
              cin >> inputChoice;
          } while (inputChoice != 1 && inputChoice != 2);

          cin.ignore(); // Игнорируем остаток строки после ввода числа

          if (inputChoice == 1) {
              cout << "Введите текст для шифрования: ";
              getline(cin, text);
          } else if (inputChoice == 2) {
              filename = "/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/default_text.txt";
              ifstream inputFile(filename);
              if (inputFile.is_open()) {
                  getline(inputFile, text, '\0'); // Читаем весь файл в строку
                  inputFile.close();
              } else {
                  cout << "Не удалось открыть файл " << filename << endl;
                  continue; // Возврат к началу цикла для повторного ввода
              }
          }

          string alphabet = (languageChoice == 1) ? ALPHABET_rus : ALPHABET_engl;
          string encryptedText = atbashEncryptDecrypt(text, alphabet);
          string decryptedText = atbashEncryptDecrypt(encryptedText, alphabet);

          cout << "Зашифрованный текст: " << encryptedText << endl;
          cout << "Расшифрованный текст: " << decryptedText << endl;
          
          
          // Запись зашифрованного текста в файл
          ofstream outfile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/encrypted_text.txt");
          if (outfile.is_open()) {
              outfile << encryptedText;
              outfile.close();
              cout << "Зашифрованный текст успешно записан в файл encrypted_text.txt" << endl;
              
          } else {
              cout << "Ошибка открытия файла для записи" << endl;
          }
          cout << "Нажмите Enter для выбора другого шифра" << endl;
          cin.ignore();
          main();
      }
}


