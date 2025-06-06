#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
#define CHIMNEY_TYPE_NONE 1;
#define CHIMNEY_TYPE_GO_DOWN 2;
#define CHIMNEY_TYPE_GO_UP 3;
class CChimney : public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
	int isVertical;	// 1: vertical, 0: horizontal
	int type; // 1: none , 2: can go down , 3 : can  go up

public:

	CChimney(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end, int isVertical, int type) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
		this->isVertical = isVertical;
		this->type = type;

	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int getType()
	{
		return type;
	}
	int IsBlocking() {
		return 1;
	}
};

