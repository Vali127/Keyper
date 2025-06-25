#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
#include <map>

 std::vector<std::string> split( std::string text, char delimiter );
 bool ValidNumberOfArgument(int n, std::string mode);
 std::string BinaryToString(std::string data);
 void ExitMessage( std::string mode );
 bool ValidArguments( char* argv[], int argc);
 void About();
 void HelpMessage();
 void Usage();

#endif