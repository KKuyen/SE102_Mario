#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Brick.h"
#include "PlayScene.h"
#include "debug.h"
#define ONE_SEC 1000
#define INIT_LIFES 4
#define INIT_TIMER 300


class CGameManager : public CGameObject {
protected:
	static CGameManager* __instance;
public:
	int points;
	int timer;
	int lifes;
	int coins;
	float elapsedTime;
	int energy;

 	static CGameManager* GetInstance();
	CGameManager(float x = 0, float y = 0) : CGameObject(x, y)
	{
		points = coins = 0;
		timer = INIT_TIMER;
		elapsedTime = 0;
 		lifes = INIT_LIFES;
		energy = 0;
	}
	void Render() {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
 
			elapsedTime += dt;

			if (elapsedTime >= ONE_SEC && timer >= 0)
			{
				//DebugOut(L"++ Timer\n");
				timer--;  
				elapsedTime -= ONE_SEC;
			}
		 
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking() { return 0; }
};
