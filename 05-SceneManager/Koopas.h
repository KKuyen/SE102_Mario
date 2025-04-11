#pragma once
#include "GameObject.h"
#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_SHELL 16

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_WALKING_RIGHT 101
#define KOOPAS_STATE_SHELL 200
#define KOOPAS_STATE_SHELL_MOVING 300

#define ID_ANI_KOOPAS_WALKING 6000
#define ID_ANI_KOOPAS_WALKING_RIGHT 6003
#define ID_ANI_KOOPAS_SHELL 6001
#define ID_ANI_KOOPAS_SHELL_MOVING 6002
class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	int nx;
	CKoopas(float x, float y);
	virtual void SetState(int state);
};