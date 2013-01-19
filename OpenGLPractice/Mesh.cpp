#include "Mesh.h"


Mesh::Mesh(void)
{
	sectionsInFile					= 0;	//
	verticesSectionStart			= 0;	//
	facesSectionStart				= 0;	//
	textureCoordinatesSectionStart	= 0;	//
	bSafeForRendering				= false;//
	verticesSectionSize				= 0;
	facesSectionSize				= 0;
	textureCoordinatesSectionSize	= 0;

	//
	sections[0]		= &verticesSectionStart;
	sections[1]		= &facesSectionStart;
	sections[2]		= &textureCoordinatesSectionStart;

	//
	sectionSizes[0]	= &verticesSectionSize;
	sectionSizes[1]	= &facesSectionSize;
	sectionSizes[2] = &textureCoordinatesSectionSize;
}


Mesh::~Mesh(void)
{
}
