#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <bitset>
#include <filesystem>
#include <fstream>
#include <vector>
#include "../headers/FileManagement.h"
#include "../headers/Utils.h"

namespace fs = std::filesystem;
 
std::string FileManagement::homePath = std::string(std::getenv("HOME"));
std::string FileManagement::directoryPath = GetDirOnConfigFile();
std::string FileManagement::filePath = GetFileOnConfigFile();
 
FileManagement::FileManagement()
{
    if(directoryPath == "null")
    {
        About();
        Setting();
        EncryptSecretFile();
        exit(0);
    }
}

void FileManagement::EncryptSecretFile()
{
    XorEncryption();
    FileTextToBinary();
}
void FileManagement::DecryptSecretFile()
{
    FileBinaryToText();
    XorEncryption();
}

void FileManagement::XorEncryption()
{
    std::fstream secretFile;
    secretFile.open(filePath, std::ios::out | std::ios::in | std::ios::binary);
    if(!secretFile.is_open())
    {
        std::cerr << "ERROR : can 't access " << filePath << std::endl;
        return;
    }
    char chr;
    int key = 0x45;
    while(secretFile.get(chr))
    {
        secretFile.seekp(-1, std::ios::cur);
        secretFile.put(chr ^ key);
        secretFile.flush();
    }
    secretFile.close();
}

void FileManagement::FileTextToBinary()
{
    std::fstream secretFile;
    secretFile.open(filePath,std::ios::in | std::ios::binary);
    if(!secretFile.is_open())
    {
        std::cerr << "ERROR : can 't access " << filePath << std::endl;        
        return;
    }
    std::string binary_value;
    char chr;    
    while(secretFile.get(chr))
        binary_value += std::bitset<8>(static_cast<unsigned char>(chr)).to_string();
    secretFile.close();

    secretFile.open(filePath,std::ios::out | std::ios::trunc);
    if(!secretFile.is_open())
    {
        std::cerr << "ERROR : can 't access " << filePath << std::endl;
        return;
    }
    secretFile << binary_value;
    secretFile.close();
}

void FileManagement::FileBinaryToText()
{
    std::fstream secretFile;
    secretFile.open(filePath, std::ios::in | std::ios::binary );
    if(!secretFile.is_open())
    {
        std::cerr << "ERROR : can 't access " << filePath << std::endl;
        return;
    }
    std::string binary_value;
    std::string line;
    while(std::getline(secretFile, line))
        binary_value += line;
    secretFile.close();
    std::string text_value = BinaryToString(binary_value);

    secretFile.open(filePath, std::ios::out | std::ios::trunc);
    if(!secretFile.is_open())
    {
        std::cerr << "ERROR : can 't access " << filePath << std::endl;
        return;
    }
    secretFile << text_value;
    secretFile.close();
}

void FileManagement::Setting()
{
    std::string set_dir;
    std::string set_file;

    std::cout << std::left << " \033[1m" << "CONFIGURATION :" << "\033[0m" << std::endl;
    std::cout << " Enter path to the directory (path from user directory ex: Mydir and it will be on ~/Mydir ) : ";
    std::getline(std::cin, set_dir);
    std::cout << " Enter filename : ";
    std::getline(std::cin, set_file);

    CreateDirectoryAndFile(set_dir, set_file);
    SetDirOnConfigFile(set_dir);
    SetFileOnConfigFile(set_file);
    directoryPath = GetDirOnConfigFile();
    filePath = GetFileOnConfigFile();
}

