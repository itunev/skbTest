#ifndef __AdjList_H
#define __AdjList_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

typedef unsigned int              uint;   // id of vertice
typedef unordered_set<uint>       hashid; // hash of destination vertex
typedef vector<hashid*>           AList;  // list of hashs

class AdjList
{
    static uint           maxInnerDegree; // maximum count of inner directed edges
    static vector<uint>   innerDegrees;   // inner directed edges count
    static vector<uint>   reflectDegrees; // mutual directed edges count

    static vector<string> names;          // ordered list of names
    static AList          adjList;        // adjacency list

    static vector<uint>   emptyMutual;
    static vector<uint>   emptyInnerDegrees;
    static vector<uint>   maxInnerDegrees;
public:
    AdjList            ( )           { };
    AdjList            (AdjList& al) { };
    virtual ~AdjList   ( );

    static bool FillLists      (const string& fileNames,
                                const string& fileAdj); // for initialisation of lists
private:
    static void FillNamesList  (ifstream&     myfile );
    static bool FillAdjList    (ifstream&     myfile );
    static bool SetAdjListLine (const string& line,
                                uint&         idx    );
public:
    static void CalcDegrees                      ( ); // call after FillLists
    static void NamesWithEmptyDegreeCount        ( ); // call after CalcDegrees for 1 task
    static void NamesWithEmptyReflectDegreeCount ( ); // call after CalcDegrees for 2 task
    static void NamesWithMaxDegreeCount          ( ); // call after CalcDegrees for 3 task

    static void ShowList                         (uint command);
};

#endif // #ifndef __AdjList_H

