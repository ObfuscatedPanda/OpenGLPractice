#include "StaticMesh.h"
#include <fstream>
#include "Vector.h"

// TODO: See Render
#include <gl/gl.h>
#include <gl/glu.h>

#define CHAR_BIT_COUNT			8
#define CHARS_PER_SCALAR			4
#define NUMBER_OF_DIMENSIONS	3
#define ORDINATES_PER_POLYGON	9
using namespace std;

#define BITS_PER_SCALAR 32
SCALAR reverse(SCALAR value)
{
	SCALAR reversedValue = 0;
	for (size_t i = 0; i < BITS_PER_SCALAR; ++i, value = ((int)value >> 1))
	reversedValue = ((int)reversedValue << 1) | ((int)value & 0x01);
	return reversedValue;
}

StaticMesh::StaticMesh(void)
{
	faceList						= null;
	textureCoordinatesList			= null;
	vertices						= null;
}


StaticMesh::~StaticMesh(void)
{
}


FILE *fp;

//if((fp=fopen("filename.whatever", "rb"))==NULL)
// return 0;

//fseek(fp, 0, SEEK_END);
//long size = ftell(fp);
//fseek(fp, 0, SEEK_SET);
//
//SCALAR *f = (SCALAR *)malloc(sizeof(SCALAR)*size);
//if(f==NULL)
//{
// fclose(fp);
// return 0;
//}
//
//if(fread(f, sizeof(SCALAR), size, fp)!=size)
//{
// fclose(fp);
// return 0;
//}
//
//fclose(fp);


int StaticMesh::ReadModelFromFile(char * filepath)
{
	if(!filepath)
	{
		return -1;
	}
	
	SCALAR SCALARFileFlags = 0;
	int fileFlags = 0;

	// 4 chars to make a SCALARing point number
	int polyCount = 0;

	ifstream binaryMeshFile (filepath, ios::in|ios::binary);
	int ordinateID = 0;	
	int polygonNumber	= 0;
	int vertexNumber	= 0;
    if(binaryMeshFile.is_open())
    {
		binaryMeshFile.seekg(0,ios::beg);
		binaryMeshFile.read((char*)&SCALARFileFlags,sizeof(SCALARFileFlags));
		fileFlags = (int)SCALARFileFlags;
		ProcessFileFlags(fileFlags, &binaryMeshFile);

		int sectionIndex = 0;
		if(-1 != *(sections[VERTICES_INDEX]))
		{
			ProcessFileSection(VERTICES_SECTION, &binaryMeshFile);
		}
		if(-1 != *(sections[FACES_INDEX]))
		{
			ProcessFileSection(FACES_SECTION, &binaryMeshFile);
		}
		if(-1 != *(sections[TEXTURE_COORDINATES_INDEX]))
		{
			ProcessFileSection(TEXTURE_COORDINATES_SECTION, &binaryMeshFile);
		}
		// Update the section sizes to be usable for our rendering thread - normalized to the number of
		// array indeces in the data structures
		//*(sectionSizes[VERTICES_INDEX]) /= 3;
		//*(sectionSizes[FACES_INDEX])	/= 3;
		//*(sectionSizes[TEXTURE_COORDINATES_INDEX])	/= 2;
		// We are safe for rendering after normalizing our array sizes
		SetSafeForRendering();
		// We need the number of texture coordinate entries to be equal to the number of vertices
		assert(*(sectionSizes[VERTICES_INDEX]) == *(sectionSizes[TEXTURE_COORDINATES_INDEX]));
		
        binaryMeshFile.close();
	}
    else
	{
		cout << "Unable to open file";
	}
    return 0;
}

void StaticMesh::DeleteModel()
{

}

