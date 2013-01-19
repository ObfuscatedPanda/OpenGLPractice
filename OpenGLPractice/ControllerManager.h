
#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include "ProgramObject.h"
#include "Controller.h"
#include "InputHandler.h"

class ControllerManager :
	public ProgramObject
{
public:
	ControllerManager(void);
	~ControllerManager(void);
	void AssignControllerToInput(Controller* controller, InputHandler* input);

};

#endif