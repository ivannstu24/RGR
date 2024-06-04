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

std::unordered_map<char, char> createTarabarskaMap();
std::string tarabarskaCipher(const std::string& text, const std::unordered_map<char, char>& tarabarska_map);


#endif /* tarabarska_hpp */