// TODO: cleanup to so we have something more generic instead of so many conditional statements
void StaticMesh::ProcessFileSection(int sectionId, ifstream* binaryFileHandle)
{
	int* sectionSize	= null;
	int* sectionStart	= null;
	int sectionIndex	= 0;
	// point to the current section
	switch (sectionId)
	{
	case VERTICES_SECTION:
		assert(null == vertices);				// only operate on empty data structs
		sectionIndex = VERTICES_INDEX;
		break;	
	case FACES_SECTION:
		assert(null == faceList);				// only operate on empty data structs
		sectionIndex = FACES_INDEX;
		break;
	case TEXTURE_COORDINATES_SECTION:
		assert(null == textureCoordinatesList);	// only operate on empty data structs
		sectionIndex = TEXTURE_COORDINATES_INDEX;
		break;
	default:
		//Handed a sectionId that does not have an assignment
		assert(0);
	}
	sectionStart= sections[sectionIndex];
	sectionSize = sectionSizes[sectionIndex];
	SCALAR fSectionSize;
	// Go to the starting location of the section we are processing
	binaryFileHandle->seekg(ios::beg + (*sectionStart) * sizeof(char));
	// Read in the number of entries in this section
	binaryFileHandle->read((char*)&fSectionSize,sizeof(fSectionSize));
	
	// Allocate the data struct for this section
	
	int normalizedSectionSize = (int)fSectionSize;
	// TODO: change magic numbers to constants for values per section entry/index \
	// perhaps by having a header just for binary file defines?
	switch (sectionId)
	{
	case VERTICES_SECTION:
		// There shouldn't be any non-filler entries that are chopped off (i.e. only 0xFFFFFFFF can be chopped off)
		assert((normalizedSectionSize / 3) == (normalizedSectionSize  - (normalizedSectionSize % 3)) / 3);
		normalizedSectionSize /= 3;
		vertices = new Vector[normalizedSectionSize];
		break;	
	case FACES_SECTION:
		// There shouldn't be any non-filler entries that are chopped off (i.e. only 0xFFFFFFFF can be chopped off)
		assert((normalizedSectionSize / 3) == (normalizedSectionSize  - (normalizedSectionSize % 3)) / 3);
		normalizedSectionSize /= 3;
		faceList = new faceVertexList[normalizedSectionSize];
		break;
	case TEXTURE_COORDINATES_SECTION:
		// There shouldn't be any non-filler entries that are chopped off (i.e. only 0xFFFFFFFF can be chopped off)
		assert((normalizedSectionSize / 2) == (normalizedSectionSize  - (normalizedSectionSize % 2)) / 2);
		normalizedSectionSize /= 2;		
		textureCoordinatesList = new Vector2d[normalizedSectionSize];
		break;
	}
	*sectionSize = normalizedSectionSize;

	// Go to section start and advance to the word after the section size
	binaryFileHandle->seekg(ios::beg + *sectionStart + sizeof(*sectionSize));
	for(sectionIndex = 0; sectionIndex < normalizedSectionSize; sectionIndex++)
	{
		SCALAR ordinate = 0;
		switch (sectionId)
		{
		case VERTICES_SECTION:
			binaryFileHandle->read((char*)&ordinate,sizeof(ordinate));
			vertices[sectionIndex].SetX(ordinate);
			binaryFileHandle->read((char*)&ordinate,sizeof(ordinate));
			vertices[sectionIndex].SetY(ordinate);
			binaryFileHandle->read((char*)&ordinate,sizeof(ordinate));
			vertices[sectionIndex].SetZ(ordinate);
			break;	
		case FACES_SECTION:
			binaryFileHandle->read((char*)&ordinate,sizeof(ordinate));
			faceList[sectionIndex].verts[_X] = ordinate;
			binaryFileHandle->read((char*)&ordinate,sizeof(ordinate));
			faceList[sectionIndex].verts[_Y] = ordinate;
			binaryFileHandle->read((char*)&ordinate,sizeof(ordinate));
			faceList[sectionIndex].verts[_Z] = ordinate;
			break;
		case TEXTURE_COORDINATES_SECTION:
			binaryFileHandle->read((char*)&ordinate,sizeof(ordinate));
			textureCoordinatesList[sectionIndex].SetX(ordinate);
			binaryFileHandle->read((char*)&ordinate,sizeof(ordinate));
			textureCoordinatesList[sectionIndex].SetY(ordinate);
			break;
		}
	}
}

void StaticMesh::ProcessFileFlags(int flags, ifstream* binaryFileHandle)
{
	int flag;
	sectionsInFile = 0;
	for(flag = 0; flag < sizeof(int) && flag < SUPPORTED_NUMBER_OF_FILE_FLAGS; flag++)
	{
		// Is the flag asserted?
		if (1 == ((flags >> flag) & 0x1))
		{
			SCALAR fSectionStartLocation = 0;
			int   sectionStartLocation  = 0;
			sectionsInFile++;
			binaryFileHandle->seekg(ios::beg + (flag * sizeof(SCALAR)) + sizeof(SCALAR));//0,ios::beg + (flag * sizeof(SCALAR)));
			binaryFileHandle->read((char*)&fSectionStartLocation, sizeof(fSectionStartLocation));
			sectionStartLocation = (int)fSectionStartLocation;
			*(sections[flag]) = sectionStartLocation;
		}
		else
		{
			*(sections[flag]) = -1;
		}
	}
}


// TODO: move this to a rendering object ? Don't like the look of openGL API calls here
void StaticMesh::Render(void)
{
	// Iterate through each face and render it
	int polygonNumber = 0;
	for(; polygonNumber < *(sectionSizes[FACES_INDEX]); polygonNumber++)
	{
		glBegin(GL_POLYGON);
		int vertex = 0;
		for(; vertex < VERTS_PER_POLYGON; vertex++)
		{
			faceVertexList face = faceList[polygonNumber];
			glTexCoord2f(	textureCoordinatesList[face.verts[0]].X(),
							textureCoordinatesList[face.verts[0]].Y());
			glVertex3f(		vertices[face.verts[0]].X(),
							vertices[face.verts[0]].Y(), 
							vertices[face.verts[0]].Z());
			glTexCoord2f(	textureCoordinatesList[face.verts[1]].X(),
							textureCoordinatesList[face.verts[1]].Y());
			glVertex3f(		vertices[face.verts[1]].X(),
							vertices[face.verts[1]].Y(), 
							vertices[face.verts[1]].Z());
			glTexCoord2f(	textureCoordinatesList[face.verts[2]].X(),
							textureCoordinatesList[face.verts[2]].Y());
			glVertex3f(		vertices[face.verts[2]].X(),
							vertices[face.verts[2]].Y(), 
							vertices[face.verts[2]].Z());
		}
		glEnd();
	}
}