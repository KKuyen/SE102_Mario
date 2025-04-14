#pragma once
#include "GameObject.h"

#define FLOWER_POP_UP_SPEED 0.03f
#define FLOWER_POP_UP_HEIGHT 32

#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 32

#define FLOWER_STATE_LEFT_POP_UP 100
#define FLOWER_STATE_LEFT_POP_DOWN 200
#define FLOWER_STATE_LEFT_FIRE 300
#define FLOWER_STATE_RIGHT_POP_UP 400
#define FLOWER_STATE_RIGHT_POP_DOWN 500
#define FLOWER_STATE_RIGHT_FIRE 600


#define ID_FLOWER_TURN_LEFT_ANI 130001
#define ID_FLOWER_TURN_RIGHT_ANI 130003
#define ID_FLOWER_TURN_LEFT_FIRE_SPRITE 130002
#define ID_FLOWER_TURN_RIGHT_FIRE_SPRITE 130004

class CFlower : public CGameObject
{
protected:
	int initY;
	DWORD start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	CFlower(float x, float y) :CGameObject(x, y) {
		initY = y;
		start = 0;
	}
};