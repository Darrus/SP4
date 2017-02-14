#ifndef OBJ_MESH_H
#define OBJ_MESH_H

#include "Mesh.h"

class OBJMesh : public Mesh
{
public:
	OBJMesh(const std::string &meshName);
	~OBJMesh();
	void Render();

	unsigned texCoordBuffer;
	unsigned normalBuffer;
};

#endif