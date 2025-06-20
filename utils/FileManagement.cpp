#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include "../includes/FileManagement.h"
#include "../includes/Utils.h"

namespace fs = std::filesystem;

FileManagement::FileManagement( std::string directory, std::string filename )
{
    linuxHomePath = std::getenv("HOME");
    directoryPath = linuxHomePath + "/" + directory;
    filePath = directoryPath + "/" + filename + ".txt";
    
    fs::path dir = fs::path(directoryPath);
    if( !fs::exists(dir) )
        fs::create_directories(dir);

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