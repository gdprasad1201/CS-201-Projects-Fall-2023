/*
  Name: Gowtham Prasad
  Email: gdprasad@crimson.ua.edu
  Course Section: Fall 2023 CS 201-001
  Homework#: 0
  Instructions to Compile: g++ hw0.cpp
  Instructions to Execute: ./a.exe <file name>
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;

class Movie {
public: 
  string movieName;
  int year;
  vector<string> actors;

  Movie(string movieName, int year, vector<string> actors) {
    this->movieName = movieName;
    this->year = year;
    this->actors = actors;
  }
};

bool nameCompare(const Movie& movie1, const Movie& movie2) { //adapted from https://stackoverflow.com/questions/12823573/c-sorting-class-array
  if (movie1.movieName.compare(movie2.movieName) == 0) {
    return movie1.year < movie2.year;
  }
  else {
    return movie1.movieName < movie2.movieName;
  }
}

bool yearCompare(const Movie& movie1, const Movie& movie2) { //adapted from https://stackoverflow.com/questions/12823573/c-sorting-class-array
  if (movie1.year == movie2.year) {
    return movie1.movieName < movie2.movieName;
  }
  else {
    return movie1.year < movie2.year;
  } 
}

int main(int argc, char** argv) {
  vector<Movie> movies; // vector of class Movie
  string line, fileName = argv[1];
  ifstream textFile(fileName);
  ofstream outFileAlpha(fileName.substr(0, fileName.find_first_of(".")) + "ByName.txt"); //creates file for sorted movies by title
  ofstream outFileYear(fileName.substr(0, fileName.find_first_of(".")) + "ByYear.txt"); //creates file for sorted movies by release year
  
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <text file>" << endl;
    return 0;
  }

  if (!textFile.is_open()) {
    cout << "Error: Unable to open input file: " << fileName << endl;
    return 0;
  }
  
  auto startCollectionClock = chrono::system_clock::now(); // timer starts for making the collection 
  while (getline(textFile, line)) {
    vector<string> actors;
    string movieName = line.substr(0, line.find_first_of("(")); //finds first instance of starting parantheses to get movie name 
    int yearStartIndex = line.find_first_of("(") + 1; 
    int yearEndIndex = line.find_first_of(")", yearStartIndex);
    int year = stoi(line.substr(yearStartIndex, yearEndIndex - yearStartIndex)); //finds release year between starting amd ending parantheses
    int actorStartIndex = line.find_first_not_of("/", yearEndIndex + 1); // looks for the first character that is not a "/"
    while (actorStartIndex != string::npos) { // iterate from first instance of "/" to next instance of "/"
      int actorEndIndex = line.find_first_of("/", actorStartIndex); //looks for location of ending "/" after the index of actorStartIndex
      if (actorEndIndex == string::npos) {
        actorEndIndex = line.size();
      }
      actors.push_back(line.substr(actorStartIndex, actorEndIndex - actorStartIndex)); //finds actor name between "/"s and looks for the next name 
      actorStartIndex = line.find_first_not_of("/", actorEndIndex + 1); //restarts search until it reaches the end of the line
    } 
    movies.emplace_back(movieName, year, actors); // push backs movie name, release year, and vector list of actors to for each line read untile 
  }
  auto endCollectionClock = chrono::system_clock::now(); // timer stops for making the collection once while loop ends
  chrono::duration<double> timeForCollection = endCollectionClock - startCollectionClock; // find difference between start and end time

  auto startAlphaClock = chrono::system_clock::now(); // timer starts for sorting via movie title 
  sort(movies.begin(), movies.end(), nameCompare); //sorts by name using lamda function
  auto endAlphaClock = chrono::system_clock::now(); // timer ends for sorting via movie title
  chrono::duration<double> timeForAlpha = endAlphaClock - startAlphaClock;
  for (int i = 0; i < movies.size(); i++) { //prints by movie title to <file name>ByName.txt
    outFileAlpha << movies.at(i).movieName << "(" << movies.at(i).year << ")"; 
    for (int j = 0; j < movies.at(i).actors.size(); j++) {
      outFileAlpha << "/" << movies.at(i).actors.at(j);
    }
    outFileAlpha << endl;
  }

  auto startYearClock = chrono::system_clock::now(); //timer starts for sorting via year
  sort(movies.begin(), movies.end(), yearCompare); //sorts by year using lamda function
  auto endYearClock = chrono::system_clock::now(); //timer ends for sorting via year
  chrono::duration<double> timeForYear = endYearClock - startYearClock;
  for (int i = 0; i < movies.size(); i++) { //prints by movie year to <file name>ByYear.txt
    outFileYear << movies.at(i).movieName << "(" << movies.at(i).year << ")";
    for (int j = 0; j < movies.at(i).actors.size(); j++) {
      outFileYear << "/" << movies.at(i).actors.at(j);
    }
    outFileYear << endl;
  }

  cout << "Elasped time for creating the collection: " << timeForCollection.count() << " seconds" << endl;
  cout << "Elasped time for sorting the collection alphabetically: " << timeForAlpha.count() << " seconds" << endl;
  cout << "Elasped time for sorting the collection chronologically: " << timeForYear.count() << " seconds" << endl;

  textFile.close();
  outFileAlpha.close();
  outFileYear.close();
  return 0;
}