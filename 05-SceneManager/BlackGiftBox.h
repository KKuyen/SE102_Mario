#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define GIFTBOX_WIDTH 16
#define GIFTBOX_BBOX_WIDTH 16
#define GIFTBOX_BBOX_HEIGHT 16

#define ID_ANI_MUSHROOM 370000
#define ID_ANI_STAR 372000
#define ID_ANI_FLOWERBLUE 372001

#define ID_ANI_MUSHROOM_EF 3710000
#define ID_ANI_FLOWER_EF 3710002
#define ID_ANI_STAR_EF 3710001


#define GIFTBOX_SPECIAL_STATE_MUSHROOM 0
#define GIFTBOX_SPECIAL_STATE_STAR 1
#define GIFTBOX_SPECIAL_STATE_FLOWERBLUE 2

#define TIMER_ROTATE 150

#define GIFTBOX_GRAVITY 0.002f

class CBlackGiftBox : public CGameObject {
protected:
	float posX;
	float posY;
	ULONGLONG timer_rotate;
	bool isEaten;
	//1: Mushroom, 2: Star, 3: Flower
	int type;

public:
	CBlackGiftBox(float x, float y, int type) : CGameObject(x, y)
	{
		SetState(GIFTBOX_SPECIAL_STATE_MUSHROOM);
		posX = x;
		posY = y;
		timer_rotate = -1;
		isEaten = false;
		this->type = type;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OpenGiftBox();
	int IsCollidable() { return 1; }
	int GetAniId();
};