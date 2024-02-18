/*  
  Name: Gowtham Prasad
  Email: gdprasad@crimson.ua.edu
  Course Section: Fall 2023 CS 201  
  Homework #: 2
  To Compile: g++ -std=c++17 hw2.cpp 
  To Run: ./a.exe <filename>
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <chrono>

using namespace std;

class HashTable { // class to store the word and its count
  private:
    string word;
    int count;
  
  public:
    HashTable(string word, int count) {
      this->word = word; // stores the word
      this->count = count; // stores the count of the word occuring in the file
    }

    // getter function for word
    string getWord() {
      return word; 
    }

    // getter function for count
    int getCount() {
      return count;
    }

    friend bool compare(HashTable& a, HashTable& b); // friend function to compare the count of the words
};

// function to compare the count of the words
bool compare(HashTable& a, HashTable& b) {
  if (a.count == b.count) {
    return a.word < b.word;
  }
  return a.count > b.count;
}

int main(int argc, char** argv) {
  string file = argv[1], word;
  int totalCount = 0;
  unordered_map<string, int> map; // stores the word and its count in a hash table
  vector<HashTable> ht; // stores the word and its count in a vector of objects HashTable
  ifstream inputFile(file);

  // checks if the file name is given as an argument
  if (argc != 2) {
    cout << "Usage: ./a.exe <filename>" << endl;
    return 0;
  }

  // checks if the file exists
  if (!inputFile.is_open()) {
    cout << "File not found" << endl;
    return 0;
  }

  // starts time
  chrono::steady_clock::time_point start = chrono::steady_clock::now();

  // parses the file and stores the words and its count in a hash table
  while (inputFile >> word) {
    map[word]++;
    totalCount++;
  }

  // stores the words and its count in a vector of objects HashTable
  for (unordered_map<string, int>::iterator i = map.begin(); i != map.end(); i++) {
    ht.emplace_back(i->first, i->second);
  }

  // sorts the vector of objects HashTable
  sort(ht.begin(), ht.end(), compare); // uses the friend function compare to sort the vector of objects HashTable
  
  // ends time and calculates the time taken
  chrono::duration<double> timeTaken = chrono::steady_clock::now() - start;

  // writes the words and its count to the terminal and optionally a file
  // ofstream outputFile(file.substr(0, file.find_first_of(".")) + "_output.txt");
  for (vector<HashTable>::iterator i = ht.begin(); i != ht.end(); i++) {
    cout << i->getWord() << ": " << i->getCount() << endl;
  }

  cout << "Total word count for " << "\"" << file << "\": " << totalCount << " words" << endl;
  cout << "Total time taken to parse and sort the words in " << "\"" << file << "\": " << timeTaken.count() << " seconds" << endl;
  
  ht.clear();
  inputFile.close();
  // outputFile.close();

  return 0;
}