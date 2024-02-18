// Sample program to read and split text delimited by whitespace
// Uses C++ regular expression library function sregex_token_iterator
// For more details see:
// https://en.cppreference.com/w/cpp/regex/regex_token_iterator/regex_token_iterator
// https://docs.microsoft.com/en-us/cpp/standard-library/regular-expressions-cpp
// 
// To compile: g++ -std=c++20 parsetext.cpp
// To run: ./a.out < input.txt
// NOTE: This program reads input from the keyboard and the example shows
//       how to use I/O redirection to read from the file. In your homework, 
//       you MUST read the file name as a command-line argument and then 
//       read the contents of that file.

#include <iostream>
#include <vector>
#include <regex>
#include <fstream>

using namespace std;

int main (int argc, char** argv) {
   ifstream file(argv[1]);
   string text;
   vector<string> tokens;
   const regex delim("\\s+"); 

   while (file >> text) {
      auto begin = sregex_token_iterator(text.begin(), text.end(), delim, -1);
      auto end = sregex_token_iterator();
      for (sregex_token_iterator word = begin; word != end; word++) {
         tokens.push_back(*word);
      }
   }

   for(const auto& str : tokens)
      cout << str << endl;

   return 0;
}
