#include "arrayref.h"

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

template<class Ref>
void doPrint(Ref& array, const char* desc)
{
    cout << "Contents of " << desc << ": ";
    for (const int* it = array.begin(); it != array.end(); ++it) {
        if (it != array.begin()) cout << ", ";
        cout << *it;
    }
    cout << "\n";
}

void printArrayNonconst(ArrayRef<int>& array)
{
    doPrint(array, "array (nonconst)");
}

void printConstArray(const ArrayRef<int>& array)
{
    doPrint(array, "const array");
}

void printArrayOfConst(ArrayRef<const int>& array)
{
    doPrint(array, "array of const");
}

void printConstArrayOfConst(const ArrayRef<const int>& array)
{
    doPrint(array, "const array of const");
}

void printArrayReverse(const ArrayRef<const int>& array)
{
    cout << "Reverse contents of array: ";
    for (ArrayRef<const int>::reverse_iterator it = array.rbegin();
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
    const int constAry[] = { 1, 2, 3 };
    vector<int> vec;
    vec.push_back(12345); vec.push_back(54321); vec.push_back(33333);

    ArrayRef<int> refNonconst(ary), refNonconst2(vec);
    ArrayRef<const int> refConst(ary), refConst2(vec);

    printArrayNonconst(refNonconst);
    printArrayOfConst(refConst);

    printConstArray(refNonconst);
    printConstArray(ary);
    printConstArray(vec);

    printConstArrayOfConst(refConst);
    printConstArrayOfConst(refNonconst);
    printConstArrayOfConst(ary);
    printConstArrayOfConst(constAry);
    printConstArrayOfConst(vec);

    cout << "An empty ArrayRef has a size() of " << ArrayRef<bool>().size()
        << ".\n";
    const ArrayRef<vector<int> > emptyRef;
    cout << "Is it empty? " << boolalpha << emptyRef.empty() << "\n";

    const ArrayRef<int> vecRef(vec);
    try {
        vecRef.at(55);
    }
    catch (std::exception& e) {
        cout << "Illegal arg to at() results in error: " << e.what() << "\n";
    }

    cout << "The second element of the vector is " << vecRef[1] << ".\n";
    vecRef[1] = 9;
    cout << "And now it is " << vecRef[1] << ".\n";

    cout << "ary has " << makeArrayRef(ary).size() << " elements.\n";
    cout << "vec has " << makeArrayRef(vec).size() << " elements.\n";

#if ERRTEST == 1
    printArrayNonconst(constAry);
#elif ERRTEST == 2
    printArrayNonconst(refConst);
#elif ERRTEST == 3
    prinyConstArray(constAry);
#elif ERRTEST == 4
    printConstArray(refConst);
#elif ERRTEST == 5
    const ArrayRef<int> constRef(refConst);
#endif
}
