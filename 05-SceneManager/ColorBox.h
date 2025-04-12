#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CColorBox : public CGameObject {
protected:
	int width;
	int height;
	int spriteId;
public:
	CColorBox(float x, float y, int width, int height, int spriteId) : CGameObject(x, y)
	{
		this->width = width;
		this->height = height;
		this->spriteId = spriteId;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);
	 
	int IsBlocking() {
		if (spriteId % 10 == 1 || spriteId % 10 == 2 || spriteId % 10 == 3)
			return 1;
		return 0;
	}
};