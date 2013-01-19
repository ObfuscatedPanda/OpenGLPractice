/*      Steven Billington
        January 13, 2003
        May 26, 2003 - UPDATE
        RobotOGL.cpp
        rod@cprogramming.com

        The following program creates a window and then
        uses multiple OpenGL functions to display a
        animated robot constructed of different size
        cubes. To compile this code you must make the
        proper library links in project--->settings.

        I apologize for any amount of scattered code or
        mis-formatting that printing this may occur. Please
        feel free to email me at the address above for the .cpp
        file.
*/

/*      These are what we refer to as Pre-processor
        Directives. In order for certain functions in
        C++ to operate you must include certain header
        files. Each header file below contains different
        functions needed throughout this program.
*/



#pragma comment(linker, "/subsystem:windows")

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Globals.h"
#include "InputHandler.h"
#include "ProgramObject.h"
#include "StaticMesh.h"

#include "TextureLoader.h"
#include "stb_image.h"

bool inputCreated = false;
InputHandler input;
/*      Here we find a few global variables. While
        i don't really like to use global variables,
        i found them very handy for this particular
        program. These variables will control angles,
        fullscreen, and the global device context.
*/

HDC g_HDC;
float angle = 0.0f;
float horizontal_pos = 0.0f;
float legAngle[2] = {0.0f, 0.0f};
float armAngle[2] = {0.0f, 0.0f};
bool fullScreen = false;

/*      Function:       Render
        Purpose:        This function will be responsible
                                for the rendering, got to love my
                                descriptive function names : )
*/
void Render(Mesh* testMesh, GLuint textureId, stbi_uc* textureData, int textureWidth, int textureHeight, int imageComponents)
{

		static bool move_right = true;
        /*      Enable depth testing        */
        glEnable(GL_DEPTH_TEST);
		
        /*      Heres our rendering. Clears the screen
                to black, clear the color and depth
                buffers, and reset our modelview matrix.        */
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        /*      Increase rotation angle counter        */
        angle = angle + 1.0f;
		
		if(horizontal_pos >= 20)
		{
			move_right = false;
		}
		if(horizontal_pos <= -20)
		{
			move_right = true;
		}

		horizontal_pos += (float)(move_right? 0.1 : -0.1);
        /*      Reset after we have completed a circle        */
        if (angle >= 360.0f)
        {
                angle = 0.0f;
        }

        glPushMatrix();
        glLoadIdentity();

        /*      Move to 0,0,-30 , rotate the robot on
                its y axis, draw the robot, and dispose
                of the current matrix.        */
		horizontal_pos = input.xpos;
		
        glTranslatef(horizontal_pos, 0, input.zpos -30);
        glRotatef(input.angle, 1,  0, 0);
        //DrawRobot(0.0f, 0.0f, 0.0f);
		if(testMesh->IsSafeForRendering())
		{
			testMesh->Render();
		}
		glBindTexture(GL_TEXTURE_2D, textureId);
		// Need to add to move into our model class
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glEnable(GL_TEXTURE_2D);
	    glPopMatrix();

        glFlush();

        /*      Bring back buffer to foreground        */
        SwapBuffers(g_HDC);
}

//function to set the pixel format for the device context
/*      Function:       SetupPixelFormat
        Purpose:        This function will be responsible
                                for setting the pixel format for the
                                device context.    */
void SetupPixelFormat(HDC hDC)
{
        /*      Pixel format index        */
        int nPixelFormat;

        static PIXELFORMATDESCRIPTOR pfd = {
                sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
                1,                                      //default version
                PFD_DRAW_TO_WINDOW |                    //window drawing support
                PFD_SUPPORT_OPENGL |                    //opengl support
                PFD_DOUBLEBUFFER,                       //double buffering support
                PFD_TYPE_RGBA,                          //RGBA color mode
                32,                                     //32 bit color mode
                0, 0, 0, 0, 0, 0,                       //ignore color bits
                0,                                      //no alpha buffer
                0,                                      //ignore shift bit
                0,                                      //no accumulation buffer
                0, 0, 0, 0,                             //ignore accumulation bits
                16,                                     //16 bit z-buffer size
                0,                                      //no stencil buffer
                0,                                      //no aux buffer
                PFD_MAIN_PLANE,                         //main drawing plane
                0,                                      //reserved
                0, 0, 0 };                              //layer masks ignored

                /*      Choose best matching format  */
                nPixelFormat = ChoosePixelFormat(hDC, &pfd);

                /*      Set the pixel format to the device context  */
                SetPixelFormat(hDC, nPixelFormat, &pfd);
}

