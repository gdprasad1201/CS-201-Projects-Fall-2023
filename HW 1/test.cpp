/*
   Sample program to test the performance of sort algorithm.
   To Compile: g++ -std=c++17 perftest.cpp
   To Run: ./a.out
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>

using namespace std;

template <class RandomIt> RandomIt partition(RandomIt first, RandomIt last) {
  // Select the middle element as the pivot
  RandomIt pivot = first + distance(first, last) / 2;

  // Swap the pivot element with the last element
  swap(*pivot, *(last - 1));

  // Partition the range into two parts: elements < pivot and elements >= pivot
  RandomIt i = first;
  for (RandomIt j = first; j < last - 1; j++) {
    if (*j < *(last - 1)) {
      swap(*i, *j);
      i++;
    }
  }

  // Swap the pivot element back to its correct position
  swap(*i, *(last - 1));

  // Return the iterator to the pivot element
  return i;
}

template <class RandomIt> constexpr void quicksort(RandomIt first, RandomIt last) {
  if (first < last - 1) {
    // Partition the range and get the pivot position
    RandomIt pivot = partition(first, last);

    // Recursively sort the two partitions
    quicksort(first, pivot);
    quicksort(pivot + 1, last);
  }
}

template <class RandomIt>
constexpr void heapify(RandomIt start, RandomIt end, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < distance(start, end) && *(start + left) > *(start + largest))
    {
        largest = left;
    }

    if (right < distance(start, end) && *(start + right) > *(start + largest))
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(*(start + i), *(start + largest));
        heapify(start, end, largest);
    }
}

template <class RandomIt>
constexpr void heapsort(RandomIt start, RandomIt end)
{
    // max heapify sequence
    for (int i = distance(start, end) / 2; i >= 0; i--)
    {
        heapify(start, end, i);
    }

    // swapping first int with the last node and then max heapifying again
    for (int i = distance(start, end) - 1; i >= 0; i--)
    {
        swap(*start, *(start + i));
        heapify(start, start + i, 0);
    }
}

int main(int argc, char **argv)
{
    chrono::duration<double> timetaken[3];
    // chrono::time_point<chrono::steady_clock> starttime, endtime;
    cout << "Problem Size\tTime Taken (seconds)" << endl;
    cout << "\t\tCase 1\tCase 2\tCase 3" << endl;
    // for (int size = 10; size <= 100000000; size *= 10) {
    int size = 100000000;
    int *a = new int[size];
    cout << size << "\t\t";
    generate(a, a + size, rand);

    /* Case 1: sorting random values */
    auto starttime = chrono::steady_clock::now();
    quicksort(a, a + size);
    auto endtime = chrono::steady_clock::now();
    timetaken[0] = endtime - starttime;

    /* Case 2: sorting data that is already sorted */
    starttime = chrono::steady_clock::now();
    quicksort(a, a + size);
    endtime = chrono::steady_clock::now();
    timetaken[1] = endtime - starttime;

    /* Case 3: sorting data that is in reverse sorted order */
    reverse(a, a + size);
    starttime = chrono::steady_clock::now();
    quicksort(a, a + size);
    endtime = chrono::steady_clock::now();
    timetaken[2] = endtime - starttime;

    cout << timetaken[0].count() << "\t";
    cout << timetaken[1].count() << "\t";
    cout << timetaken[2].count() << endl;

    delete[] a;

    return 0;
}
