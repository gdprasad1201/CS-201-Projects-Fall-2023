// Sample program that reads a "/" delimited file and a query file and 
// prints the parsed concents to stdout
// To Compile: g++ -std=c++20 HW3Sample.cpp
// To Run: ./a.out dbfile1.txt query.txt

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char *argv[]) {
	int i = 0;
	// check for correct command-line arguments
	if (argc != 3) {
	   cout << "Usage: " << argv[0] << " <db file> <query file>" << endl;
	   exit(-1);
	}

	string line, name;
	regex delim("/");
	ifstream dbfile(argv[1]);
	
	if (!dbfile.is_open()) {
	   cout << "Unable to open file: " << argv[1] << endl;
	   exit(-1);
	}

	cout << "***Reading db file " << argv[1] << "***" << endl;
	while (getline(dbfile, line)) {
	   // parse each line for tokens delimited by "/"
	   auto begin = sregex_token_iterator(line.begin(), line.end(), delim, -1);
	   auto end = sregex_token_iterator();
	   cout << "***Line " << ++i << " ***" << endl;
	   cout << "Movie:\t" << *begin << endl;
	   ++begin;
	   cout << "Actors: " << endl;
	   for (sregex_token_iterator word = begin; word != end; ++word) {
		cout << "\t" << *word << endl;
	   }
	}
	dbfile.close();
	cout << "***Done reading db file " << argv[1] << "***" << endl;

	ifstream queryfile(argv[2]);
	if (!queryfile.is_open()) {
	   cout << "Unable to open file: " << argv[2] << endl;
	   exit(-1);
	}

	cout << "***Reading query file " << argv[2] << "***" << endl;
	while (getline(queryfile, name)) {
	   cout << name << endl;
	}
	queryfile.close();
	cout << "***Done reading query file " << argv[2] << "***" << endl;

	return 0;
}

