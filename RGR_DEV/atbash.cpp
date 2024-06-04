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
#include <unordered_map>

using namespace std;

// Atbash encryption/decryption for English text
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

// Tarabar encryption/decryption for Russian text
string tarabarEncryptDecrypt(const string& text) {
    string consonants_top = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    string consonants_bottom = "ЯЮЭЬЫЪЩШЧЦХФУТСРПОНМЛКЙИЗЖЁЕДГВБА";
    unordered_map<char, char> tarabarska_map;

    for (size_t i = 0; i < consonants_top.size(); ++i) {
        tarabarska_map[consonants_top[i]] = consonants_bottom[i];
        tarabarska_map[consonants_bottom[i]] = consonants_top[i];
        tarabarska_map[tolower(consonants_top[i])] = tolower(consonants_bottom[i]);
        tarabarska_map[tolower(consonants_bottom[i])] = tolower(consonants_top[i]);
    }

    string result = "";
    for (char c : text) {
        if (tarabarska_map.find(c) != tarabarska_map.end()) {
            result += tarabarska_map[c];
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
            return; // Возврат из функции в случае ошибки открытия файла
        }
    }

    string encryptedText, decryptedText;
    if (languageChoice == 1) {
        encryptedText = tarabarEncryptDecrypt(text);
        decryptedText = tarabarEncryptDecrypt(encryptedText);
    } else {
        encryptedText = atbashEncryptDecrypt(text, ALPHABET_engl);
        decryptedText = atbashEncryptDecrypt(encryptedText, ALPHABET_engl);
    }

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

    cout << "Нажмите Enter для выхода" << endl;
    cin.ignore();
    main();
}
