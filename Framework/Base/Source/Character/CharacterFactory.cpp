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

CharacterFactory::CharacterFactory() :
id(0)
{
	// Shadow
	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Shadow", 5, 4)->textureID = LoadTGA("Image//Characters//Shadow.tga");
	names.push_back("Shadow");
	AnimationsContainer::GetInstance()->AddAnimation("Shadow_walk_front", new Animation("Shadow", 0, 4, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Shadow_walk_back", new Animation("Shadow", 4, 8, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Shadow_walk_left", new Animation("Shadow", 8, 12, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Shadow_walk_right", new Animation("Shadow", 12, 16, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Shadow_idle_front", new Animation("Shadow", 16, 16, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Shadow_idle_back", new Animation("Shadow", 17, 17, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Shadow_idle_left", new Animation("Shadow", 18, 18, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Shadow_idle_right", new Animation("Shadow", 19, 19, 0.5f, -1.f));

	// Terra
	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Terra", 5, 4)->textureID = LoadTGA("Image//Characters//Terra.tga");
	names.push_back("Terra");
	AnimationsContainer::GetInstance()->AddAnimation("Terra_walk_front", new Animation("Terra", 0, 4, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Terra_walk_back", new Animation("Terra", 4, 8, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Terra_walk_left", new Animation("Terra", 8, 12, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Terra_walk_right", new Animation("Terra", 12, 16, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Terra_idle_front", new Animation("Terra", 16, 16, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Terra_idle_back", new Animation("Terra", 17, 17, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Terra_idle_left", new Animation("Terra", 18, 18, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Terra_idle_right", new Animation("Terra", 19, 19, 0.5f, -1.f));

	// Celes
	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Celes", 5, 4)->textureID = LoadTGA("Image//Characters//Celes.tga");
	names.push_back("Celes");
	AnimationsContainer::GetInstance()->AddAnimation("Celes_walk_front", new Animation("Celes", 0, 4, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Celes_walk_back", new Animation("Celes", 4, 8, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Celes_walk_left", new Animation("Celes", 8, 12, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Celes_walk_right", new Animation("Celes", 12, 16, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Celes_idle_front", new Animation("Celes", 16, 16, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Celes_idle_back", new Animation("Celes", 17, 17, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Celes_idle_left", new Animation("Celes", 18, 18, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Celes_idle_right", new Animation("Celes", 19, 19, 0.5f, -1.f));

	// Edgar
	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Edgar", 5, 4)->textureID = LoadTGA("Image//Characters//Edgar.tga");
	names.push_back("Edgar");
	AnimationsContainer::GetInstance()->AddAnimation("Edgar_walk_front", new Animation("Edgar", 0, 4, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Edgar_walk_back", new Animation("Edgar", 4, 8, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Edgar_walk_left", new Animation("Edgar", 8, 12, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Edgar_walk_right", new Animation("Edgar", 12, 16, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Edgar_idle_front", new Animation("Edgar", 16, 16, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Edgar_idle_back", new Animation("Edgar", 17, 17, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Edgar_idle_left", new Animation("Edgar", 18, 18, 0.5f, -1.f));
	AnimationsContainer::GetInstance()->AddAnimation("Edgar_idle_right", new Animation("Edgar", 19, 19, 0.5f, -1.f));
}

CharacterFactory::~CharacterFactory()
{

}

CharacterInfo* CharacterFactory::CreateCharacter()
{
	string name = names[Math::RandIntMinMax(0, names.size() - 1)];

	CharacterInfo* character = new CharacterInfo();
	character->stats.AddLevel(Math::RandIntMinMax(1, 100));
	character->name = name;
	character->anim.AddAnimation(name + "_walk_front");
	character->anim.AddAnimation(name + "_walk_back");
	character->anim.AddAnimation(name + "_walk_left");
	character->anim.AddAnimation(name + "_walk_right");
	character->anim.AddAnimation(name + "_idle_front");
	character->anim.AddAnimation(name + "_idle_back");
	character->anim.AddAnimation(name + "_idle_left");
	character->anim.AddAnimation(name + "_idle_right");
	character->anim.PlayAnimation(name + "_idle_front");
	character->id = GenerateID();
	RandomStat(character);
	return character;
}

CharacterInfo* CharacterFactory::GetCharacter(string name)
{
	CharacterInfo* character = new CharacterInfo();
	character->name = name;
	character->anim.AddAnimation(name + "_walk_front");
	character->anim.AddAnimation(name + "_walk_back");
	character->anim.AddAnimation(name + "_walk_left");
	character->anim.AddAnimation(name + "_walk_right");
	character->anim.AddAnimation(name + "_idle_front");
	character->anim.AddAnimation(name + "_idle_back");
	character->anim.AddAnimation(name + "_idle_left");
	character->anim.AddAnimation(name + "_idle_right");
	character->id = GenerateID();
	return character;
}

void CharacterFactory::RandomStat(CharacterInfo* character)
{
	int statPoint = character->stats.GetStatPoints();
	int stats[6] = { 0 };
	int sum = 0;
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
	character->HP = character->stats.GetMaxHP();
	character->MP = character->stats.GetMaxMP();
}