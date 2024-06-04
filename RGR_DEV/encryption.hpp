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

using namespace std;

string padMessage(const string& message, int rows, int cols);
string encrypt(const string& message, int rows, int cols);
string decrypt(const string& cipherText, int rows, int cols);
void SimpleTable();
int main();




#endif /* encryption_hpp */

