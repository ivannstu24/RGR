//
//  tarabarska.hpp
//  RGR_DEV
//
//  Created by Иван Мерзов on 30.05.2024.
//

#ifndef tarabarska_hpp
#define tarabarska_hpp

#include <stdio.h>

#include <string>
#include <unordered_map>

using namespace std;

unordered_map<char, char> createTarabarskaMap();
void Tarabara();
int main();

string tarabarskaCipher(const string& text, const unordered_map<char, char>& tarabarska_map);


#endif /* tarabarska_hpp */


