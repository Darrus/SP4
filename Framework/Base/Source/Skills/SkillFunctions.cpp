#include "SkillFunctions.h"
#include "Skill.cpp"
#include "GL\glew.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

SkillContainer::SkillContainer()
{
	
}

SkillContainer::~SkillContainer()
{
	SkillMap::iterator it = m_skill_container.begin();
	while (it != m_skill_container.end())
		it = m_skill_container.erase(it);
}

void SkillContainer::Init()
{
	MeshBuilder::GetInstance()->GenerateQuad("skill_1", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_1.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_2", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_2.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_3", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_3.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_4", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_4.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_5", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_5.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_6", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_6.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_7", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_7.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_8", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_8.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_9", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_9.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_10", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_10.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_11", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_11.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_12", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_12.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_13", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_13.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_14", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_14.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_15", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_15.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_16", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_16.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_17", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_17.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_18", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_18.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_19", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_19.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skill_20", Color(1, 1, 1), 1.f)->textureID = LoadTGA("Image//Skills//skill_20.tga");
	
	Heal* heal = new Heal();
	m_skill_container.insert(std::make_pair(heal->GetName(), heal));
    Curate* curate = new Curate();
    m_skill_container.insert(std::make_pair(curate->GetName(), curate));
    HeroMaker* hero = new HeroMaker();
    m_skill_container.insert(std::make_pair(hero->GetName(), hero));
    Charisma* charisma = new Charisma();
    m_skill_container.insert(std::make_pair(charisma->GetName(), charisma));
    Illusion* illusion = new Illusion();
    m_skill_container.insert(std::make_pair(illusion->GetName(), illusion));

	//Can u pls
	ATKBoost* gji = new ATKBoost();
	m_skill_container.insert(std::make_pair(gji->GetName(), gji));

	Sabotage* asd = new Sabotage();
	m_skill_container.insert(std::make_pair(asd->GetName(), asd));

    Thrust* thrust = new Thrust();
    m_skill_container.insert(std::make_pair(thrust->GetName(), thrust));
    Sweep* sweep = new Sweep();
    m_skill_container.insert(std::make_pair(sweep->GetName(), sweep));
    Feint* feint = new Feint();
    m_skill_container.insert(std::make_pair(feint->GetName(), feint));
    SpeedBoost* speedboost = new SpeedBoost();
    m_skill_container.insert(std::make_pair(speedboost->GetName(), speedboost));
    PowerThrust* powerthrust = new PowerThrust();
    m_skill_container.insert(std::make_pair(powerthrust->GetName(), powerthrust));


    FireBlast* blast = new FireBlast();
    m_skill_container.insert(std::make_pair(blast->GetName(), blast));
    Firaga* firaga = new Firaga();
    m_skill_container.insert(std::make_pair(firaga->GetName(), firaga));
    IceBlast* iceblast = new IceBlast();
    m_skill_container.insert(std::make_pair(iceblast->GetName(), iceblast));
    Blizzaga* blizzaga = new Blizzaga();
    m_skill_container.insert(std::make_pair(blizzaga->GetName(), blizzaga));
    BliFirga* blifirga = new BliFirga();
    m_skill_container.insert(std::make_pair(blifirga->GetName(), blifirga));
}

Skill* SkillContainer::GetSkill(string name)
{
	SkillMap::iterator it = m_skill_container.find(name);
	if (it != m_skill_container.end())
		return (it)->second;
	else
		return nullptr;
}