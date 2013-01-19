#include "InputHandler.h"
#include <strsafe.h>
#include <math.h>

InputHandler::InputHandler()
{
	// We only have one input handler per input stream
	// Register this InputHandler for RawInput
	
	// variable only temporarily part of this class
	xpos = 0.0f;
	zpos = 0.0f;
	angle = 0;

	registeredForRawInput = false;
	RawInputDev[0].usUsagePage = 0x01; 
	RawInputDev[0].usUsage = 0x02; 
	RawInputDev[0].dwFlags = RIDEV_NOLEGACY;   // adds HID mouse and also ignores legacy mouse messages
	RawInputDev[0].hwndTarget = 0;

	RawInputDev[1].usUsagePage = 0x01; 
	RawInputDev[1].usUsage = 0x06; 
	RawInputDev[1].dwFlags = RIDEV_NOLEGACY;   // adds HID keyboard and also ignores legacy keyboard messages
	RawInputDev[1].hwndTarget = 0;
	 


	
}


InputHandler::~InputHandler(void)
{
	// Notify the system that we wish to un-register from the RawInput service
}

void InputHandler::Init(LPARAM lParam)
{
	if (RegisterRawInputDevices(RawInputDev, 2, sizeof(RawInputDev[0])) == FALSE) {
		//registration failed. Call GetLastError for the cause of the error
		keyboard = NULL;
		mouse    = NULL;
	}
	else
	{
		registeredForRawInput = true;
		keyboard = &RawInputDev[1];
		mouse    = &RawInputDev[0];

		// Check to see how large our input buffer should be
		GetRawInputData((HRAWINPUT) lParam, RID_INPUT, NULL, &keyboardInputBufferSize, sizeof (RAWINPUTHEADER));

		// Allocate our input buffers based on the reported size from GetRawInputData
		mouseInputBuffer=new BYTE[mouseInputBufferSize];
		keyboardInputBuffer=new BYTE[keyboardInputBufferSize];
	}
}

int InputHandler::ReadInput(LPARAM lParam)
{

	UINT dwSize;
	HRESULT hResult;
	TCHAR szTempOutput[3000];


	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, 
					sizeof(RAWINPUTHEADER));
	LPBYTE lpb = new BYTE[dwSize];
	if (lpb == NULL) 
	{
		return 0;
	} 

	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, 
			sizeof(RAWINPUTHEADER)) != dwSize )
			OutputDebugString (TEXT("GetRawInputData does not return correct size !\n")); 

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEKEYBOARD) 
	{
		// We don't actually need this print - we can take the raw data and process it
		hResult = StringCchPrintf(szTempOutput, 3000/*STRSAFE_MAX_CCH*/, TEXT(" Kbd: make=%04x Flags:%04x Reserved:%04x ExtraInformation:%08x, msg=%04x VK=%04x \n"), 
			raw->data.keyboard.MakeCode, 
			raw->data.keyboard.Flags, 
			raw->data.keyboard.Reserved, 
			raw->data.keyboard.ExtraInformation, 
			raw->data.keyboard.Message, 
			raw->data.keyboard.VKey);
		if (FAILED(hResult))
		{
		    // TODO: write error handler
		}
		else
		{
			OutputDebugString(szTempOutput);

		//if(KeyDataValid(raw))
		//{
			if(raw->data.keyboard.VKey == 0x0025 && raw->data.keyboard.Message == 0x0100)
			{
				angle -= 1.1;
			}
			else if(raw->data.keyboard.VKey == 0x0027 && raw->data.keyboard.Message == 0x0100)
			{
				angle += 1.1;
			}
			if(raw->data.keyboard.VKey == 0x0026 && raw->data.keyboard.Message == 0x0100)
			{
				xpos += 1 * cos(angle * 3.1415962 /360);
				zpos += 1 * sin(angle * 3.1415962 /360);
			}
			else if(raw->data.keyboard.VKey == 0x0028 && raw->data.keyboard.Message == 0x0100)
			{
				xpos -= 1 * cos(angle * 3.1415962 /360);
				zpos -= 1 * sin(angle * 3.1415962 /360);
			}
			if(angle < 0)
			{
				angle += 360;
			}
			if(angle > 360)
			{
				angle -= 360;
			}

			if(xpos < -20.0f)
			{
				xpos = -20;
			}
			if(20.0f < xpos)
			{
				xpos = 20;
			}
		//}
		}
	}
	else if (raw->header.dwType == RIM_TYPEMOUSE) 
	{
		hResult = StringCchPrintf(szTempOutput, 3000/*STRSAFE_MAX_CCH*/, TEXT("Mouse: usFlags=%04x ulButtons=%04x usButtonFlags=%04x usButtonData=%04x ulRawButtons=%04x lLastX=%04x lLastY=%04x ulExtraInformation=%04x\r\n"), 
			raw->data.mouse.usFlags, 
			raw->data.mouse.ulButtons, 
			raw->data.mouse.usButtonFlags, 
			raw->data.mouse.usButtonData, 
			raw->data.mouse.ulRawButtons, 
			raw->data.mouse.lLastX, 
			raw->data.mouse.lLastY, 
			raw->data.mouse.ulExtraInformation);

		if (FAILED(hResult))
		{
		// TODO: write error handler
		}
		OutputDebugString(szTempOutput);

		//if(MouseDataValid(raw))
		//{

		//}
	} 

	delete[] lpb; 
	return 0;

}

bool InputHandler::KeyDataValid(RAWINPUT *rawKeyboardData)
{
	
	return true;
}

bool InputHandler::MouseDataValid(RAWINPUT *rawMouseData)
{
	return true;

}