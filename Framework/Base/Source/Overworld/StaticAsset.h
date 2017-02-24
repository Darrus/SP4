#pragma once
#include "OverworldAsset.h"
class StaticAsset :
	public OverworldAsset
{
	float rotZ;

public:
	StaticAsset(const string& meshName);
	virtual ~StaticAsset();

	virtual void Render();
	inline void SetRotZ(float rotZ){ this->rotZ = rotZ; }
};

