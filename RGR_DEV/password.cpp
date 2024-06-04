//
//  password.cpp
//  RGR_DEV
//
//  Created by Иван Мерзов on 30.05.2024.
//

#include "password.hpp"

#include <iostream>
#include <fstream>

bool checkPassword(const std::string& inputPassword) {
    std::ifstream passwordFile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/password.txt");
    if (!passwordFile) {
        std::cerr << "Ошибка при открытии файла с паролем" << std::endl;
        return false;
    }

    std::string storedPassword;
    std::getline(passwordFile, storedPassword);

    passwordFile.close();

    return (inputPassword == storedPassword);
}
