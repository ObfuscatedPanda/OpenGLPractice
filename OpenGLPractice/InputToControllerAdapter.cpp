#include "InputToControllerAdapter.h"


InputToControllerAdapter::InputToControllerAdapter(void)
{
	consumableControls = new LinkedList;
}


InputToControllerAdapter::~InputToControllerAdapter(void)
{
}

void InputToControllerAdapter::AddConsumableControl(USHORT control, USHORT mappedValue)
{
	// Create node
	LinkedListNode* consumableControl = NULL;

	// Add node to list
	consumableControls->AppendNode(consumableControl);
}