#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BULLET 150000

#define BULLET_BBOX_WIDTH 6
#define BULLET_BBOX_HEIGHT 6

#define BULLET_TIMEOUT 10000
#define BULLET_V 0.06f

class CBullet : public CGameObject {
private:
	ULONGLONG fire_start;
public:
	CBullet(float x, float y, float marioX, float marioY) : CGameObject(x, y)
	{
		SetUpAngle(marioX, marioY);
		fire_start = GetTickCount64();
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	void SetUpAngle(float marioX, float marioY);
};