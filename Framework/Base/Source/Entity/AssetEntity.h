#ifndef ASSET_ENTITY_H
#define ASSET_ENTITY_H

#include <string>

#include "EntityBase.h"

using std::string;

class AssetEntity : public EntityBase
{
	Mesh* mesh;

public:
	AssetEntity(const string& meshName);
	virtual ~AssetEntity();

	virtual void Update();
	virtual void Render();
	virtual void RenderUI();
};

#endif