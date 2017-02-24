#ifndef SKYBOX_ENTITY_H
#define SKYBOX_ENTITY_H

#include "EntityBase.h"
#include "Vector3.h"
#include <string>

class Mesh;

class SkyBoxEntity : public EntityBase
{
public:
	enum SIDES
	{
		FRONT = 0,
		BACK,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
		NUM_SIDES
	};

	SkyBoxEntity(void);
	virtual ~SkyBoxEntity();

	virtual void Update(double _dt);
	virtual void Render();

	void SetMesh(const int _side, Mesh* _modelMesh);

private:
	Mesh* modelMesh[6];
};

#endif // SKYBOX_ENTITY_H