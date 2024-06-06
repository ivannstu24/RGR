#include "atbash.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;
namespace fs = std::filesystem;

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

string tarabarEncryptDecrypt(const string& text) {
    string consonants_top = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    string consonants_bottom = "ЯЮЭЬЫЪЩШЧЦХФУТСРПОНМЛКЙИЗЖЁЕДГВБА";
    map<char, char> tarabarska_map;

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

    cin.ignore();

    if (inputChoice == 1) {
        cout << "Введите текст для шифрования: ";
        getline(cin, text);
    } else if (inputChoice == 2) {
        while (true) {
            cout << "Введите путь к файлу который будем шифровать: ";
            getline(cin, filename);

            ifstream infile(filename);
            if (infile.is_open()) {
                ostringstream ss;
                ss << infile.rdbuf();
                text = ss.str();
                infile.close();
                cout << "Текст успешно прочитан из файла " << filename << endl;
                break;
            } else {
                cout << "Ошибка открытия файла. Пожалуйста, попробуйте снова." << endl;
            }
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

    string filePath2;
    while (true) {
        cout << "Введите путь к файлу, в который нужно записать зашифрованный текст: ";
        getline(cin, filePath2); // Читаем всю строку, включая пробелы

        fs::path dirPath = fs::path(filePath2).parent_path();
        if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
            ofstream outfile(filePath2);
            if (outfile.is_open()) {
                outfile << encryptedText;
                outfile.close();
                cout << "Зашифрованный текст успешно записан в файл " << filePath2 << endl;
                break;
            } else {
                cout << "Ошибка открытия файла для записи. Пожалуйста, попробуйте снова." << endl;
            }
        } else {
            cout << "Неверный путь. Введите еще раз: " << endl;
        }
    }

    cout << "Нажмите Enter для выбора другого шифра" << endl;
    cin.get(); // Ждем нажатия Enter
    cin.ignore();
    main(); // Рекурсивно вызываем atbash() для выбора другого шифра
}
