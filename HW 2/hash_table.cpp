#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <cmath>

using namespace std;

unsigned long djb2(string str) {
  const char *ptr = str.c_str();
  unsigned long hash = 5381;
  int c;
  while ((c = *ptr++)) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash;
}

class HashTable {
private:
  int a, wordCount = 0, insertCollisionCount = 0, uniqueWordCount = 0, searchCollisionCount;
  string collisionResolution;
  vector<pair<string, vector<int>>> hashTable;

  int hash1(string strKey) { return djb2(strKey) % hashTable.size(); }

  int hash2(string strKey) { return a - (djb2(strKey) % a); }

  int getTotalWords() { return wordCount; }

  int getInsertCollisionCount() { return insertCollisionCount; }

  int getSearchCollisionCount() { return searchCollisionCount; }
  
  int search(string strKey);
  
  void insert(string strKey, int lineNumber);

  int getUniqueWordCount() {
    for (int i = 0; i < hashTable.size(); i++) {
      if (hashTable.at(i).first.compare("") != 0) {
        uniqueWordCount++;
      }
    }
    return uniqueWordCount;
  }

  void UpperToLower(string word, int lineNumber) {
    if (word.compare("") != 0) {
      for (int i = 0; i < word.size(); i++) {
        word.at(i) = tolower(word.at(i));
      }
      insert(word, lineNumber);
    } 
    else if (word.compare("") == 0) {
      return;
    }
  }

  int getCollisionResolution(string strKey, int j) {
    if (collisionResolution.compare("lp") == 0) {
      return (hash1(strKey) + j) % hashTable.size();
    } 
    else if (collisionResolution.compare("qp") == 0) {
      return (hash1(strKey) + (int)pow(j + 0.0, 2.0)) % hashTable.size();
    } 
    else if (collisionResolution.compare("dh") == 0) {
      return (hash1(strKey) + j * hash2(strKey)) % hashTable.size();
    }
  }

public:
  HashTable(int size, int a, string collisionResolution) {
    this->collisionResolution = collisionResolution;
    this->a = a;
    hashTable.resize(size);
  }

  void readText(string textF);

  void printResult(string queryF, ostream &os);
};

void HashTable::readText(string textF) {
  string line, word;
  ifstream textFile(textF);
  int lineNumber = 1;
  while (getline(textFile, line)) {
    for (int i = 0; i < line.size(); i++) {
      if (isalpha(line.at(i))) {
        word.push_back(line.at(i));
      } 
      else if (!isalpha(line.at(i))) {
        UpperToLower(word, lineNumber);
        word.clear();
      }
    }
    UpperToLower(word, lineNumber++);
    word.clear();
  }
  textFile.close();
}

void HashTable::printResult(string queryF, ostream &os) {
  ifstream queryFile(queryF);
  string queryWord;
  vector<string> queryWordArray;
  os << "The number of words found in the file was " << getTotalWords() << endl;
  os << "The number of unique words found in the file was " << getUniqueWordCount() << endl;
  os << "The number of collisions was " << getInsertCollisionCount() << endl << endl;
  while (queryFile >> queryWord) {
    queryWordArray.push_back(queryWord);
  }
  for (int i = 0; i < queryWordArray.size(); i++) {
    int searchIndex = search(queryWordArray.at(i));
    os << queryWordArray.at(i) << " appears on lines [";
    for (int j = 0; j < hashTable.at(searchIndex).second.size(); j++) {
      if (!j) {
        os << hashTable.at(searchIndex).second.at(j);
      } 
      else {
        os << "," << hashTable.at(searchIndex).second.at(j);
      }
    }
    os << "]" << endl;
    if (i < queryWordArray.size() - 1) {
      os << "The search had " << getSearchCollisionCount() << " collisions" << endl << endl;
    } 
    else {
      os << "The search had " << getSearchCollisionCount() << " collisions" << endl;
    }
  }
  queryFile.close();
}

void HashTable::insert(string strKey, int lineNumber) {
  int hashIndex = hash1(strKey);
  if (hashTable.at(hashIndex).first.compare("") != 0 && hashTable.at(hashIndex).first.compare(strKey) != 0) {
    int j = 0;
    for (int i = 0; i < hashTable.size(); i++) {
      if (hashTable.at(hashIndex).first.compare("") != 0 && hashTable.at(hashIndex).first.compare(strKey) != 0) {
        insertCollisionCount++;
        j++;
        hashIndex = getCollisionResolution(strKey, j);
      } 
      else if (hashTable.at(hashIndex).first.compare("") == 0) {
        hashTable.at(hashIndex).first = strKey;
        hashTable.at(hashIndex).second.push_back(lineNumber);
        break;
      } 
      else if (hashTable.at(hashIndex).first.compare(strKey) == 0) {
        hashTable.at(hashIndex).second.push_back(lineNumber);
        break;
      }
    }
  } 
  else if (hashTable.at(hashIndex).first.compare("") == 0) {
    hashTable.at(hashIndex).first = strKey;
    hashTable.at(hashIndex).second.push_back(lineNumber);
  } 
  else if (hashTable.at(hashIndex).first.compare(strKey) == 0) {
    hashTable.at(hashIndex).second.push_back(lineNumber);
  }
  wordCount++;
}

int HashTable::search(string strKey) {
  int hashIndex = hash1(strKey), j = 0;
  searchCollisionCount = 0;
  for (int i = 0; i < hashTable.size(); i++) {
    if (hashTable.at(hashIndex).first.compare("") != 0 && hashTable.at(hashIndex).first.compare(strKey) != 0) {
      searchCollisionCount++;
      j++;
      hashIndex = getCollisionResolution(strKey, j);
    } 
    else {
      return hashIndex;
    }
  }
}

int main(int argc, char **argv) {
  int a = 0;
  string collisionResolution = argv[4];

  if (collisionResolution.compare("dh") == 0) a = stoi(argv[5]);

  HashTable ht(stoi(argv[3]), a, collisionResolution);

  ht.readText(argv[1]);
  ht.printResult(argv[2], cout);

  return 0;
}