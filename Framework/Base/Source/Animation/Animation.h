#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

using std::string;

class Mesh;

struct Animation
{
	Animation(string meshName, int startFrame, int endFrame, float playTime, int repeatCount = 0);
	~Animation();

	Mesh* spriteSheet;
	float playTime;
	int startFrame;
	int endFrame;
	int repeatCount;
};

#endif