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
 	static CGameManager* GetInstance();
	CGameManager(float x = 0, float y = 0) : CGameObject(x, y)
	{
		points =   0;
	}
	void Render() {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
 
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking() { return 0; }
};
