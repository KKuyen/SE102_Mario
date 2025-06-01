#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BREAKABLE_BRICK 14000
#define ID_ANI_BREAKABLE_BRICK_BREAK 14100
#define ID_ANI_BREAKABLE_BRICK_BREAK_2 14200
#define BREAKABLE_BRICK_WIDTH 1
#define BREAKABLE_BRICK_BBOX_WIDTH 15
#define BREAKABLE_BRICK_BBOX_HEIGHT 15

#define BREAKABLE_BRICK_STATE_NORMAL 100
#define BREAKABLE_BRICK_STATE_BREAK 200
#define BREAKABLE_BRICK_STATE_INVISIBLE 300

#define BREAKABLE_BRICK_STATE_COIN 455
#define COIN_STATE_TIMEOUT 5000
class CBreakableBrick : public CGameObject {
protected:
	

public:
	int state;
	ULONGLONG coin_state_start;
	int initx;
	int inity;
	CBreakableBrick(float x, float y) : CGameObject(x, y) {
		state = BREAKABLE_BRICK_STATE_NORMAL;
		initx = x;
		inity = y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void Upp(float& t);

	void SetState(int state);
	int IsCollidable() { return 1; }
	int IsBlocking() { return (state == BREAKABLE_BRICK_STATE_NORMAL); }

	void OnCollisionWith(LPCOLLISIONEVENT e);
};