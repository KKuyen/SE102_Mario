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



class CGiftBox : public CGameObject {
protected:
	int animationId;
	int initY;
	//0: coin, 1 : mushroom
	int type; 
	//0: Not hidden, 1: Hidden, 2: Null
	int isBoxHidden;
public:
 	CGiftBox(float x, float y, int animationId, int type);
	void Render();
	void Open();
	void OpenCoinBox();
	void OpenMushroomBox();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};