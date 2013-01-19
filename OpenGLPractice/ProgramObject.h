

#ifndef PROGRAM_OBJECT_H
#define PROGRAM_OBJECT_H
#include <windows.h>
#include "Globals.h"
//TODO: change hardcoded define to compiler flag
#define MEMORY_DEBUG
//using namespace std;
void IncrementTotalNewCalls();
void IncrementSuccessfulNewCalls();
void IncrementTotalDeleteCalls();
void IncrementSuccessfulDeleteCalls();

class mem_exception :	public Exception {}; 
class ENotImplemented : public Exception {};

class ProgramObject
{
private:
	long temporary;
public:
	ProgramObject(void);
	~ProgramObject(void);
	static void* operator new (size_t size);
	//static void * operator new[] (size_t size);
	static void operator delete(void* reference);
	//static void operator delete[](ProgramObject []reference);
	
};


/*****************************************************************************/
/*                            Exception Classes                              */
/*****************************************************************************/
class E_NO_MEM;
class E_NONEXISTANT_FILE;
class E_NULL_PTR;

#endif