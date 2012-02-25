#include "arrayref.h"

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

void printArray(const ArrayRef<int>& array)
{
    cout << "Contents of array: ";
    for (const int* it = array.begin(); it != array.end(); ++it) {
        if (it != array.begin()) cout << ", ";
        cout << *it;
    }
    cout << "\n";
}

void printArrayOfConst(const ArrayRef<const int>& array)
{
    cout << "Contents of array of const: ";
    for (const int* it = array.begin(); it != array.end(); ++it) {
        if (it != array.begin()) cout << ", ";
        cout << *it;
    }
    cout << "\n";
}

void printArrayReverse(const ArrayRef<int>& array)
{
    cout << "Reverse contents of array: ";
    for (ArrayRef<int>::const_reverse_iterator it = array.rbegin();
            it != array.rend(); ++it)
    {
        if (it != array.rbegin()) cout << ", ";
        cout << *it;
    }
    cout << "\n";
}

int main()
{
    int ary[] = { 11, 22, 33, 44, 55 };
    vector<int> vec;
    vec.push_back(12345);
    vec.push_back(54321);
    vec.push_back(33333);
    printArray(makeArrayRef(ary));
    printArrayOfConst(ary);
    printArrayReverse(ary);
    printArray(vec);
    printArrayReverse(vec);

    cout << "An empty ArrayRef has a size() of " << ArrayRef<bool>().size()
        << ".\n";
    ArrayRef<vector<int> > emptyRef;
    cout << "Is it empty? " << boolalpha << emptyRef.empty() << "\n";

    ArrayRef<int> vecRef(vec);
    try {
        vecRef.at(55);
    }
    catch (std::exception& e) {
        cout << "Illegal arg to at() results in error: " << e.what() << "\n";
    }

    cout << "The second element of the vector is " << vecRef[1] << ".\n";
    vecRef[1] = 9;
    cout << "And now it is " << vecRef[1] << ".\n";

    const int constAry[] = { 100, 200, 400, 600 };
    printArrayOfConst(constAry);
}
