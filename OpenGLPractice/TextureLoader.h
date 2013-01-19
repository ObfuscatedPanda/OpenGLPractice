#pragma once
#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H
#include "ProgramObject.h"

#include <windows.h>	// Header File For Windows
#include <olectl.h>	// Header File For The OLE Controls Library
#include <math.h>	// Header File For The Math Library

#include <gl/gl.h>
#include <gl/glu.h>
int BuildTexture(char *szPathName, GLuint &texid);
	





class TextureLoader :
	public ProgramObject
{
public:
	TextureLoader(void);
	~TextureLoader(void);
};

#endif