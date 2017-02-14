#ifndef SPRITE_ENTITY_H
#define SPRITE_ENTITY_H

#include "EntityBase.h"
#include "Vector3.h"
#include "Vertex.h"
#include <string>

class Mesh;

class SpriteEntity : public EntityBase
{
public:
	enum SPRITE_RENDERMODE
	{
		MODE_2D,
		MODE_3D,
		NUM_MODE
	};

	SpriteEntity(Mesh* _modelMesh);
	virtual ~SpriteEntity();

	virtual void Update(double _dt);
	virtual void Render();
	virtual void RenderUI();

	inline void SetPosition(const Vector3& _value){ position = _value; };
	inline Vector3 GetPosition(){ return position; };

	inline void SetScale(const Vector3& _value){ scale = _value; };
	inline Vector3 GetScale(){ return scale; };

	inline void SetTextRenderMode(SPRITE_RENDERMODE _mode){ mode = _mode; };

private:
	Vector3 position;
	Vector3 scale;
	Mesh* modelMesh;
	SPRITE_RENDERMODE mode;
};

#endif // SPRITE_ENTITY_H