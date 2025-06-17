#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include "../includes/FileManagement.h"

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

void FileManagement::AddNewENtry( std::string group , std::string user, std::string password )
{
     std::ofstream secretFile;
     secretFile.open(filePath, std::ios::out | std::ios::app );
     std::string entry = group + ':' + user + ':' + password;
     secretFile << entry;
     secretFile << "\n";
     secretFile.close();
     std::cout << "RESULT : Entry added successfully at : '" << filePath << "' !! " << std::endl;
}