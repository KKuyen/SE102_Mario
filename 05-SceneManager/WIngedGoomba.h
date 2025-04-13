﻿#pragma once
#include "GameObject.h"

#define WINGED_GOOMBA_GRAVITY 0.002f
#define WINGED_GOOMBA_WALKING_SPEED 0.05f
#define WINGED_GOOMBA_JUMP_SPEED_Y 0.3f 
#define WINGED_GOOMBA_JUMP_INTERVAL 1500

#define WINGED_GOOMBA_BBOX_WIDTH 16
#define WINGED_GOOMBA_BBOX_HEIGHT 14
#define WINGED_GOOMBA_BBOX_HEIGHT_DIE 8


#define WINGED_GOOMBA_DIE_TIMEOUT 500

#define WINGED_GOOMBA_STATE_WALKING 100
#define WINGED_GOOMBA_STATE_DIE 200
#define WINGED_GOOMBA_STATE_FLYING 300 

#define ID_ANI_WINGED_GOOMBA_WALKING 8000
#define ID_ANI_WINGED_GOOMBA_DIE 8001
#define ID_ANI_WINGED_GOOMBA_FLYING 8002
#define ID_ANI_WINGED_GOOMBA_FLYING_LEFT 8003

class CWingedGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;
	ULONGLONG jump_start;
	bool isJumping;


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CWingedGoomba(float x, float y);
	virtual void SetState(int state);
};