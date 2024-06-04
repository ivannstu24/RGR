//
//  tarabarska.cpp
//  RGR_DEV
//
//  Created by Иван Мерзов on 30.05.2024.
//

#include "tarabarska.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;




unordered_map<char, char> createTarabarskaMap() {
    string consonants_top = "БВГДЖЗКЛМН";
       string consonants_bottom = "ЩШЧЦХФТСРП";
       unordered_map<char, char> tarabarska_map;

       for (size_t i = 0; i < consonants_top.size(); ++i) {
           tarabarska_map[consonants_top[i]] = consonants_bottom[i];
           tarabarska_map[consonants_bottom[i]] = consonants_top[i];
       }

       string vowels_top = "АЕЁИО";
       string vowels_bottom = "ЯЮЭЫУ";
       for (size_t i = 0; i < vowels_top.size(); ++i) {
           tarabarska_map[vowels_top[i]] = vowels_bottom[i];
           tarabarska_map[vowels_bottom[i]] = vowels_top[i];
       }

       return tarabarska_map;
}




string tarabarskaCipher(const string& text, const unordered_map<char, char>& tarabarska_map) {
    
    string encrypted_text;
       for (char c : text) {
           auto it = tarabarska_map.find(toupper(c));
           if (it != tarabarska_map.end()) {
               encrypted_text += it->second;
           } else {
               encrypted_text += c;
           }
       }
       return encrypted_text;
}




void Tarabara(){
    unordered_map<char, char> tarabarska_map = createTarabarskaMap();

    string text;
    int choice;
    cout << "Выберите источник текста: 1 - файл, 2 - ввод с консоли: ";
    cin >> choice;
    cin.ignore(); // Игнорируем оставшийся символ новой строки после ввода числа

    if (choice == 1) {
        ifstream infile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/default_text.txt");
        if (infile.is_open()) {
            ostringstream ss;
            ss << infile.rdbuf();
            text = ss.str();
            infile.close();
//                               cout << "Текст успешно прочитан из файла default_text.txt." << endl;
        } else {
            cout << "Ошибка открытия файла default_text.txt." << endl;
            
        }
    } else if (choice == 2) {
        cout << "Введите текст для шифрования: ";
        getline(cin, text);
    } else {
        cout << "Неверный выбор." << endl;
       
    }

    string encrypted_text = tarabarskaCipher(text, tarabarska_map);
    string decrypted_text = tarabarskaCipher(encrypted_text, tarabarska_map);
//                       cout << "Исходный текст: " << text << endl;
    cout << "Зашифрованный текст: " << encrypted_text << endl;
    cout << "Расшифрованный текст: " << decrypted_text << endl;

    // Запись зашифрованного текста в файл
    ofstream outfile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/encrypted_text.txt");
    if (outfile.is_open()) {
        outfile << encrypted_text;
        outfile.close();
        cout << "Зашифрованный текст успешно записан в файл encrypted_text.txt" << endl;
    } else {
        cout << "Ошибка открытия файла для записи" << endl;
    }
    cout << "Нажмите Enter для выбора другого шифра" << endl;
    cin.ignore();
    main();
}
