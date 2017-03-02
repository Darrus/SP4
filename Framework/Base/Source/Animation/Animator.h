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
	inline int GetAnimatorSize(){ return animations.size(); }
	inline AnimMap GetAnimations() { return animations; }
	
	// Remove animation from the animator
	void RemoveAnimation(string name);
	// Plays selected animation and resets the previous
	void PlayAnimation(string name);
	// Copy animations from another animator
	void CopyAnimator(Animator& anim);

};

#endif

