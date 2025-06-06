﻿#pragma once
#pragma once
#include "GameObject.h"
#include "Mario.h"
#define WINGED_KOOPAS_GRAVITY 0.00055f
#define WINGED_KOOPAS_GRAVITY_FALL 0.001f
#define WINGED_KOOPAS_WALKING_SPEED 0.06f
#define WINGED_KOOPAS_SHELL_MOVING_SPEED 0.2f
#define WINGED_KOOPAS_JUMP_SPEED -0.155f
#define WINGED_KOOPAS_FALL_SPEED -0.23f
#define WINGED_KOOPAS_FALL_SPEED_HORIZONTAL 0.2f
#define WINGED_KOOPAS_BBOX_WIDTH 16
#define WINGED_KOOPAS_BBOX_HEIGHT 24
#define WINGED_KOOPAS_BBOX_HEIGHT_SHELL 12

#define WINGED_KOOPAS_ACTIVATION_DISTANCE 100.0f // Distance at which Koopas activates
#define WINGED_KOOPAS_STATE_INACTIVE 50
#define WINGED_KOOPAS_STATE_WALKING 100
#define WINGED_KOOPAS_STATE_WALKING_RIGHT 101
#define WINGED_KOOPAS_STATE_SHELL 200
#define WINGED_KOOPAS_STATE_SHELL_MOVING 300
#define WINGED_KOOPAS_STATE_HELD 202
#define WINGED_KOOPAS_STATE_FALL 203


#define WINGED_KOOPAS_STATE_REVERSE 204


#define ID_ANI_WINGED_KOOPAS_WALKING 6000
#define ID_ANI_WINGED_KOOPAS_WALKING_RIGHT 6003
#define ID_ANI_WINGED_KOOPAS_SHELL 6001
#define ID_ANI_WINGED_KOOPAS_SHELL_MOVING 6002
#define ID_ANI_WINGED_KOOPAS_FALL 6004
#define ID_ANI_WINGED_KOOPAS_GREEN_WALKING 7000
#define ID_ANI_WINGED_KOOPAS_GREEN_WALKING_RIGHT 7003
#define ID_ANI_WINGED_KOOPAS_GREEN_SHELL 7001
#define ID_ANI_WINGED_KOOPAS_GREEN_SHELL_MOVING 7002
#define ID_ANI_WINGED_KOOPAS_GREEN_SHELL_MOVING_REVERSE 7012
#define ID_ANI_WINGED_KOOPAS_GREEN_FALL 7004
#define WINGED_KOOPAS_REVIVE_TIME 4000 
class CWingedKoopas : public CGameObject
{
protected:

	ULONGLONG revive_start; // Thời điểm bắt đầu đếm để hồi sinh

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() {
		return state != WINGED_KOOPAS_STATE_HELD && state != WINGED_KOOPAS_STATE_FALL;
	}
	virtual int IsBlocking() { return state == WINGED_KOOPAS_STATE_SHELL_MOVING; }

	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void StartReviveTimer() { if(revive_start==0) revive_start = GetTickCount64(); }
public:

	float lastShakeOffset; // Track previous shaking offset
	int shakeFrameCounter;
	bool isReverse;
	float ax;
	float ay;
	int nx;
	bool beforeLand;
	bool canFly;
	int level;

	CMario* mario;
	CWingedKoopas(float x, float y, bool canFly=true);
	virtual void SetState(int state);
};