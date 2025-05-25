#pragma once
#include "GameObject.h"
#include "Mario.h"
#define KOOPAS_GRAVITY 0.0002f
#define KOOPAS_GRAVITY_FALL 0.001f
#define KOOPAS_VERTICAL_MOVE_SPEED 0.02f
#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 25
#define MAX_VERTICAL_MOVE 180.0f
#define MIN_VERTICAL_MOVE 50.0f
#define KOOPAS_STATE_DOWN 204
#define KOOPAS_STATE_UP 205
 
#define ID_ANI_WINGED_RED_KOOPA	7005

class CWingedRedKoopa : public CGameObject
{
protected:

 

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
 public:
	float ax;
	float ay;
	int nx;
	int color;
 	CMario* mario;
	CWingedRedKoopa(float x, float y);
	virtual void SetState(int state);

};