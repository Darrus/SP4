#include "Animator.h"
#include "RenderHelper.h"
#include "timer.h"
#include "MyMath.h"

#include "AnimationsContainer.h"

Animator::Animator() :
currentFrame(0),
currentTime(0.f),
playCount(0),
isDone(false)
{
}


Animator::~Animator()
{
	
}

void Animator::Update()
{
	if (activeAnim && !isDone)
	{
		float dt = (float)StopWatch::GetInstance()->GetDeltaTime();
		currentTime += dt;
		if (currentTime >= activeAnim->playTime)
		{
			if (activeAnim->repeatCount > 0 && playCount != activeAnim->repeatCount)
			{
				playCount++;
				currentTime = 0.f;
			}
			else if (activeAnim->repeatCount < 0)
				currentTime = 0.f;
			else
			{
				currentTime = 0.f;
				playCount = 0;
				isDone = true;
			}
		}

		int numOfFrame = activeAnim->endFrame - activeAnim->startFrame;
		int frame = numOfFrame * (currentTime / activeAnim->playTime);

		currentFrame = Math::Min(activeAnim->endFrame, activeAnim->startFrame + frame);
	}
}

void Animator::Render()
{
	RenderHelper::RenderSprite(activeAnim->spriteSheet, currentFrame);
}

void Animator::AddAnimation(string name)
{
	Animation* anim = AnimationsContainer::GetInstance()->GetAnimation(name);
	if (anim)
		animations.insert(std::make_pair(name, anim));
}

void Animator::RemoveAnimation(string name)
{
	AnimMap::iterator it = animations.find(name);
	animations.erase(it);
}

void Animator::PlayAnimation(string name)
{
	activeAnim = animations.find(name)->second;
	Reset();
}

void Animator::Reset()
{
	currentFrame = activeAnim->startFrame;
	currentTime = 0.f;
	isDone = false;
	playCount = 0;
}