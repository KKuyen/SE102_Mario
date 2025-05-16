#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_MOVABLE_PLATFORM1 270000
#define ID_MOVABLE_PLATFORM2 270001
#define ID_MOVABLE_PLATFORM3 270002
#define PLATFORM_WIDTH 48
#define PLATFORM_HEIGHT 16

class CMovablePlatform : public CGameObject {
public:
	CMovablePlatform(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
};