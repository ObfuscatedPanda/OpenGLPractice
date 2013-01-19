#include "ProgramObject.h"


ProgramObject::ProgramObject(void)
{
	
}


ProgramObject::~ProgramObject(void)
{
}

void * ProgramObject::operator new (size_t size)
{
	IncrementTotalNewCalls();
	void * allocated = malloc(size);
	if(!allocated)
	{
		throw mem_exception();
	}
	else
	{
		IncrementSuccessfulNewCalls();
	}
	return allocated;
}

//void * ProgramObject::operator new[] (size_t size)
//{
//
//}

void ProgramObject::operator delete(void *memory)
{
	IncrementTotalDeleteCalls();
	if(memory)
	{
		free(memory);
		IncrementSuccessfulDeleteCalls();
	}
}

//void ProgramObject::operator delete(ProgramObject []reference)
//{
//
//}