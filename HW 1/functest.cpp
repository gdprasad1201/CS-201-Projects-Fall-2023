/*
   Sample program to test sort with different containers.
   To Compile: g++ -std=c++17 functest.cpp
   To Run: ./a.out
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>

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
void quicksort(RandomIt first, RandomIt last)
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

template <class RandomIt>
void print(RandomIt start, RandomIt end)
{
	while (start != end)
	{
		cout << *(start++) << " ";
	}
	cout << endl;
}

int main(int argc, char **argv)
{
	int choice;
	int *a = new int[10];
	generate(a, a + 10, rand);
	int a0[] = {56, 23, 11, 64, 43};
	array<int, 5> a1 = {5, 4, 3, 2, 1};
	array<string, 5> a2 = {"lion", "dog", "cat", "fox", "pig"};
	vector<double> v = {4.2, 3.1, 5.6, 2.8, 1.9};

	cout << "Which sorting algorithm do use want to use: " << endl
		 << "1. Quick Sort" << endl
		 << "2. Heap Sort" << endl
		 << "3. sort" << endl;
	cin >> choice;
	cout << endl;

	if (choice == 1)
	{
		quicksort(a, a + 10);
		print(a, a + 10);

		quicksort(a0, a0 + 5);
		print(a0, a0 + 5);

		quicksort(&a0[0], &a0[5]);
		print(&a0[0], &a0[5]);

		quicksort(a1.begin(), a1.end());
		print(a1.begin(), a1.end());

		quicksort(a2.begin(), a2.end());
		print(a2.begin(), a2.end());

		reverse(a2.begin(), a2.end());
		print(a2.begin(), a2.end());

		quicksort(a2.begin(), a2.end());
		print(a2.begin(), a2.end());

		quicksort(v.begin(), v.end());
		print(v.begin(), v.end());
	}
	else if (choice == 2)
	{
		heapsort(a, a + 5);
		print(a, a + 5);

		heapsort(a0, a0 + 5);
		print(a0, a0 + 5);

		heapsort(&a0[0], &a0[5]);
		print(&a0[0], &a0[5]);

		heapsort(a1.begin(), a1.end());
		print(a1.begin(), a1.end());

		heapsort(a2.begin(), a2.end());
		print(a2.begin(), a2.end());

		reverse(a2.begin(), a2.end());
		print(a2.begin(), a2.end());

		heapsort(a2.begin(), a2.end());
		print(a2.begin(), a2.end());

		heapsort(v.begin(), v.end());
		print(v.begin(), v.end());
	}
	else if (choice == 3)
	{
		sort(a, a + 5);
		print(a, a + 5);

		sort(a0, a0 + 5);
		print(a0, a0 + 5);

		sort(&a0[0], &a0[5]);
		print(&a0[0], &a0[5]);

		sort(a1.begin(), a1.end());
		print(a1.begin(), a1.end());

		sort(a2.begin(), a2.end());
		print(a2.begin(), a2.end());

		reverse(a2.begin(), a2.end());
		print(a2.begin(), a2.end());

		sort(a2.begin(), a2.end());
		print(a2.begin(), a2.end());

		sort(v.begin(), v.end());
		print(v.begin(), v.end());
	}

	delete[] a;
	return 0;
}
