#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include "../includes/FileManagement.h"
#include "../includes/Utils.h"

namespace fs = std::filesystem;

FileManagement::FileManagement()
{    
    if( directoryPath == "Empty" )
        std::cout << "Please type : 'keyper set-up' to set things up !" << std::endl;
}

static void FileManagement::Setting()
{
    std::cout << std::left << " \033[1m" << "CONFIGURATION :" << "\033[0m"<< std::endl;
    std::string set_dir;
    std::string set_file;
    std::cout << " Enter path to the directory (path from user directory ex: Mydir and it will be on ~/Mydir ) : ";
    getline(std::in, set_dir);
    std::cout << " Enter filename : ";
    getline(std::in, set_file);
    CreateDirectoryAndFile( set_dir, set_file );
}

static void FileManagement::CreateDirectoryAndFile( std::string dirname, std::string filename )
{
    linuxHomePath = std::getenv("HOME");
    directoryPath = linuxHomePath + "/" + dirname;
    filePath = directoryPath + "/" + filename + ".txt";

    fs::path dir = fs::path(directoryPath);

    if(fs::create_directories(dir))
    {
        std::cout << "Directory Created !!" << std::endl;
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
     std::string entry = group + ':' + user + ':' + password;
     secretFile << entry;
     secretFile << "\n";
     secretFile.close();
     std::cout << "RESULT : Entry added successfully at : '" << filePath << "' !! " << std::endl;
}

void FileManagement::GetEntry( std::string data , std::vector<std::string>& label )
{
    std::string line;
    std::ifstream secretFile;
    secretFile.open(filePath, std::ios::in );
    while( std::getline(secretFile, line) )
    {
        if( line.find(data) != std::string::npos )
        {
            std::vector<std::string> values = split( line, ':');
            std::cout << "" << std::endl;
            std::cout << "Corresponding Information written on the current file" << std::endl;
            std::cout << "" << std::endl;
            for( int i = 0; i < (int)values.size() ; ++i  )
            {
                std::cout << std::left << " \033[1m" << std::setw(10) << label[i] << "\033[0m" << std::left << std::setw(2) << ": " << values[i] << std::endl;
            }
        }
    }

}