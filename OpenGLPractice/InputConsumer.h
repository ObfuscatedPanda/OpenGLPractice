
#include "programobject.h"

#ifndef INPUT_CONSUMER_H
#define INPUT_CONSUMER_H
#ifdef DEBUG
#define MEMORY_DEBUG
#endif

class InputConsumer :
	public ProgramObject
{
private:
	USHORT *keyboardMap;
	bool acceptsMouse;


public:
	InputConsumer(void);
	~InputConsumer(void);
 
};

#endif