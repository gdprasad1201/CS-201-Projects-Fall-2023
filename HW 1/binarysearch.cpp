/*
   Program to perform binary search using iterators

   To Compile: g++ -Wall -std=c++17 binarysearch.cpp
   To Run: ./a.out
           <enter a number to search or Control-D to end>
*/
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <class RandomIt>
void print(RandomIt start, RandomIt end) {
    while (start != end) {
        cout << *start << " ";
        ++start;
    }
    cout << endl;
}

template <class ForwardIt, class T>
constexpr bool binarysearch(ForwardIt first, ForwardIt last, const T &value) {
    auto low = first;
    auto high = last - 1;
    while (low <= high) {
        auto mid = low + distance(low, high) / 2;
        cout << *low << " " << *mid << " " << *high << endl;

        if (*mid < value)
            low = mid + 1;
        else if (*mid > value)
            high = mid - 1;
        else
            return true;
    }
    return false;
}

template <class ForwardIt, class T>
constexpr bool recursive_binarysearch(ForwardIt first, ForwardIt last, const T &value) {
    auto low = first;
    auto high = last - 1;
    if (low <= high) {
        auto mid = low + distance(low, high) / 2;
        cout << *low << " " << *mid << " " << *high << endl;

        if (*mid < value)
            return recursive_binarysearch(mid + 1, last, value);
        else if (*mid > value)
            return recursive_binarysearch(first, mid, value);
        else
            return true;
    }
    else
        return false;
}

int main(int argc, char *argv[]) {
    array<int, 12> a1;
    generate(a1.begin(), a1.end(), rand);
    print(a1.begin(), a1.end());

    sort(a1.begin(), a1.end());
    print(a1.begin(), a1.end());

    cout << "Enter an integer: ";
    int value = 0;
    while (cin >> value) {
        if (binarysearch(a1.begin(), a1.end(), value))
            cout << value << " found!" << endl;
        else
            cout << value << " not found!" << endl;

        if (recursive_binarysearch(a1.begin(), a1.end(), value))
            cout << value << " found!" << endl;
        else
            cout << value << " not found!" << endl;

        cout << "Enter an integer: ";
    }

    return 0;
}
