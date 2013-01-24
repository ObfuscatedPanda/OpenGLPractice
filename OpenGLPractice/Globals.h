
#include <iostream>
#include <cassert>
using namespace std;

#ifndef GLOBALS_H
#define GLOBALS_H

#ifndef null
#define null 0
#endif

typedef float SCALAR;

static int totalNewCalls = 0;
static int successfulNewCalls = 0;
static int totalDeleteCalls = 0;
static int successfulDeleteCalls = 0;

inline void IncrementTotalNewCalls()         { totalNewCalls++;}
inline void IncrementSuccessfulNewCalls()    { successfulNewCalls++;}
inline void IncrementTotalDeleteCalls()      { totalDeleteCalls++;}
inline void IncrementSuccessfulDeleteCalls() { successfulDeleteCalls++;}
inline void PrintTotalNewCalls()             { printf ("TOTAL NEW CALLS: %d\n", totalNewCalls);}//<< "\n"; }
inline void PrintSuccessfulNewCalls()        { cout << "SUCCESSFUL NEW CALLS: "    << successfulNewCalls    << "\n"; }
inline void PrintTotalDeleteCalls()          { cout << "TOTAL DELETE CALLS: "      << totalDeleteCalls      << "\n"; }
inline void PrintSuccessfulDeleteCalls()     { cout << "SUCCESSFUL DELETE CALLS: " << successfulDeleteCalls << "\n"; }


#endif