#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CBackground : public CGameObject {
protected:
	int width;
	int height;
	int spriteId;
public:
	CBackground(float x, float y, int width, int height, int spriteId) : CGameObject(x, y)
	{
		this->width = width;
		this->height = height;
		this->spriteId = spriteId;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};