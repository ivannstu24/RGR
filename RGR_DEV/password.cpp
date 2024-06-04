//
//  password.cpp
//  RGR_DEV
//
//  Created by Иван Мерзов on 30.05.2024.
//

#include "password.hpp"

#include <iostream>
#include <fstream>

using namespace std;

bool checkPassword(const string& inputPassword) {
    ifstream passwordFile("/Users/ivanmerzov/Desktop/RGR_DEV/RGR_DEV/password1/password.txt");
    if (!passwordFile) {
        cerr << "Ошибка при открытии файла с паролем" << endl;
        return false;
    }

    string storedPassword;
    getline(passwordFile, storedPassword);

    passwordFile.close();

    return (inputPassword == storedPassword);
}
