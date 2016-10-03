#include <iostream>
#include "AdjList.h"

int main()
{
    AdjList al;
    uint request;

// initialize structures for tasks solving
    if (!al.FillLists ("names.txt", "AdjList.txt"))
    {
        cout << "incorrect input data\n";
        return 1;
    }

// Calculaion of inner degree and mutual edges count for every nodes
    al.CalcDegrees ();

// prepare lists of names for task 1, 2 and 3
    al.NamesWithEmptyDegreeCount        ();
    al.NamesWithEmptyReflectDegreeCount ();
    al.NamesWithMaxDegreeCount          ();

// show requested lists
    do
    {
        cin >> request;
        if (request != Finish)
        {
            al.ShowList (request);
        }
    }
    while (request != Finish);

    return 0;
}

