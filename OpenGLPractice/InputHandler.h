#pragma once

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <Windows.h>
#include "programobject.h"

class InputHandler :
	public ProgramObject
{
private:

	/*        Members                           */
	bool registeredForRawInput;
	RAWINPUTDEVICE RawInputDev[2];
	RAWINPUTDEVICE *keyboard;
	RAWINPUTDEVICE *mouse;
	unsigned int keyboardInputBufferSize;
	unsigned int mouseInputBufferSize;
	BYTE *keyboardInputBuffer;
	BYTE *mouseInputBuffer;

	/*        Methods                          */
	bool KeyDataValid(RAWINPUT *rawKeyboardData);
	bool MouseDataValid(RAWINPUT *rawMouseData);


	//TODO: add a buffer to store unconsumed commands - commands should be handed off as soon as possible

public:
	InputHandler();
	~InputHandler(void);
	int ReadInput(LPARAM lParam);
	void Init(LPARAM lParam);
	SCALAR xpos;
	SCALAR zpos;
	SCALAR angle;
};
#endif