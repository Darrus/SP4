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

	void AttackBarFill(double dt = 0.033f); ///< Fills Up the Attack Turn Bar of every entity that is in Battle. Stops filling when anyone is full.
    void PlayerCommand(/*Pass in the Entity here to access commands*/); ///< Basically a Popup when it's Player's Turn to Attack.

    BattleSystem stuff;

    BattleSystem* testingBattle;
    BattleEntity* testEntity;
    BattleEntity* testEntity2;

    ///< DEBUGGING STUFF -- Remove when complete
    // Enemy 1
    enum STATES
    {
        IDLE = 0,
        ATTACK,
        DEFEND,
        SKILL,
        PASS,
        DEAD
    };

    STATES state;
    Vector3 position_;
    int health_;        ///< Health of Unit
    int attack_;        ///< Attack of Unit
    int defense_;       ///< Defense of Unit
    float atkbar_;      ///< Current Attack Bar of Unit
    int fillrate;       ///< This is Speed. Will rename to speed
    //std::list<Skills*> skill_;
    void DetermineAction();

    // Enemy 2

    STATES state2;
    Vector3 position2_;
    int health2_;        ///< Health of Unit
    int attack2_;        ///< Attack of Unit
    int defense2_;       ///< Defense of Unit
    float atkbar2_;      ///< Current Attack Bar of Unit
    int fillrate2;       ///< This is Speed. Will rename to speed
    //std::list<Skills*> skill_;
    void DetermineAction2();

private:
	FPSCamera camera;
	SpriteEntity* BattleStateBackground;
	Entity2D entity;
    bool turnbarfill; ///< Sets to check if everyone's Bar should start to fill or not.
    SpriteEntity* CommandBox;
    SpriteEntity* TestEnemy, *TestEnemy2;

    bool encounter;
};

#endif /* BATTLESTATE_H */