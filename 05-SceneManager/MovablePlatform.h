#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_MOVABLE_PLATFORM1 270000
#define ID_MOVABLE_PLATFORM2 270001
#define ID_MOVABLE_PLATFORM3 270002
#define PLATFORM_WIDTH 48
#define PLATFORM_HEIGHT 16
#define PLATFORM_SPEED 0.03f
#define PLATFORM_GRAVITY 0.02f

class CMovablePlatform : public CGameObject {
public:
	CMovablePlatform(float x, float y) : CGameObject(x, y) {
		vx =- PLATFORM_SPEED;
		vy = 0;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	virtual int IsCollidable() { return 1; };
	void Falling();

 
};