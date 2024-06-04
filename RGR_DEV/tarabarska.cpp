//
//  tarabarska.cpp
//  RGR_DEV
//
//  Created by Иван Мерзов on 30.05.2024.
//

#include "tarabarska.hpp"

#include <unordered_map>
#include <string>

std::unordered_map<char, char> createTarabarskaMap() {
    std::string consonants_top = "БВГДЖЗКЛМН";
       std::string consonants_bottom = "ЩШЧЦХФТСРП";
       std::unordered_map<char, char> tarabarska_map;

       for (size_t i = 0; i < consonants_top.size(); ++i) {
           tarabarska_map[consonants_top[i]] = consonants_bottom[i];
           tarabarska_map[consonants_bottom[i]] = consonants_top[i];
       }

       // ��������� ������� ������ �������
       std::string vowels_top = "АЕЁИО";
       std::string vowels_bottom = "ЯЮЭЫУ";
       for (size_t i = 0; i < vowels_top.size(); ++i) {
           tarabarska_map[vowels_top[i]] = vowels_bottom[i];
           tarabarska_map[vowels_bottom[i]] = vowels_top[i];
       }

       return tarabarska_map;
}

std::string tarabarskaCipher(const std::string& text, const std::unordered_map<char, char>& tarabarska_map) {
    // ... (остальная часть функции)
    std::string encrypted_text;
       for (char c : text) {
           auto it = tarabarska_map.find(toupper(c)); // ���������� toupper ��� ��������� �������� ����
           if (it != tarabarska_map.end()) {
               encrypted_text += it->second;
           } else {
               encrypted_text += c;
           }
       }
       return encrypted_text;
}
