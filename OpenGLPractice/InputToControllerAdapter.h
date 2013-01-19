#pragma once
#include "ProgramObject.h"
#include "InputToControllerAdapter.h"
#include "LinkedList.h"

#ifndef INPUT_TO_CONTROLLER_ADAPTER_H
#define INPUT_TO_CONTROLLER_ADAPTER_H
class InputToControllerAdapter :
	public ProgramObject
{
	// Use a linked-list to see what controls we can consume
	// TODO: Switch to an array or hashtable to see the control mapping
	LinkedList* consumableControls;
public:
	InputToControllerAdapter(void);
	~InputToControllerAdapter(void);
	void AddConsumableControl(USHORT control, USHORT mappedValue);
};

#endif
