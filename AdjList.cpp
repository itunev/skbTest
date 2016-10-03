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

AdjList::~AdjList ()
{
    for (AList::iterator it = adjList.begin(); it != adjList.end(); it++)
    {
        if (*it)
        {
            delete *it;
        }
    }
}
/**
* input data from files to structures
*/
bool AdjList::FillLists (const string& fileNames, const string& fileAdj)
{
    ifstream namesFile;
    namesFile.open (fileNames);

    if (namesFile.is_open ())
    {
        FillNamesList (namesFile);
        namesFile.close();
    }
    else
    {
        return false;
    }

    ifstream adjFile;
    adjFile.open (fileAdj);

    if (adjFile.is_open ())
    {
        if (!FillAdjList (adjFile))
        {
            adjFile.close();
            return false;
        }

        adjFile.close();
    }
    else
    {
        return false;
    }

    return true;
}
/**
* fill names list from file
*/
void AdjList::FillNamesList (ifstream& myfile)
{
    string   line;

    while (getline (myfile, line))
    {
        if (line.size ())
        {
            names.push_back (line);
        }
    }
}
/**
* prepare and fill adjacency list from file
*/
bool AdjList::FillAdjList (ifstream& myfile)
{
    uint   idx = 0;
    string line;
    adjList.resize (names.size (), NULL);

    while (getline (myfile, line) && idx < names.size ())
    {
        if (!SetAdjListLine (line, idx))
         {
            return false;
         }

        idx++;
    }

    return true;
}
/**
* parse line with numbers and fill one line (with index idx) of adjacency list
*/
bool AdjList::SetAdjListLine (const string& line, uint& idx)
{
    if (line.size ())
    {
        hashid *      elist  = new hashid;
        istringstream ss (line);
        uint          dest;

        while (!ss.eof())
        {
            ss >> dest;
            if (dest < names.size () && dest != idx)
                elist->insert (dest);
            else
                return false;
        }

        adjList [idx] = elist;
    }

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
            for (hashid::iterator hit = (*it) -> begin (); hit != (*it) -> end (); hit++)
            {
                innerDegrees [*hit]++; // idx likes *hit

                if (maxInnerDegree < innerDegrees [*hit])
                {
                    maxInnerDegree++;
                }

                if (adjList [*hit] &&
                    adjList [*hit] -> find (idx) !=
                    adjList [*hit] -> end ()) // is *hit likes idx too
                {
                    reflectDegrees [idx]++;
                }
            }
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

