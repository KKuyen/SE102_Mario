#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.001f
#define MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_EATEN 200

#define ID_MUSHROOM_SPRITE 110000

class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 1; };
 	virtual int IsBlocking() { return 0; }
public:
	CMushroom(float x, float y) :CGameObject(x, y){
		vx =- MUSHROOM_WALKING_SPEED;
		this->ax = 0;
		this->ay = MUSHROOM_GRAVITY;
		SetState(MUSHROOM_STATE_WALKING);
	}
};