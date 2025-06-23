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

bool ValidNumberOfArgument( int n, std::string mode)
{
    if( mode == "add" )
        return (n == 8);
    else if( mode == "get" )
        return (n == 4);
    return false;
}

void ExitMessage( std::string mode )
{
    std::cout << "All arguments are requuired" << std::endl;
    if( mode == "get" )
        std::cout << "USAGE : get [ [group <groupname>] | [user <username>] | [key <key>] ] " << std::endl;
    else if( mode == "add" )
        std::cout << "USAGE : add group <groupname> user <username> key <key> " << std::endl;
}