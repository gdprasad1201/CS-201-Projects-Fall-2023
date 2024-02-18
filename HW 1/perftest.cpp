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
RandomIt partition(RandomIt first, RandomIt last)
{
	// Select the middle element as the pivot
	RandomIt pivot = first + distance(first, last) / 2;

	// Swap the pivot element with the last element
	swap(*pivot, *(last - 1));

	// Partition the range into two parts: elements < pivot and elements >= pivot
	RandomIt i = first - 1;
	for (RandomIt j = first; j <= last - 1; j++)
	{
		if (*j < *(last - 1))
		{
			i++;
			swap(*i, *j);
			
		}
	}

	// Swap the pivot element back to its correct position
	swap(*(i + 1), *(last - 1));

	// Return the iterator to the pivot element
	return i + 1;
}

template <class RandomIt>
constexpr void quicksort(RandomIt first, RandomIt last)
{
	if (first < last - 1)
	{
		// Partition the range and get the pivot position
		RandomIt pivot = partition(first, last);

		// Recursively sort the two partitions
		quicksort(first, pivot);
		quicksort(pivot + 1, last);
	}
}

template <class RandomIt> constexpr void heapify(RandomIt start, RandomIt end, int i) {
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

template <class RandomIt> constexpr void heapsort(RandomIt start, RandomIt end) {
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
	chrono::time_point<chrono::steady_clock> starttime, endtime;
	cout << "Problem Size\tTime Taken (seconds)" << endl;
	cout << "\t\tCase 1\tCase 2\tCase 3" << endl;
	for (int size = 10; size <= 100000000; size *= 10) {
		int *a = new int[size];

		// repeat each case for three times 
		for (int i = 0; i < 3; i++) {
			generate(a, a + size, rand);

			/* Case 1: sorting random values */
			starttime = chrono::steady_clock::now();
			quicksort(a, a + size);
			endtime = chrono::steady_clock::now();
			timetaken[i][0] = endtime - starttime;

			/* Case 2: sorting data that is already sorted */
			starttime = chrono::steady_clock::now();
			quicksort(a, a + size);
			endtime = chrono::steady_clock::now();
			timetaken[i][1] = endtime - starttime;

			/* Case 3: sorting data that is in reverse sorted order */
			reverse(a, a + size);
			starttime = chrono::steady_clock::now();
			quicksort(a, a + size);
			endtime = chrono::steady_clock::now();
			timetaken[i][2] = endtime - starttime;
		}

		// print the average time of three runs
		cout << size << "\t\t";
		cout << (timetaken[0][0].count() + timetaken[1][0].count() + timetaken[2][0].count())/3.0 << "\t";
		cout << (timetaken[0][1].count() + timetaken[1][1].count() + timetaken[2][1].count())/3.0 << "\t";
		cout << (timetaken[0][2].count() + timetaken[1][2].count() + timetaken[2][2].count())/3.0 << endl;

		delete[] a;
	}

	return 0;
}
