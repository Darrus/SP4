#ifndef LIGHT_H
#define LIGHT_H

#include "LightBase.h"

#include "Vertex.h"
#include "Vector3.h"
#include <string>

class Light : public LightBase
{
public:
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};

	LIGHT_TYPE type;
	Position position;
	Color color;
	float power;
	float kC;
	float kL;
	float kQ;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
	std::string name;

	virtual void Update(double _dt);
	virtual void UpdateUniforms();

	Light();
	virtual ~Light();
};

#endif