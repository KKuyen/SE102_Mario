#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define NUMBER_TEXT_0 230000
#define NUMBER_TEXT_1 230001
#define NUMBER_TEXT_2 230002
#define NUMBER_TEXT_3 230003
#define NUMBER_TEXT_4 230004
#define NUMBER_TEXT_5 230005
#define NUMBER_TEXT_6 230006
#define NUMBER_TEXT_7 230007
#define NUMBER_TEXT_8 230008
#define NUMBER_TEXT_9 230009
#define NUMBER_TEXT_P_ANI 230013
#define NUMBER_TEXT_P 230011


class CNumberText : public CGameObject {
protected:
	int idSprite;
	int energy;
public:
	CNumberText(float x, float y, int energy) : CGameObject(x, y) {
		idSprite = NUMBER_TEXT_0;
		this->energy = energy;
	}
	CNumberText() : energy(0) {}


	void setEnergy(int energy) {
		this->energy = energy;
	}
	void setPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
	void SetIdSprite(int idSp);
};