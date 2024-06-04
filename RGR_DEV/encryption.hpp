//
//  encryption.hpp
//  RGR_DEV
//
//  Created by Иван Мерзов on 30.05.2024.
//

#ifndef encryption_hpp
#define encryption_hpp

#include <stdio.h>

#include <string>
#include <vector>

std::string padMessage(const std::string& message, int rows, int cols);
std::string encrypt(const std::string& message, int rows, int cols);
std::string decrypt(const std::string& cipherText, int rows, int cols);


#endif /* encryption_hpp */

