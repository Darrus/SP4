#include "Animation.h"

#include "timer.h"
#include "MyMath.h"
#include "MeshBuilder.h"


Animation::Animation(string meshName, int startFrame, int endFrame, float playTime, int repeatCount) :
startFrame(startFrame), 
endFrame(endFrame), 
currentFrame(startFrame),
playTime(playTime),
currentTime(0.f),
repeatCount(repeatCount),
playCount(0),
active(true)
{
	spriteSheet = MeshBuilder::GetInstance()->GetMesh(meshName);
}


Animation::~Animation()
{
}

void Animation::Update()
{
	if (active)
	{
		float dt = (float)StopWatch::GetInstance()->GetDeltaTime();
		currentTime += dt;
		if (currentTime >= playTime)
		{
			if (repeatCount > 0 && playCount != repeatCount)
			{
				playCount++;
				currentTime = 0.f;
			}
			else if (repeatCount < 0)
				currentTime = 0.f;
			else
			{
				currentTime = 0.f;
				playCount = 0;
				active = false;
			}
		}

		int numOfFrame = endFrame - startFrame;
		int frame = numOfFrame * (currentTime / playTime);

		currentFrame = Math::Min(endFrame, startFrame + frame);
	}
}