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
    private:

    protected:
        std::string linuxHomePath;
        std::string directoryPath;
        std::string filePath;
};

#endif