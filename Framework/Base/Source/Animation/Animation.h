#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

using std::string;

class Mesh;

class Animation
{
public:
	Animation(string meshName, int startFrame, int endFrame, float playTime, int repeatCount = 0);
	~Animation();

	void Update();

	inline Mesh* GetSprite(){ return spriteSheet; };
	inline int GetCurrentFrame() { return currentFrame; };
	inline void SetActive(bool active){ this->active = active; }

private:
	Mesh* spriteSheet;
	float playTime;
	float currentTime;

	int startFrame;
	int endFrame;
	int currentFrame;

	int playCount;
	int repeatCount;

	bool active;
};

#endif