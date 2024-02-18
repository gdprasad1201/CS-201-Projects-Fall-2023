/*  
    Name: Gowtham Prasad 
    Email: gdprasad@crimson.ua.edu 
    Course Section: Fall 2023 CS 201  
    Homework #: 3
    Instructions to compile: g++ -std=c++20 hw3.cpp
    Instructions to run: ./a.exe <database file> <query file>
*/  

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <regex>
#include <chrono>

using namespace std;

int main (int argc, char** argv) {
    string line;
    unordered_map<string, vector<string>> actorMap, movieMap; // Maps actors to movies and movies to actors
    ifstream databaseFile(argv[1]), queryFile(argv[2]);
    regex delim("/");

    // Check for correct number of arguments
    if (argc != 3) {
        cout << "Usage: ./a.exe <database file> <query file>" << endl;
        exit(1);
    }

    // Check if files can be opened
    if (!databaseFile.is_open() && !queryFile.is_open()) {
        cout << "Unable to open files: " << "\"" << argv[1] << "\" and \"" << argv[2] << "\"" << endl;
        exit(1);
    }
    else if (!databaseFile.is_open()) {
        cout << "Unable to open file: \"" << argv[1] << "\"" << endl;
        exit(1);   
    }
    else if (!queryFile.is_open()) {
        cout << "Unable to open file: \"" << argv[2] << "\"" << endl;
        exit(1);   
    }
    
    chrono::time_point<chrono::steady_clock> constructBegin = chrono::steady_clock::now(); // Start timer
    while (getline(databaseFile, line)) { // Construct data structure from database file
        auto begin = sregex_token_iterator(line.begin(), line.end(), delim, -1);
        auto end = sregex_token_iterator();
        string name = *(begin++);
        for (auto text = begin; text != end; text++) { // Add movie to movieMap
            movieMap[name].push_back(*text);
        }
        for (vector<string>::iterator actor = movieMap[name].begin(); actor != movieMap[name].end(); actor++) { // Add actor to actorMap
            actorMap[*actor].push_back(name);
        }
    }
    chrono::time_point<chrono::steady_clock> constructEnd = chrono::steady_clock::now(); // End timer

    ofstream outFile(string(argv[1]).substr(0, string(argv[1]).find(".")) + "_output.txt"); // Create output file
    chrono::time_point<chrono::steady_clock> printBegin = chrono::steady_clock::now(); // Start timer
    while (getline(queryFile, line)) { // Read query file and search data structure
        if (actorMap.find(line) != actorMap.end()) { // Check if actor exists in actorMap
            outFile << "Movies starring " << line << ":" << endl;
            for (vector<string>::iterator movie = actorMap[line].begin(); movie != actorMap[line].end(); movie++) {
                outFile << "\t" << *movie << endl;
            }
            outFile << endl;
        } 
        else if (movieMap.find(line) != movieMap.end()) { // Check if movie exists in movieMap
            outFile << "Actors starring in " << line << ":" << endl;
            for (vector<string>::iterator actor = movieMap[line].begin(); actor != movieMap[line].end(); actor++) {
                outFile << "\t" << *actor << endl;
            }
            outFile << endl;
        } 
        else { // Actor or movie not found
            cout << line << " Not Found" << endl;
        }
    }
    chrono::time_point<chrono::steady_clock> printEnd = chrono::steady_clock::now(); // End timer

    chrono::duration<double> constructionTime = constructEnd - constructBegin, printTime = printEnd - printBegin; // Calculate time taken
    
    cout << endl << "Time to construct data structure: " << constructionTime.count() << " seconds" << endl;
    cout << "Time to search data structure: " << printTime.count() << " seconds" << endl;
    cout << "Total time: " << constructionTime.count() + printTime.count() << " seconds" << endl << endl;
    
    line.clear();
    actorMap.clear();
    movieMap.clear();
    databaseFile.close();
    queryFile.close();
    outFile.close();
    return 0;
}