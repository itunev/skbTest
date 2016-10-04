#include "AdjList.h"
#include <sstream>
#include <cstring>
#include <fstream>
#include <iostream>

vector<uint>   AdjList::emptyMutual;
vector<uint>   AdjList::emptyInnerDegrees;
vector<uint>   AdjList::maxInnerDegrees;

uint           AdjList::maxInnerDegree;
vector<uint>   AdjList::innerDegrees;
vector<uint>   AdjList::reflectDegrees;

vector<string> AdjList::names;
AList          AdjList::adjList;

/**
* check for existing oriented edge
*/
bool AdjList::GetEdge (uint from, uint to)
{
    return (adjList [from] &&
            adjList [from] -> find (to) !=
            adjList [from] -> end ());
}
/**
* input data from files to structures
*/
bool AdjList::FillLists (const string& fileNames, const string& fileAdj)
{
    if (!FillNamesList (fileNames))
    {
        return false;
    }

    if (!FillAdjList (fileAdj))
    {
        return false;
    }

    return true;
}

void AdjList::ClearLists ( )
{
    ResizeAdjList (0);
}
/**
* fill names list from file
*/
bool AdjList::FillNamesList (const string& fileNames)
{
    ifstream namesFile;
    string   line;
    namesFile.open (fileNames);

    if (!namesFile.is_open ())
    {
        return false;
    }

    while (getline (namesFile, line))
    {
        if (line.size ())
        {
            names.push_back (line);
        }
    }

    namesFile.close();

    return true;
}
/**
* clear adjList and resize it filling by empty pointers
*/
void AdjList::ResizeAdjList (uint size)
{
    for (AList::iterator it = adjList.begin(); it != adjList.end(); it++)
    {
        if (*it)
        {
            delete (*it);
        }
    }

    adjList.resize (size, NULL);
}
/**
* prepare and fill adjacency list from file
*/
bool AdjList::FillAdjList (const string& fileAdj)
{
    ifstream adjFile;
    string   line;
    ResizeAdjList (names.size ());
    adjFile.open (fileAdj);

    if (!adjFile.is_open ())
    {
        return false;
    }

    for (uint idx = 0; getline (adjFile, line) && idx < names.size (); idx++)
    {
        if (line.size () && !SetAdjListLine (line, idx))
        {
            adjFile.close();
            return false;
        }
    }

    adjFile.close();

    return true;
}
/**
* parse line with numbers and fill one line (with index idx) of adjacency list
*/
bool AdjList::SetAdjListLine (const string& line, uint idx)
{
    hashid *      elist  = new hashid;
    istringstream ss (line);
    uint          dest;

    while (!ss.eof())
    {
        ss >> dest;

        if (dest < names.size () && dest != idx)
        {
            elist->insert (dest);
        }
        else
        {
            return false;
        }
    }

    adjList [idx] = elist;

    return true;
}
/**
* prepare arrays for tasks solving
*/
void AdjList::CalcDegrees ()
{
    uint idx       = 0;
    maxInnerDegree = 0;
    innerDegrees.  resize (names.size (), 0);
    reflectDegrees.resize (names.size (), 0);

    for (AList::iterator it = adjList.begin (); it != adjList.end (); it++, idx++)
    {
        if (*it) // it also warranty of ignoring of vertexes with empty outer degrees
        {
            UpdateDegreesInfoByNextNode (idx);
        }
    }
}

void AdjList::UpdateDegreesInfoByNextNode (uint idx)
{
    hashid * node = adjList [idx];

    for (hashid::iterator hit = node -> begin (); hit != node -> end (); hit++)
    {
        innerDegrees [*hit]++;   // idx likes *hit

        maxInnerDegree = max (maxInnerDegree, innerDegrees [*hit]);

        if (GetEdge (*hit, idx)) // is *hit likes idx too
        {
            reflectDegrees [idx]++;
        }
    }
}
// solving tasks 1 - prepare list of vertices with empty inner degrees
void AdjList::NamesWithEmptyDegreeCount ()
{
    emptyInnerDegrees.clear ();

    for (uint i = 0; i < innerDegrees.size (); i++)
    {
        if (innerDegrees [i] == 0)
        {
            emptyInnerDegrees.push_back (i);
        }
    }
}
// solving task 2
void AdjList::NamesWithEmptyReflectDegreeCount ()
{
    emptyMutual.clear ();

    for (uint i = 0; i < reflectDegrees.size (); i++)
    {
        if (reflectDegrees [i] == 0 && adjList[i])
        {
            emptyMutual.push_back (i);
        }
    }
}
// solving tasks 3
void AdjList::NamesWithMaxDegreeCount ()
{
    maxInnerDegrees.clear ();

    for (uint i = 0; i < innerDegrees.size (); i++)
    {
        if (innerDegrees [i] == maxInnerDegree)
        {
            maxInnerDegrees.push_back (i);
        }
    }
}
// show requested list
void AdjList::ShowList (uint request)
{
    switch (request)
    {
        case EmptyInnerDegreesCount:
            ShowList (emptyInnerDegrees);
            break;
        case EmptyMutualDegreesCount:
            ShowList (emptyMutual);
            break;
        case MaxInnerDegreesCount:
            ShowList (maxInnerDegrees);
            break;
        default:
            cout << "unknown request " << request << endl;
    }
}
// show list
void AdjList::ShowList (vector<uint>& idsList)
{
    for (uint i = 0; i < idsList.size (); i++)
    {
        cout << names [idsList [i]] << "\n";
    }
}

