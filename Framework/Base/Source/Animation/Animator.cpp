#include "Animator.h"
#include "RenderHelper.h"

Animator::Animator()
{
}


Animator::~Animator()
{
	AnimMap::iterator it = animations.begin();
	while (it != animations.end())
	{
		delete it->second;
		it = animations.erase(it);
	}
}

void Animator::Update()
{
	if (activeAnim)
		activeAnim->Update();
}

void Animator::Render()
{
	RenderHelper::RenderSprite(activeAnim->GetSprite(), activeAnim->GetCurrentFrame());
}

void Animator::AddAnimation(string name, Animation* anim)
{
	animations.insert(std::make_pair(name, anim));
}

void Animator::AddAnimation(string name, string meshName, int startFrame, int endFrame, float playTime, int repeatcount)
{
	Animation* anim = new Animation(meshName, startFrame, endFrame, playTime, repeatcount);
	animations.insert(std::make_pair(name, anim));
}

void Animator::RemoveAnimation(string name)
{
	AnimMap::iterator it = animations.find(name);
	delete it->second;
	animations.erase(it);
}

void  Animator::PlayAnimation(string name)
{
	activeAnim = animations.find(name)->second;
	activeAnim->SetActive(true);
}
