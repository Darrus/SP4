#include <iostream>
#include "AnimationsContainer.h"

AnimationsContainer::AnimationsContainer()
{
}


AnimationsContainer::~AnimationsContainer()
{
	AnimMap::iterator it = container.begin();
	while (it != container.end())
	{
		it = container.erase(it);
	}
}

void AnimationsContainer::AddAnimation(string name, Animation* anim)
{
	AnimMap::iterator it = container.find(name);
	if (it != container.end())
	{
		std::cout << "Unable to add animation " << name << ". Already exist." << std::endl;
		delete anim;
		return;
	}

	container.insert(std::make_pair(name, anim));
}

void AnimationsContainer::AddAnimation(string name, string meshName, int startFrame, int endFrame, float playTime, int repeatcount)
{
	AnimMap::iterator it = container.find(name);
	if (it != container.end())
	{
		std::cout << "Unable to add animation " << name << ". Already exist." << std::endl;
		return;
	}

	Animation* anim = new Animation(meshName, startFrame, endFrame, playTime, repeatcount);
	container.insert(std::make_pair(name, anim));
}

void AnimationsContainer::RemoveAnimation(string name)
{
	AnimMap::iterator it = container.find(name);
	delete it->second;
	container.erase(it);
}

Animation* AnimationsContainer::GetAnimation(string name)
{
	AnimMap::iterator it = container.find(name);
	if (it != container.end())
		return (it)->second;
	else
	{
		std::cout << it->first << " animation does not exist." << std::endl;
		return nullptr;
	}
}
