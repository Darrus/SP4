#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <map>
#include "Animation.h"

using std::map;
typedef map<string, Animation*> AnimMap;

class Animator
{
	AnimMap animations;
	Animation* activeAnim;

public:
	Animator();
	~Animator();

	void Update();
	void Render();

	void AddAnimation(string name, Animation* anim);
	void AddAnimation(string name, string meshName, int startFrame, int endFrame, float playTime, int repeatcount = 0);
	void RemoveAnimation(string name);
	void PlayAnimation(string name);
};

#endif

