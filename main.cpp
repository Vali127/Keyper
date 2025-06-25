#include <iostream>
#include <map>
#include "headers/FileManagement.h"
#include "headers/Utils.h"

int main ( int argc, char* argv[] )
{
    FileManagement keyFileManager;
    std::string groupname, username, password;
    std::map<std::string, std::string*> data =
    {
        {"group", &groupname},
        {"user", &username},
        {"key", &password}
    };
    std::vector<std::string > dataLabel = { "GROUP", "USERNAME", "KEY" };
    
    if( argc == 1 )
    {
        About();
        HelpMessage();
        exit(0);
    }

    std::string mode = argv[1];
    if( mode == "add")
    {
        if(!ValidNumberOfArgument(argc, mode) || !ValidArguments( argv, argc ))
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
        if(!ValidNumberOfArgument(argc, mode) || !ValidArguments( argv, argc))
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
                keyFileManager.DisplayEntry(*data[argument], dataLabel );
            }
        }
    }
    
    else if( mode == "set-up" )
    {
        FileManagement::Setting();
    }
    
    else if( mode == "help" )
    {
        Usage();
    }
    
    return 1;
}