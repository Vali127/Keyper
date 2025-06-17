#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>

class FileManagement
{
    public:
        FileManagement( std::string directory, std::string filename );
        void AddNewENtry( std::string group , std::string user, std::string password );
    private:

    protected:
        std::string linuxHomePath;
        std::string directoryPath;
        std::string filePath;
};

#endif