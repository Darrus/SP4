#include "EnemyNPC.h"

#include "SceneManager.h"
#include "../Scenes/BattleState.h"
#include "../Overworld/Overworld.h"

EnemyNPC::EnemyNPC()
{
}


EnemyNPC::~EnemyNPC()
{
}

void EnemyNPC::Interact()
{
	CBattleState* scene = dynamic_cast<CBattleState*>(SceneManager::GetInstance()->SetActiveScene("BattleScene", true));
	if (scene)
	{
		scene->testingBattle->EnemyInfoList.clear();
        scene->testingBattle->EnemyList.clear();
        scene->testingBattle->BattleList.clear();
        scene->testingBattle->EnemyInfoList.push_back(scene->efactory->CreateBoss(4));
        scene->testingBattle->AssignEnemies();
        Overworld::battle = true;
	}
}
