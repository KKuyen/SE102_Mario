#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BREAKABLE_BRICK 14000
#define ID_ANI_BREAKABLE_BRICK_BREAK 14100
#define ID_ANI_BREAKABLE_BRICK_BREAK_2 14200
#define BREAKABLE_BRICK_WIDTH 16
#define BREAKABLE_BRICK_BBOX_WIDTH 16
#define BREAKABLE_BRICK_BBOX_HEIGHT 16

#define BREAKABLE_BRICK_STATE_NORMAL 100
#define BREAKABLE_BRICK_STATE_BREAK 200

class CBreakableBrick : public CGameObject {
protected:
	int state;

public:
	CBreakableBrick(float x, float y) : CGameObject(x, y) { state = BREAKABLE_BRICK_STATE_NORMAL; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);
	int IsCollidable() { return state == BREAKABLE_BRICK_STATE_NORMAL; }
	int IsBlocking() { return state == BREAKABLE_BRICK_STATE_NORMAL; }

	void OnCollisionWith(LPCOLLISIONEVENT e);
};