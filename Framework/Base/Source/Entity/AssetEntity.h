#ifndef ASSET_ENTITY_H
#define ASSET_ENTITY_H

#include "EntityBase.h"

class AssetEntity : public EntityBase
{
public:
	AssetEntity();
	virtual ~AssetEntity();

	virtual void Update();
	virtual void Render();
	virtual void RenderUI();
};

#endif