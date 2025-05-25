#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Brick.h"
#include "PlayScene.h"
#include "debug.h"


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
		timer = 300;
		elapsedTime = 0;
 		lifes = 4;
		energy = 6;
	}
	void Render() {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
 
			elapsedTime += dt;

			if (elapsedTime >= 1000 && timer >= 0)
			{
				//DebugOut(L"++ Timer\n");
				timer--;  
				elapsedTime -= 1000;  
			}
		 
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking() { return 0; }
};
