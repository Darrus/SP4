#pragma once

#include "OverworldAsset.h"

class StaticAsset : public OverworldAsset
{
	float rotZ;
	Mesh* front;
	Mesh* side;

	Vector3 view;

public:
	StaticAsset(const string& frontMeshName, const string& sideMeshName);
	virtual ~StaticAsset();

	virtual void Update();
	virtual void Render();
	void SetRotZ(const float& rotZ);
};

