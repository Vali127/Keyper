#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>
#include <vector>

class FileManagement
{
    public:
        FileManagement();
        void AddNewEntry( std::string group , std::string user, std::string password );
        void DisplayEntry( std::string data, std::vector<std::string>& label );
        void XorEncryption();
        void FileTextToBinary();
        void FileBinaryToText();
        void EncryptSecretFile();
        void DecryptSecretFile();   

        static void Setting();
        static void DisplayInfo();
        static void CreateDirectoryAndFile( std::string dirname, std::string filename );
        static void SetDirOnConfigFile(std::string new_dir);
        static void SetFileOnConfigFile(std::string new_file);
        static std::string GetDirOnConfigFile();
        static std::string GetFileOnConfigFile();

        static std::string homePath;
        static std::string directoryPath;
        static std::string filePath;
};

#endif