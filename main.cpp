#include <iostream>
#include <map>
#include "includes/FileManagement.h"
#include "includes/Utils.h"

int main ( int argc, char* argv[] )
{
    FileManagement keyFileManager(".hidden", ".mysecret");

    std::string groupname, username, password;
    
    std::map<std::string, std::string*> data =
    {
        {"group", &groupname},
        {"user", &username},
        {"key", &password}
    };

    std::vector<std::string > dataLabel = { "GROUP", "USERNAME", "KEY" };
    
    std::string mode = argv[1];

    if( mode == "add")
    {
        
        if(!ValidNumberOfArgument(argc, mode))
        {
            ExitMessage(mode);
            exit(0);
        }

        for ( int i = 0; i < argc ; i++ )
        {
            std::string argument = argv[i];
            if(data.count(argument))
                *data[argument] = argv[++i];
        }
        keyFileManager.AddNewEntry(groupname, username, password);
    }
    else if( mode == "get" )
    {
        if(!ValidNumberOfArgument(argc, mode))
        {
            ExitMessage(mode);
            exit(0);
        }

        for( int i = 0; i < argc ; i++ )
        {
            std::string argument = argv[i];
            if(data.count(argument))
            {
                *data[argument] = argv[++i];
                keyFileManager.GetEntry(*data[argument], dataLabel );
            }
        }
    }
    
    return 1;
}