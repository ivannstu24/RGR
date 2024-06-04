//
//  encryption.cpp
//  RGR_DEV
//
//  Created by Иван Мерзов on 30.05.2024.
//

#include "encryption.hpp"

#include <vector>
#include <string>

std::string padMessage(const std::string& message, int rows, int cols) {
    std::string paddedMessage = message;
       int totalChars = rows * cols;
       while (paddedMessage.size() < totalChars) {
           paddedMessage += ' ';
       }
       return paddedMessage;
}

std::string encrypt(const std::string& message, int rows, int cols) {
    std::string paddedMessage = padMessage(message, rows, cols);
        std::vector<std::vector<char>> table(rows, std::vector<char>(cols, ' '));

        int index = 0;
        for (int col = 0; col < cols; ++col) {
            for (int row = 0; row < rows; ++row) {
                if (index < paddedMessage.size()) {
                    table[row][col] = paddedMessage[index++];
                }
            }
        }

        std::string cipherText;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                cipherText += table[row][col];
            }
        }
        return cipherText;
}

std::string decrypt(const std::string& cipherText, int rows, int cols) {
    std::vector<std::vector<char>> table(rows, std::vector<char>(cols, ' '));

       int index = 0;
       for (int row = 0; row < rows; ++row) {
           for (int col = 0; col < cols; ++col) {
               if (index < cipherText.size()) {
                   table[row][col] = cipherText[index++];
               }
           }
       }

       std::string message;
       for (int col = 0; col < cols; ++col) {
           for (int row = 0; row < rows; ++row) {
               message += table[row][col];
           }
       }

       // �������� �������⥫��� �஡����, ����� ����� ���� ��������� �� ��஢����
       while (!message.empty() && std::isspace(message.back())) {
           message.pop_back();
       }

       return message;
}
