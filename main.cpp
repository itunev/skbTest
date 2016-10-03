#include <iostream>
#include "AdjList.h"

int main()
{
    AdjList al;
    uint command = 0;

// initialize structures for tasks solving
    if (!al.FillLists ("names.txt", "AdjList.txt"))
    {
        cout << "incorrect input data\n";
        return 1;
    }

// prepare lists of names for task 1, 2 and 3
    al.CalcDegrees ();
    al.NamesWithEmptyDegreeCount        ();
    al.NamesWithEmptyReflectDegreeCount ();
    al.NamesWithMaxDegreeCount          ();

// show required lists
    while (command != 4)
    {
        cin >> command;
        al.ShowList (command);
    }

    return 0;
}

