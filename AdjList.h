#ifndef __AdjList_H
#define __AdjList_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

typedef unsigned int              uint;   // id of vertice
typedef unordered_set<uint>       hashid; // hash of destination vertex
typedef vector<hashid*>           AList;  // list of hashs

enum Request
{
    EmptyInnerDegreesCount  = 1,
    EmptyMutualDegreesCount = 2,
    MaxInnerDegreesCount    = 3,
    Finish                  = 4
};

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

    AdjList            ( )           { };
    AdjList            (AdjList& al) { };
    virtual ~AdjList   ( )           { };
public:
    static bool GetEdge    (uint          from,
                            uint          to     );   // check for directed edge existing
    static bool FillLists  (const string& fileNames,
                            const string& fileAdj);   // for initialisation of lists
    static void ClearLists ( );            // for correct finish without memory leaks
private:
    static void ResizeAdjList               (uint          size      );
    static bool FillNamesList               (const string& fileNames );
    static bool FillAdjList                 (const string& fileAdj   );
    static bool SetAdjListLine              (const string& line,
                                             uint          idx       );
    static void UpdateDegreesInfoByNextNode (uint          idx       );
public:
    static void CalcDegrees                      ( ); // call after FillLists
    static void NamesWithEmptyDegreeCount        ( ); // call after CalcDegrees for 1 task
    static void NamesWithEmptyReflectDegreeCount ( ); // call after CalcDegrees for 2 task
    static void NamesWithMaxDegreeCount          ( ); // call after CalcDegrees for 3 task

    static void ShowList                         (uint          request);
    static void ShowList                         (vector<uint>& idsList);
};

#endif // #ifndef __AdjList_H

