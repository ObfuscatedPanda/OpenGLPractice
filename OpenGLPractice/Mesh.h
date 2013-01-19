#pragma once
#include "Entity.h"

#include "Vector3d.h"
#include "Vector2d.h"

#ifndef MESH_H
#define MESH_H
#define VERTS_PER_POLYGON 3

// DEFINES FOR BINARY FILE FLAGS FOR MODELS
#define VERTICES_SECTION            0x1
#define VERTICES_INDEX				0
#define FACES_SECTION	            0x2
#define FACES_INDEX					1
#define TEXTURE_COORDINATES_SECTION 0x4
#define TEXTURE_COORDINATES_INDEX	2

#define SUPPORTED_NUMBER_OF_FILE_FLAGS 3

typedef struct Polygon_struct
{
	Vector3d vertices[VERTS_PER_POLYGON];
}polygon;

typedef struct Polygon_face_vertex_list_struct
{
	int verts[VERTS_PER_POLYGON];
}faceVertexList;

typedef struct Polygon_texture_map_struct
{
	Vector3d coordinates[VERTS_PER_POLYGON];
}textureCoordinates;

class Mesh :
	public Entity
{
private:

	// Sections that can be found in our binary file format
	int verticesSectionStart;
	int facesSectionStart;
	int textureCoordinatesSectionStart;
	int verticesSectionSize;
	int facesSectionSize;
	int textureCoordinatesSectionSize;
	bool bSafeForRendering;
	
protected:
	int* sections[SUPPORTED_NUMBER_OF_FILE_FLAGS];
	int* sectionSizes[SUPPORTED_NUMBER_OF_FILE_FLAGS];
	int  sectionsInFile;	
	inline void SetSafeForRendering(void) { bSafeForRendering = 1; }

public:
	Mesh(void);
	~Mesh(void);

	virtual int  ReadModelFromFile(char* filepath) = 0;
	virtual void DeleteModel(void) = 0;
	virtual void Render(void) = 0;
	virtual void ProcessFileFlags(int flags, ifstream* binaryFileHandle) = 0;
	inline  bool IsSafeForRendering(void) { return bSafeForRendering; }
};

#endif