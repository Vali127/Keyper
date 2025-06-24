#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>
#include <vector>

class FileManagement
{
    public:
        FileManagement( std::string directory, std::string filename );
        void AddNewEntry( std::string group , std::string user, std::string password );
        void GetEntry( std::string data, std::vector<std::string>& label );

        static void Setting();
        static void FileManagement::CreateDirectoryAndFile( std::string dirname, std::string filename );

        static std::string linuxHomePath;
        static std::string directoryPath = "Empty";
        static std::string filePath;

    private:
    protected:
};

#endif