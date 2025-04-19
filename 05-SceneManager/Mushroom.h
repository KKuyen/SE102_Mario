#pragma once
#include "GameObject.h"
#include "Mario.h"

#define MUSHROOM_GRAVITY 0.0002f
#define MUSHROOM_WALKING_SPEED 0.06f
#define MUSHROOM_POP_UP_SPEED 0.03f


#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_EATEN 200
#define MUSHROOM_STATE_POP_UP 300

#define ID_MUSHROOM_SPRITE 110000

class CMushroom : public CGameObject
{
protected:
	float ax;
	CMario* mario;
	float ay;
	int initY;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 1; };
 	virtual int IsBlocking() { return 0; }
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	virtual void SetState(int state);
	CMushroom(float x, float y, CMario* mario) :CGameObject(x, y){
		this->mario = mario;
 		this->ax = 0;
		this->ay = 0;
		this->initY = y;
		SetState(MUSHROOM_STATE_POP_UP);
	}
};