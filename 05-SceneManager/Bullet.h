#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BULLET 150000

#define BULLET_BBOX_WIDTH 6
#define BULLET_BBOX_HEIGHT 6

#define BULLET_TIMEOUT 10000
#define BULLET_V 0.06f
#define CONST180 180.0f
#define ANGLE_10 10
#define ANGLE_20 20
#define ANGLE_30 30
#define ANGLE_45 45
#define ANGLE_90 90
#define ANGLE_135 135
#define ANGLE_145 145
#define ANGLE_160 160
#define ANGLE_180 180



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