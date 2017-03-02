#include "CharacterFactory.h"

// Graphics
#include "GL\glew.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

// Utility
#include "MyMath.h"
#include "MathUtility.h"

// Animation
#include "../Animation/AnimationsContainer.h"
#include "../Animation/Animation.h"

CharacterFactory::CharacterFactory()
{
	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Moogle", 1, 2)->textureID = LoadTGA("Image//moogle.tga");
	names.push_back("Moogle");
	AnimationsContainer::GetInstance()->AddAnimation("Moogle_walk_front", new Animation("Moogle", 0, 1, 1.f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Moogle_walk_left", new Animation("Moogle", 0, 1, 1.f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Moogle_walk_right", new Animation("Moogle", 0, 1, 1.f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Moogle_walk_down", new Animation("Moogle", 0, 1, 1.f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Moogle_idle", new Animation("Moogle", 0, 1, 1.f, -1.f));
}

CharacterFactory::~CharacterFactory()
{

}

CharacterInfo* CharacterFactory::CreateCharacter()
{
	Math::InitRNG();
	string name = names[Math::RandIntMinMax(0, names.size() - 1)];

	CharacterInfo* character = new CharacterInfo();
	character->stats.AddLevel(Math::RandIntMinMax(0, 20));
	character->name = name;
	character->anim.AddAnimation(name + "_walk_front");
	character->anim.AddAnimation(name + "_walk_left");
	character->anim.AddAnimation(name + "_walk_right");
	character->anim.AddAnimation(name + "_walk_down");
	character->anim.AddAnimation(name + "_idle");
	RandomStat(character);
	return character;
}

void CharacterFactory::RandomStat(CharacterInfo* character)
{
	int statPoint = character->stats.GetStatPoints();
	int stats[6] = { 0 };
	int sum = 0;
	Math::InitRNG();
	for (int i = 0; i < 6; ++i)
	{
		stats[i] = Math::RandIntMinMax(0, statPoint);
		sum += stats[i];
	}

	int container[6] = { 0 };
	int leftOver = 0;
	for (int i = 0; i < 6; ++i)
	{
		container[i] = (int)(((float)stats[i] / (float)sum) * (float)statPoint);
		leftOver += container[i];
	}
	leftOver = statPoint - leftOver;
	if (leftOver > 0)
	{
		container[5] += leftOver;
	}

	character->stats.AddStr(container[0]);
	character->stats.AddVit(container[1]);
	character->stats.AddInt(container[2]);
	character->stats.AddMind(container[3]);
	character->stats.AddDex(container[4]);
	character->stats.AddAgi(container[5]);
	character->stats.UpdateStats();
}