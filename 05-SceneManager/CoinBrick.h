#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define BOX_WIDTH 16
#define BOX_BBOX_WIDTH 16
#define BOX_BBOX_HEIGHT 16
#define GIFTBOX_STATE_SHOWING 100
#define GIFTBOX_STATE_BOUNCE 200
#define GIFTBOX_STATE_HIDDEN 300
#define GIFTBOX_GRAVITY	0.002f
#define GIFTBOX_BOUNCE_SPEED 0.2f
#define SPRITE_ID_HIDDEN 90004
#define ANI 14000
#include "Mario.h"

class CCoinBrick : public CGameObject {
protected:
	int quantity;
	int currentQuantity;
	int initY;
	int isBoxHidden;
 public:

	CCoinBrick(float x, float y, int quantity);
	void Render();
	void OpenCoinBox();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};