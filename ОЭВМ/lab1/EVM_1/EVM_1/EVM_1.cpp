using namespace std;
#include <iostream>
#include "BufferValue.h"
#include "IntRipper.h"
#include "LongDoubleRipper.h"

int main()
{
    //int, long double
    //task 5: swap bit groups

    //input vars
    int inputInt, startIndex1, startIndex2, count;
    long double inputDouble;

    //classes for value processing
    LongDoubleRipper doubleRipper;
    IntRipper intRipper;





    ////////////////////////////////////////////////
    ///////32 bit int processing.../////////////////
    ////////////////////////////////////////////////

    cout << "Enter int value, startIndex1, startIndex2, count\n";

    //get int input
    if (scanf_s("%i%i%i%i", &inputInt, &startIndex1, &startIndex2, &count) != 4)
    {
        cout << "Invalid input";
        return 0;
    }
    
    cout << "\n";
    //print int bits
    intRipper.PrintBits(inputInt);

    //print swap result
    cout << "\n+++++++++++++++++++++++SWAPPING++++++++++++++++++++++++++++++++++++\n";
    intRipper.SwapBitGroups(inputInt, startIndex1, startIndex2, count);
    cout << "\n";




    ////////////////////////////////////////////////
    ///////64 bit float processing...///////////////
    ////////////////////////////////////////////////


    cout << "Enter long double value, startIndex1, startIndex2, count\n";

    //get input
    if (scanf_s("%lf%i%i%i", &inputDouble, &startIndex1, &startIndex2, &count) != 4)
    {
        cout << "Invalid input";
        return 0;
    }

    cout << "\n";
    //print long double bits
    doubleRipper.PrintBits(inputDouble);

    //print swap result
    cout << "\n+++++++++++++++++++++++SWAPPING++++++++++++++++++++++++++++++++++++\n";
    doubleRipper.SwapBitGroups(inputDouble, startIndex1, startIndex2, count);
    cout << "\n";

    return 1;
}

