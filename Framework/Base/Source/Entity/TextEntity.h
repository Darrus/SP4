#ifndef TEXT_ENTITY_H
#define TEXT_ENTITY_H

#include "EntityBase.h"
#include "Vector3.h"
#include "Vertex.h"
#include <string>

class Mesh;

class TextEntity : public EntityBase
{
public:
	enum TEXT_RENDERMODE
	{
		MODE_2D,
		MODE_3D,
		NUM_MODE
	};

	TextEntity(Mesh* _modelMesh, const std::string& _text, const Color& _color);
	virtual ~TextEntity();

	virtual void Update(double _dt);
	virtual void Render();
	virtual void RenderUI();

	inline void SetPosition(const Vector3& _value){ position = _value; };
	inline Vector3 GetPosition(){ return position; };

	inline void SetScale(const Vector3& _value){ scale = _value; };
	inline Vector3 GetScale(){ return scale; };

	inline void SetText(const std::string& _text){ text = _text; };
	inline std::string GetText(){ return text; };

	inline void SetTextRenderMode(TEXT_RENDERMODE _mode){ mode = _mode; };
	inline void SetColor(const Color& _color){ color = _color; };

private:
	Vector3 position;
	Vector3 scale;
	Mesh* modelMesh;
	std::string text;
	TEXT_RENDERMODE mode;
	Color color;
};

namespace Create
{
	TextEntity* Text2DObject(const std::string& _meshName, const Vector3& _position, const std::string& _text, const Vector3& _scale, const Color& _color);
	TextEntity* Text3DObject(const std::string& _meshName, const Vector3& _position, const std::string& _text, const Vector3& _scale, const Color& _color);
};

#endif // TEXT_ENTITY_H