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

	float currentTime;
	int currentFrame;
	int playCount;
	bool isDone;

public:
	Animator();
	~Animator();

	void Update();
	void Render();

	void Reset();

	void AddAnimation(string name);

	inline int GetCurrentFrame() { return currentFrame; };
	inline int GetPlayCount() { return playCount; }
	inline bool GetDone() { return isDone; }

	// Remove animation from the animator
	void RemoveAnimation(string name);
	// Plays selected animation and resets the previous
	void PlayAnimation(string name);
};

#endif

