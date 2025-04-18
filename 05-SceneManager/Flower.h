#pragma once
#include "GameObject.h"
#include "Mario.h"
#define FLOWER_POP_UP_SPEED 0.03f
#define FLOWER_POP_UP_HEIGHT 32

#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 32

#define FLOWER_STATE_LEFT_POP_UP 100
#define FLOWER_STATE_LEFT_POP_DOWN 200
#define FLOWER_STATE_LEFT_UP_FIRE 300
#define FLOWER_STATE_LEFT_DOWN_FIRE 350
#define FLOWER_STATE_RIGHT_POP_UP 400
#define FLOWER_STATE_RIGHT_POP_DOWN 500
#define FLOWER_STATE_RIGHT_UP_FIRE 600
#define FLOWER_STATE_RIGHT_DOWN_FIRE 650



#define ID_FLOWER_TURN_LEFT_ANI 130001
#define ID_FLOWER_TURN_RIGHT_ANI 130004
#define ID_FLOWER_LEFT_UP_FIRE_SPRITE 130002
#define ID_FLOWER_LEFT_DOWN_FIRE_SPRITE 130003
#define ID_FLOWER_RIGHT_UP_FIRE_SPRITE 130005
#define ID_FLOWER_RIGHT_DOWN_FIRE_SPRITE 130006

#define TOO_FAR 1
#define IN_RANGE 2
#define TOO_CLOSE 3

class CFlower : public CGameObject
{
protected:
	int initY;
	DWORD start;
	CMario* mario; 
	bool isFired;
	int isMarioInRange;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }

public:
	CFlower(float x, float y) :CGameObject(x, y) {
		initY = y;
		start = 0;
		mario = nullptr;
		isFired = false;
		isMarioInRange = TOO_FAR;
	}
	void SetMario(CMario* m) { mario = m; } 
};