#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>
#include <vector>

class FileManagement
{
    public:
        FileManagement();
        void AddNewEntry( std::string group , std::string user, std::string password );
        void GetEntry( std::string data, std::vector<std::string>& label );
        void XorEncryption();
        void CharToBinary();
        void BinaryToChar();
        void Encrypting();
        void Decrypting();
        

        static void Setting();
        static std::string GetDirOnConfigFile();
        static std::string GetFileOnConfigFile();
        static void SetDirOnConfigFile(std::string new_dir);
        static void SetFileOnConfigFile(std::string new_file);
        static void CreateDirectoryAndFile( std::string dirname, std::string filename );

        static std::string homePath;
        static std::string directoryPath;
        static std::string filePath;

    private:
    protected:
};

#endif