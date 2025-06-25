#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
#include <map>

 std::vector<std::string> split( std::string text, char delimiter );
 bool ValidNumberOfArgument(int n, std::string mode);
 bool ValidArguments( char* argv[], int argc);
 std::string BinaryToString(std::string data); 
 void About();
 void Usage();
 void HelpMessage();
 void ExitMessage( std::string mode );

#endif