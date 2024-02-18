/*
Name: Gowtham Prasad
Email: gdprasad@crimosn.ua.edu
Course Section: Fall 2023 CS 201
Homework #: 1
Instructions to compile the program: g++ hw1.cpp
Instructions to execute the program: ./a.exe
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>

using namespace std;

template <class RandomIt>
RandomIt partitionArray(RandomIt first, RandomIt last) {
  RandomIt pivot = first;
  RandomIt i = first;
  RandomIt j = last - 1;

  while (i < j) {
    while (*i <= *pivot && i < last) {
      i++;
    }
    while (*j > *pivot && j > first) {
      j--;
    }
    if (i < j) {
      swap(*i, *j);
    }
  }
  swap(*pivot, *j);
  return j;
}

template <class RandomIt>
constexpr void quicksort(RandomIt first, RandomIt last) {
  if (distance(first, last) <= 1) {
    return;
  }

  RandomIt pivot = partitionArray(first, last);
  quicksort(first, pivot);
  quicksort(pivot + 1, last);
}

template <class RandomIt>
constexpr void heapify(RandomIt start, RandomIt end, int i) { // Adapted from https://www.geeksforgeeks.org/heap-sort/
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < distance(start, end) && *(start + left) > *(start + largest)) {
    largest = left;
  }

  if (right < distance(start, end) && *(start + right) > *(start + largest)) {
    largest = right;
  }

  if (largest != i) {
    swap(*(start + i), *(start + largest));
    heapify(start, end, largest);
  }
}

template <class RandomIt>
constexpr void heapsort(RandomIt start, RandomIt end) {
  // Max heapify sequence
  for (int i = distance(start, end) / 2; i >= 0; i--) {
    heapify(start, end, i);
  }

  // Swapping first int with the last node and then max heapifying again
  for (int i = distance(start, end) - 1; i >= 0; i--) {
    swap(*start, *(start + i));
    heapify(start, start + i, 0);
  }
}

int main(int argc, char** argv) {
  chrono::duration<double> timetaken[3][3];
  cout << "Problem Size for std::sort\tTime Taken (seconds)" << endl;
  cout << "\t\t\t\tCase 1\t\tCase 2\t\tCase 3" << endl;
  for (int size = 10; size <= 100000000; size *= 10) {
    int *sortArray = new int[size];
    // repeat each case for three times
    for (int i = 0; i < 3; i++) {
      generate(sortArray, sortArray + size, rand);

      // Case 1: sorting random values
      auto startTime = chrono::steady_clock::now();
      sort(sortArray, sortArray + size);
      auto endTime = chrono::steady_clock::now();
      timetaken[i][0] = endTime - startTime;

      // Case 2: sorting data that is already sorted
      startTime = chrono::steady_clock::now();
      sort(sortArray, sortArray + size);
      endTime = chrono::steady_clock::now();
      timetaken[i][1] = endTime - startTime;

      // Case 3: sorting data that is in reverse sorted order
      reverse(sortArray, sortArray + size);
      startTime = chrono::steady_clock::now();
      sort(sortArray, sortArray + size);
      endTime = chrono::steady_clock::now();
      timetaken[i][2] = endTime - startTime;
    }

    cout << size << "\t\t\t\t";
    cout << (timetaken[0][0].count() + timetaken[1][0].count() + timetaken[2][0].count()) / 3.0 << "\t";
    cout << (timetaken[0][1].count() + timetaken[1][1].count() + timetaken[2][1].count()) / 3.0 << "\t";
    cout << (timetaken[0][2].count() + timetaken[1][2].count() + timetaken[2][2].count()) / 3.0 << "\t";
    cout << endl;

    delete[] sortArray;
  }
  cout << endl;

  cout << "Problem Size for Heap Sort\tTime Taken (seconds)" << endl;
  cout << "\t\t\t\tCase 1\t\tCase 2\t\tCase 3" << endl;
  for (int size = 10; size <= 100000000; size *= 10) {
    int *sortArray = new int[size];
    // repeat each case for three times
    for (int i = 0; i < 3; i++) {
      generate(sortArray, sortArray + size, rand);

      // Case 1: sorting random values
      auto startTime = chrono::steady_clock::now();
      heapsort(sortArray, sortArray + size);
      auto endTime = chrono::steady_clock::now();
      timetaken[i][0] = endTime - startTime;

      // Case 2: sorting data that is already sorted
      startTime = chrono::steady_clock::now();
      heapsort(sortArray, sortArray + size);
      endTime = chrono::steady_clock::now();
      timetaken[i][1] = endTime - startTime;

      // Case 3: sorting data that is in reverse sorted order
      reverse(sortArray, sortArray + size);
      startTime = chrono::steady_clock::now();
      heapsort(sortArray, sortArray + size);
      endTime = chrono::steady_clock::now();
      timetaken[i][2] = endTime - startTime;
    }

    cout << size << "\t\t\t\t";
    cout << (timetaken[0][0].count() + timetaken[1][0].count() + timetaken[2][0].count()) / 3.0 << "\t";
    cout << (timetaken[0][1].count() + timetaken[1][1].count() + timetaken[2][1].count()) / 3.0 << "\t";
    cout << (timetaken[0][2].count() + timetaken[1][2].count() + timetaken[2][2].count()) / 3.0 << "\t";
    cout << endl;

    delete[] sortArray;
  }
  cout << endl;

  cout << "Problem Size for Quick Sort\tTime Taken (seconds)" << endl;
  cout << "\t\t\t\tCase 1\t\tCase 2\t\tCase 3" << endl;
  for (int size = 10; size <= 100000000; size *= 10) {
    // repeat each case for three times
    int *sortArray = new int[size];
    for (int i = 0; i < 3; i++) {
      generate(sortArray, sortArray + size, rand);

      // Case 1: sorting random values
      auto startTime = chrono::steady_clock::now();
      quicksort(sortArray, sortArray + size);
      auto endTime = chrono::steady_clock::now();
      timetaken[i][0] = endTime - startTime;

      // Case 2: sorting data that is already sorted
      startTime = chrono::steady_clock::now();
      quicksort(sortArray, sortArray + size);
      endTime = chrono::steady_clock::now();
      timetaken[i][1] = endTime - startTime;

      // Case 3: sorting data that is in reverse sorted order
      reverse(sortArray, sortArray + size);
      startTime = chrono::steady_clock::now();
      quicksort(sortArray, sortArray + size);
      endTime = chrono::steady_clock::now();
      timetaken[i][2] = endTime - startTime;
    }

    cout << size << "\t\t\t\t";
    cout << (timetaken[0][0].count() + timetaken[1][0].count() + timetaken[2][0].count()) / 3.0 << "\t";
    cout << (timetaken[0][1].count() + timetaken[1][1].count() + timetaken[2][1].count()) / 3.0 << "\t";
    cout << (timetaken[0][2].count() + timetaken[1][2].count() + timetaken[2][2].count()) / 3.0 << "\t";
    cout << endl;

    delete[] sortArray;
  }

  cout << endl;
  return 0;
}