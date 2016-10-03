#include <iostream>
#include "AdjList.h"

int main()
{
    uint request;

// initialize structures for tasks solving
    if (!AdjList::FillLists ("names.txt", "AdjList.txt"))
    {
        cout << "incorrect input data\n";
        return 1;
    }

// Calculaion of inner degree and mutual edges count for every nodes
    AdjList::CalcDegrees ();

// prepare lists of names for task 1, 2 and 3
    AdjList::NamesWithEmptyDegreeCount        ();
    AdjList::NamesWithEmptyReflectDegreeCount ();
    AdjList::NamesWithMaxDegreeCount          ();

// show requested lists
    do
    {
        cin >> request;

        if (request != Finish)
        {
            AdjList::ShowList (request);
        }
    }
    while (request != Finish);

    AdjList::ClearLists ();

    return 0;
}

