#ifndef BATTLESTATE_H
#define BATTLESTATE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../FPSCamera.h"
#include "../Entity/SpriteEntity.h"
#include "../Entity/Entity2D.h"
#include "timer.h"

#include "../Battle/BattleSystem.h"
#include "../Entity/BattleEntity.h"
#include "..\Player\Player.h"
#include "..\Battle\MonsterFactory.h"

class SceneManager;
class TextEntity;

class CBattleState : public Scene, public BattleSystem
{
public:
	CBattleState();
	~CBattleState();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

    virtual void UnPause();

	void AttackBarFill(double dt = 0.033f); ///< Fills Up the Attack Turn Bar of every entity that is in Battle. Stops filling when anyone is full.
    void PlayerCommand(/*Pass in the Entity here to access commands*/); ///< Basically a Popup when it's Player's Turn to Attack.

    BattleSystem stuff;

    BattleSystem* testingBattle;
    BattleEntity* testEntity;
    BattleEntity* testEntity2;
    BattleEntity* wow;
    BattleEntity* wow2;

    CharacterInfo* charahehe;
    EnemyInfo* enemyhehe;

private:
	FPSCamera camera;
	SpriteEntity* BattleStateBackground;
	Entity2D entity;
    SpriteEntity* CommandBox;

    bool encounter;
    PartySystem* party;
    MonsterFactory* efactory;
};

#endif /* BATTLESTATE_H */