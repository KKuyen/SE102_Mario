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
#define PLATFORM_GRAVITY 0.04f
#define SCREEN_WIDTH 270

class CMovablePlatform : public CGameObject {
public:
	int ay;
	int isActive;
	CMovablePlatform(float x, float y) : CGameObject(x, y) {
		vx =- PLATFORM_SPEED;
		vy = 0;
		ay = 0;
		isActive = 0;

	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	virtual int IsCollidable() { return 1; };
	void Falling();
	int IsDirectionColliable(float nx, float ny);

 
};