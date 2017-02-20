#include "Animation.h"

#include "timer.h"
#include "MyMath.h"
#include "MeshBuilder.h"


Animation::Animation(string meshName, int startFrame, int endFrame, float playTime, int repeatCount) :
startFrame(startFrame), 
endFrame(endFrame),
playTime(playTime),
repeatCount(repeatCount)
{
	spriteSheet = MeshBuilder::GetInstance()->GetMesh(meshName);
}


Animation::~Animation()
{
}