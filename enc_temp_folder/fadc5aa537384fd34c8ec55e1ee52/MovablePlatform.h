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
<<<<<<< HEAD
#define PLATFORM_GRAVITY 0.09f
=======
#define PLATFORM_GRAVITY 0.07f
>>>>>>> ba902ca415e1d18789f119c9d7690c5004fbc09b
#define SCREEN_WIDTH 270
#define MAX_SCENE_X 2540

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
	int IsBlocking()  { return 1; } // Đảm bảo platform là vật cản
	virtual int IsCollidable() { return 1; } // Đảm bảo platform có thể va chạm
	void Falling();
	int IsDirectionColliable(float nx, float ny);

 
};