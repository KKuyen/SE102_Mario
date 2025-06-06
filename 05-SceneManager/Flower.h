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
#define ID_FLOWER_GREEN_TURN_LEFT_ANI 140001
#define ID_FLOWER_GREEN_TURN_RIGHT_ANI 140004
#define ID_FLOWER_LEFT_UP_FIRE_SPRITE 130002
#define ID_FLOWER_LEFT_DOWN_FIRE_SPRITE 130003
#define ID_FLOWER_RIGHT_UP_FIRE_SPRITE 130005
#define ID_FLOWER_RIGHT_DOWN_FIRE_SPRITE 130006
#define ID_FLOWER_GREEN_LEFT_UP_FIRE_SPRITE 140002
#define ID_FLOWER_GREEN_LEFT_DOWN_FIRE_SPRITE 140003
#define ID_FLOWER_GREEN_RIGHT_UP_FIRE_SPRITE 140005
#define ID_FLOWER_GREEN_RIGHT_DOWN_FIRE_SPRITE 140006

#define TOO_FAR 1
#define IN_RANGE 2
#define TOO_CLOSE 3

#define FIRE_DOWN_ZONE_Y 110
#define FIRE_LEFT_ZONE_X 240
#define FIRE_RIGHT_ZONE_X 500

#define FIRE_LEFT_ZONE_X2 1744
#define FIRE_RIGHT_ZONE_X2 2004

#define LEFT_EDGE_X1 352
#define RIGHT_EDGE_X1 384
#define LEFT_EDGE_X2 1856
#define RIGHT_EDGE_X2 1887

#define PAUSE_TIME 1700
#define FIRE_TIME 1000

#include "debug.h"

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
	int color;
	CFlower(float x, float y, int color) :CGameObject(x, y) {
		initY = y;
		start = 0;
		mario = nullptr;
		isFired = false;
		isMarioInRange = TOO_FAR;
		this->color = color;

	}
	void SetMario(CMario* m) { mario = m; } 
};