void FileManagement::CreateDirectoryAndFile( std::string dirname, std::string filename )
{
    std::string directory_path = homePath + "/" + dirname;
    std::string file_path = directory_path + "/" + filename + ".txt";
    fs::path dir = fs::path(directory_path);

    std::cout << "\n" << "\033[1m" << "RESULT :" << "\033[0m" << std::endl;
    
    if(fs::exists(dir) && fs::is_directory(dir))
    {
        std::cout << "The Directory already exists !!" << std::endl;
    }
    else if(fs::create_directories(dir))
    {
        std::cout << "Directory Created !!" << std::endl;
    }
    else
    {
        std::cerr << "Something went wrong, couldn't create directory !!" << std::endl;
        return;
    }
    std::ofstream file;
    file.open(file_path, std::ios::out);
    if(file.is_open())
    {
        std::cout << "File Created !!" << std::endl;
        file.close();
    }
    else
    {
        std::cerr << "Something went wrong, couldn't create file !!" << std::endl;
    }
}
 
std::string FileManagement::GetDirOnConfigFile()
{
    std::vector<std::string> tmp;
    std::string line;

    std::ifstream config_file;
    config_file.open("keyper.conf", std::ios::in);
    if(!config_file.is_open())
        return "null";
    while(std::getline(config_file, line))
    {
        if(line.find("DIR") != std::string::npos)
        {
            tmp = split(line, '=');
            config_file.close();
            return tmp[1];
        }
        config_file.close();
    }
    return "null";
}

std::string FileManagement::GetFileOnConfigFile()
{    
    std::ifstream config_file;
    config_file.open("keyper.conf", std::ios::in);
    if(!config_file.is_open())
        return "null";

    std::vector<std::string> tmp;
    std::string line;
    while(std::getline(config_file, line))
    if(line.find("FILE") != std::string::npos)
        tmp = split(line, '=');
    config_file.close();
    return tmp[1];
    
}

void FileManagement::SetDirOnConfigFile(std::string new_dir)
{ 
    std::ofstream config_file;
    config_file.open("keyper.conf", std::ios::out);
    if(!config_file.is_open())
    {
        std::cerr << "ERROR : can 't open config file" << std::endl;
        return;
    }
    std::string entry = "DIR=" + homePath + "/" + new_dir;
    config_file << entry;
    config_file.close();
}

void FileManagement::SetFileOnConfigFile(std::string new_file)
{ 
    std::ofstream config_file;
    config_file.open("keyper.conf", std::ios::app);
    if(!config_file.is_open())
    {
        std::cerr << "ERROR : Can' t open config file" << std::endl;
        return;
    }
    std::string dir_path = GetDirOnConfigFile();
    std::string entry = "FILE=" + dir_path + "/" + new_file + ".txt";
    config_file << "\n";
    config_file << entry;
    config_file.close();
} 

void FileManagement::AddNewEntry( std::string group , std::string user, std::string password )
{
    DecryptSecretFile();
    
    std::ofstream secretFile;
    secretFile.open(filePath, std::ios::out | std::ios::app );
    if(!secretFile.is_open())
    {
        std::cerr << "ERROR : Couldn' t open " << filePath << "!!" << std::endl;
        return;
    }
    std::string entry = group + ':' + user + ':' + password;
    secretFile << entry;
    secretFile << "\n";
    secretFile.close();
    std::cout << "RESULT : Entry added successfully at : '" << filePath << "' !! " << std::endl;

    EncryptSecretFile();
}

void FileManagement::DisplayEntry( std::string data , std::vector<std::string>& label )
{
    DecryptSecretFile();

    std::string line;
    std::ifstream secretFile;
    secretFile.open(FileManagement::filePath, std::ios::in );
    if(!secretFile.is_open())
    {
        std::cerr << "ERROR : Couldn 't open" << filePath << " !!" << std::endl;
        return;
    }
    while( std::getline(secretFile, line) )
    {
        if( line.find(data) != std::string::npos )
        {
            std::vector<std::string> values = split( line, ':');
            std::cout << "" << std::endl;
            for( int i = 0; i < (int)values.size() ; ++i  )
                std::cout << std::left << " \033[1m" << std::setw(10) << label[i] << "\033[0m" << std::left << std::setw(2) << ": " << values[i] << std::endl;
        }
    }
    secretFile.close();

    EncryptSecretFile();
}