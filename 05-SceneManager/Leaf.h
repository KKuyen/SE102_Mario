#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_LEFT_LEAF 170001
#define ID_RIGHT_LEAF 170002
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 14
#define LEAF_GRAVITY_Y 0.03f
#define LEAF_GRAVITY_X 0.05f
#define LEAF_SOAR_SPEED 0.07f
#define PLATFORM_Y 184
//Bien do dao dong
 #define AMPLITUDE 48
#define LEAF_SOAR_HEIGHT 80

#define LEAF_STATE_SOAR 100
#define LEAF_STATE_FALL 200
 
class CLeaf : public CGameObject {
public:
	int initX;
	int direction  ;
	CLeaf(float x, float y) : CGameObject(x, y) {
		this->initX = x;
		direction = -1;
		SetState(LEAF_STATE_SOAR);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};