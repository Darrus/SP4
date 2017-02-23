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

	// size is included for completeness. we assume that the mesh has a size of 1.0X1.0 square units
	// use scale to change the ground texture sizes
	inline void SetSize(const Vector3& _value) { size = _value; };
	inline Vector3 GetSize(){ return size; };

	Vector3 GetBoundary(void);

	void SetMesh(const int _side, Mesh* _modelMesh);

private:
	Vector3 size, boundary;
	bool m_bBoundaryDefined;
	Mesh* modelMesh[6];
};

#endif // SKYBOX_ENTITY_H