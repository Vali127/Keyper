#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../includes/Utils.h"

std::vector<std::string> split( std::string text, char delimiter )
{
    std::vector<std::string> token;
    std::stringstream textline(text);
    std::string item;
    while (std::getline(textline, item, delimiter)) {
        token.push_back(item);
    }
    return token;

}