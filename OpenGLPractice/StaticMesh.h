
#include "Mesh.h"

#ifndef STATIC_MESH_H
#define STATIC_MESH_H
class StaticMesh :
	public Mesh
{
private:
	Vector3d*	vertices;
	faceVertexList*	faceList;
	//vector2d*			textureCoordinateList;
	Vector2d*	textureCoordinatesList;

public:
	StaticMesh(void);
	~StaticMesh(void);

	int ReadModelFromFile(char* filepath);
	void DeleteModel(void);
	void Render(void);
	void ProcessFileFlags(int flags, ifstream* binaryFileHandle);
	void ProcessFileSection(int sectionId, ifstream* binaryFileHandle);
};

#endif