/*      Windows Event Procedure Handler
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
        /*      Rendering and Device Context
                variables are declared here.        */
        static HGLRC hRC;
        static HDC hDC;

        /*      Width and Height for the
                window our robot is to be
                displayed in.        */
        int width, height;

        switch(message)
        {
                case WM_CREATE: //window being created
						//input = new InputHandler(lParam);
                        hDC = GetDC(hwnd);  //get current windows device context
                        g_HDC = hDC;
                        SetupPixelFormat(hDC); //call our pixel format setup function

                        /*      Create rendering context and make it current        */
                        hRC = wglCreateContext(hDC);
                        wglMakeCurrent(hDC, hRC);
						
						input.Init(lParam);
						inputCreated = true;

                        return 0;
                        break;

                case WM_CLOSE:  //window is closing

                        /*      Deselect rendering context and delete it   */
                        wglMakeCurrent(hDC, NULL);
                        wglDeleteContext(hRC);

                        /*      Send quit message to queue   */
                        PostQuitMessage(0);

                        return 0;
                        break;

                case WM_SIZE:

                        /*      Retrieve width and height    */
                        height = HIWORD(lParam);
                        width = LOWORD(lParam);

                        /*      Don't want a divide by 0     */
                        if (height == 0)
                        {
                                height = 1;
                        }

                        /*      Reset the viewport to new dimensions  */
                        glViewport(0, 0, width, height);

                        /*      Set current Matrix to projection      */
                        glMatrixMode(GL_PROJECTION);
                        glLoadIdentity(); //reset projection matrix

                        /*      Time to calculate aspect ratio of
                                our window.                        */
                        gluPerspective(54.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);

                        glMatrixMode(GL_MODELVIEW); //set modelview matrix
                        glLoadIdentity(); //reset modelview matrix

                        return 0;
                        break;

				case WM_INPUT:
					input.ReadInput(lParam);

                default:

                        break;
        }

        return (DefWindowProc(hwnd, message, wParam, lParam));
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	
	WNDCLASSEX windowClass; //window class
	HWND    hwnd;           //window handle
	MSG     msg;            //message
	bool    done;           //flag for completion of app
	DWORD   dwExStyle;      //window extended style
	DWORD   dwStyle;        //window style
	RECT    windowRect;

	/*      Screen/display attributes*/
	int width = 800;
	int height = 600;
	int bits = 32;
		
	windowRect.left =(long)0;       //set left value to 0
	windowRect.right =(long)width;  //set right value to requested width
	windowRect.top =(long)0;        //set top value to 0
	windowRect.bottom =(long)height;//set bottom value to requested height

	/*      Fill out the window class structure   */
	windowClass.cbSize              = sizeof(WNDCLASSEX);
	windowClass.style               = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc         = WndProc;
	windowClass.cbClsExtra          = 0;
	windowClass.cbWndExtra          = 0;
	windowClass.hInstance           = hInstance;
	windowClass.hIcon               = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor             = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground       = NULL;
	windowClass.lpszMenuName        = NULL;
	windowClass.lpszClassName       = "MyClass";
	windowClass.hIconSm             = LoadIcon(NULL, IDI_WINLOGO);

	/*      Register window class        */
	if (!RegisterClassEx(&windowClass))
	{
			return 0;
	}

	/*      Check if fullscreen is on    */
	if (fullScreen)
	{
			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = width;   //screen width
			dmScreenSettings.dmPelsHeight = height; //screen height
			dmScreenSettings.dmBitsPerPel = bits;   //bits per pixel
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN !=
																DISP_CHANGE_SUCCESSFUL))
			{
					/*      Setting display mode failed, switch to windowed    */
					MessageBox(NULL, "Display mode failed", NULL, MB_OK);
					fullScreen = false;
			}
	}

	/*      Check if fullscreen is still on     */
	if (fullScreen)
	{
			dwExStyle = WS_EX_APPWINDOW;    //window extended style
			dwStyle = WS_POPUP;             //windows style
			ShowCursor(FALSE);              //hide mouse pointer
	}

	else
	{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; //window extended style
			dwStyle = WS_OVERLAPPEDWINDOW;                  //windows style
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	/*      Class registerd, so now create our window      */
	hwnd = CreateWindowEx(NULL, "MyClass",  //class name
												"OpenGL Robot",       //app name
												dwStyle |
												WS_CLIPCHILDREN |
												WS_CLIPSIBLINGS,
												0, 0,                         //x and y coords
												windowRect.right - windowRect.left,
												windowRect.bottom - windowRect.top,//width, height
												NULL,                 //handle to parent
												NULL,                 //handle to menu
												hInstance,            //application instance
												NULL);                //no xtra params

	/*      Check if window creation failed (hwnd = null ?)    */
	if (!hwnd)
	{
			return 0;
	}

	ShowWindow(hwnd, SW_SHOW);      //display window
	UpdateWindow(hwnd);             //update window

	done = false;   //initialize loop condition variable

	/* TEMPORARY - TEST TO RENDER A RANDOM MESH */
	Mesh* testModelPtr = NULL;
	StaticMesh* testModel = new StaticMesh();
	testModel->ReadModelFromFile("C:/Users/Sean/Downloads/table_lowpoly_x/table_lowpoly.bf");

	// Load .JPG From A File		(1st Texture)
	GLuint textureId = 0;
	int imageComponents = 0;
	int textureWidth = 0;
	int textureHeight = 0;
	stbi_uc* textureData = stbi_load("C:/Users/Sean/Downloads/table_lowpoly_x/planks02.jpg", &textureWidth, &textureHeight, &imageComponents, 3);
	//BuildTexture("", textureId);
	//return FALSE;													// Return False If Loading Failed

	/* END MESH INSTANTIATION */

	/*      Main message loop*/
	while (!done)
	{
		Sleep(15);   
		PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE);

		if (msg.message == WM_QUIT)     //did we receive a quit message?
		{
			done = true;
		}
		else
		{			
			
			Render(testModel, textureId, textureData, textureWidth, textureHeight, imageComponents);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (fullScreen)
	{
			ChangeDisplaySettings(NULL, 0);
			ShowCursor(TRUE);
	}

	return msg.wParam;
}