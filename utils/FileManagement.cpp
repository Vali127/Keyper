#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include "../includes/FileManagement.h"
#include "../includes/Utils.h"

namespace fs = std::filesystem;

/*Attribute*/
std::string FileManagement::homePath = std::string(std::getenv("HOME"));
std::string FileManagement::directoryPath = GetDirOnConfigFile();
std::string FileManagement::filePath = GetFileOnConfigFile();




FileManagement::FileManagement()
{
    if(directoryPath == "null")
    {
        About();
        Setting();
    }
}

void FileManagement::Setting()
{
    std::cout << std::left << " \033[1m" << "CONFIGURATION :" << "\033[0m"<< std::endl;
    std::string set_dir;
    std::string set_file;
    std::cout << " Enter path to the directory (path from user directory ex: Mydir and it will be on ~/Mydir ) : ";
    std::getline(std::cin, set_dir);
    std::cout << " Enter filename : ";
    std::getline(std::cin, set_file);
    CreateDirectoryAndFile(set_dir, set_file);
    SetDirOnConfigFile(set_dir);
    SetFileOnConfigFile(set_file);
}

void FileManagement::CreateDirectoryAndFile( std::string dirname, std::string filename )
{
    directoryPath = homePath + "/" + dirname;
    std::string file_path = directoryPath + "/" + filename + ".txt";
    fs::path dir = fs::path(directoryPath);

    std::cout << "\n" << "\033[1m" << "RESULT :" << "\033[0m" << std::endl;
    if(fs::create_directories(dir))
    {
        std::cout << "Directory Created !!" << std::endl;
        std::ofstream file;

        file.open(file_path, std::ios::out);
        if(file.is_open())
        {
            std::cout << "File Created !!" << std::endl;
            file.close();
        }
         else
        {
            std::cout << "Something went wrong, couldn't create file !!" << std::endl;
        }
    }
    else
    {
        std::cout << "Something went wrong, couldn't create directory !!" << std::endl;
    }

}

void FileManagement::AddNewEntry( std::string group , std::string user, std::string password )
{
     std::ofstream secretFile;
     secretFile.open(filePath, std::ios::out | std::ios::app );
     if(secretFile.is_open())
     {
        std::string entry = group + ':' + user + ':' + password;
        secretFile << entry;
        secretFile << "\n";
        secretFile.close();
        std::cout << "RESULT : Entry added successfully at : '" << filePath << "' !! " << std::endl;
     }
     else
     {
        std::cout << "ERROR : Couldnèt add a new entry!!" << std::endl;
     }
}

void FileManagement::GetEntry( std::string data , std::vector<std::string>& label )
{
    std::string line;
    std::ifstream secretFile;
    secretFile.open(FileManagement::filePath, std::ios::in );
    if(secretFile.is_open())
    {
        while( std::getline(secretFile, line) )
        {
            if( line.find(data) != std::string::npos )
            {
                std::vector<std::string> values = split( line, ':');
                std::cout << "" << std::endl;
                for( int i = 0; i < (int)values.size() ; ++i  )
                {
                    std::cout << std::left << " \033[1m" << std::setw(10) << label[i] << "\033[0m" << std::left << std::setw(2) << ": " << values[i] << std::endl;
                }
            }
        }
        secretFile.close();
    }
}   

    /*For the config File*/
    

std::string FileManagement::GetDirOnConfigFile()
{
    std::vector<std::string> tmp;
    std::string line;

    std::ifstream config_file;
    config_file.open("keyper.conf", std::ios::in);
    if(config_file.is_open())
    {
        
        while(std::getline(config_file, line))
        {
            if(line.find("DIR") != std::string::npos)
            {
                tmp = split(line, '=');
                config_file.close();
                return tmp[1];
            }
            config_file.close();
            return "null";
        }
                
    }
    return "null";
    
}

std::string FileManagement::GetFileOnConfigFile()
{
    std::vector<std::string> tmp;
    std::string line;
        
    std::ifstream config_file;
    config_file.open("keyper.conf", std::ios::in);
    if(config_file.is_open())
    {
        while(std::getline(config_file, line))
            if(line.find("FILE") != std::string::npos)
                tmp = split(line, '=');

        config_file.close();
        return tmp[1];
    }
    return "null";
    
}

void FileManagement::SetDirOnConfigFile(std::string new_dir)
{
    
    std::string entry = "DIR=" + homePath + "/" + new_dir;
    
    std::ofstream config_file;
    config_file.open("keyper.conf", std::ios::out);
    if(config_file.is_open())
    {
        config_file << entry;
        config_file.close();
    }
    else
    {
        std::cout << "ERROR : can 't open config file" << std::endl;
    }
}

void FileManagement::SetFileOnConfigFile(std::string new_file)
{
    std::string dir_path = GetDirOnConfigFile();
    std::string entry = "FILE=" + dir_path + "/" + new_file + ".txt";
    std::ofstream config_file;
    config_file.open("keyper.conf", std::ios::app);
    if(config_file.is_open())
    {
        config_file << "\n";
        config_file << entry;
        config_file.close();
    }
    else
    {
        std::cout << "ERROR : Can' t open config file" << std::endl;
    }
}
