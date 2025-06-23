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
    std::cout << "All arguments are required and please check the syntax" << std::endl;
    if( mode == "get" )
        std::cout << "USAGE : get [ [group <groupname>] | [user <username>] | [key <key>] ] " << std::endl;
    else if( mode == "add" )
        std::cout << "USAGE : add group <groupname> user <username> key <key> " << std::endl;
}

bool ValidArguments( char* argv[], int argc)
{
    std::vector<std::string> arg_values;
    for( int i = 0; i < argc; i++ )
    {
        std::string tmp = argv[i];
        arg_values.push_back(tmp);
    }

    std::vector<std::string> valid_arguments = { "group", "user", "key" };
    std::vector<bool> validation;
    int j = 0;
    for( int i = 2; i < argc;)
    {
        bool tmp;
        for( const auto& arg : valid_arguments )
        {
            if( arg_values[i] == arg )
            {
                tmp = true;
                break;
            }
            tmp = false;
        }
        validation.push_back(tmp);
        i += 2;
        j++;
    }
    for( const auto& item : validation )
    {
        if( !item )
            return false; 
    }
    return true;
}