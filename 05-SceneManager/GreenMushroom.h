#pragma once
#pragma once
#include "GameObject.h"
#include "Mario.h"

#define GREEN_MUSHROOM_GRAVITY 0.0002f
#define GREEN_MUSHROOM_WALKING_SPEED 0.06f
#define GREEN_MUSHROOM_POP_UP_SPEED 0.03f


#define GREEN_MUSHROOM_BBOX_WIDTH 16
#define GREEN_MUSHROOM_BBOX_HEIGHT 16

#define GREEN_MUSHROOM_STATE_WALKING 100
#define GREEN_MUSHROOM_STATE_EATEN 200
#define GREEN_MUSHROOM_STATE_POP_UP 300

#define ID_GREEN_MUSHROOM_SPRITE 110001

class CGreenMushroom : public CGameObject
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
	CGreenMushroom(float x, float y, CMario* mario) :CGameObject(x, y) {
		this->mario = mario;
		this->ax = 0;
		this->ay = 0;
		this->initY = y;
		SetState(GREEN_MUSHROOM_STATE_POP_UP);
	}
};