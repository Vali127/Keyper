#include <iostream>
#include <map>
#include "includes/FileManagement.h"

int main ( int argc, char* argv[] )
{
    FileManagement instance(".hidden", ".mysecret");

    std::string groupname;
    std::string username;
    std::string password;
    
    std::map<std::string, std::string*> data =
    {
        {"group", &groupname},
        {"user", &username},
        {"key", &password}
    };
   

    std::string mode = argv[1];
    if( mode == "add")
    {
        for ( int i = 0; i < argc ; i++ )
        {
            std::string argument = argv[i];
            if(data.count(argument))
                *data[argument] = argv[++i];
        }
        instance.AddNewENtry(groupname, username, password);
    }
    

    return 1;
}