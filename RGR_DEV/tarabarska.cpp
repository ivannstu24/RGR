
#include "tarabarska.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;
namespace fs = std::filesystem;




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
    
    if (choice > 2){
        cout << "Неверынй выбор. Попробуйте еще раз! \n";
        Tarabara();
    }
    cin.ignore(); // Игнорируем оставшийся символ новой строки после ввода числа
    
    std::string filePath;
    
    
    if (choice == 1) {
        while (true) {
            cout << "Введите путь к файлу который будем шифровать: ";
            getline(cin, filePath);
            
            ifstream infile(filePath);
            if (infile.is_open()) {
                ostringstream ss;
                ss << infile.rdbuf();
                text = ss.str();
                infile.close();
                cout << "Текст успешно прочитан из файла " << filePath << endl;
                break;
            } else {
                cout << "Ошибка открытия файла. Пожалуйста, попробуйте снова." << endl;
            }
        }
    }
    else if (choice == 2) {
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
                    outfile << encrypted_text;
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
