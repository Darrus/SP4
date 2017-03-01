#include "CharacterFactory.h"

// Graphics


void CharacterFactory::Init()
{
	 
}

CharacterInfo* CharacterFactory::CreateCharacter(string name)
{
	for (int i = 0; i < names.size(); ++i)
	{
		if (names[i] == name)
		{
			CharacterInfo* character = new CharacterInfo();
			character->name = name;
			character->anim.AddAnimation(name + "_walk_front");
			character->anim.AddAnimation(name + "_walk_left");
			character->anim.AddAnimation(name + "_walk_right");
			character->anim.AddAnimation(name + "_walk_down");
			character->anim.AddAnimation(name + "_idle");
			return character;
		}
	}
	return nullptr;
}
