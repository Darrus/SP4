#pragma once

#include <SingletonTemplate.h>
#include <map>
#include <string>

#include "Animation.h"

using std::map;
using std::string;

typedef map<string, Animation*> AnimMap;

class AnimationsContainer : public Singleton<AnimationsContainer>
{
	friend Singleton<AnimationsContainer>;
private:
	AnimMap container;

public:
	AnimationsContainer();
	~AnimationsContainer();

	void AddAnimation(string name, Animation* anim);
	void AddAnimation(string name, string meshName, int startFrame, int endFrame, float playTime, int repeatcount = 0);
	void RemoveAnimation(string name);

	Animation* GetAnimation(string name);
};

