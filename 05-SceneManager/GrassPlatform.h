#pragma once

#include "GameObject.h"
#include "Koopas.h"

// 
// The most popular type of object in Mario! 
// 
class CGrassPlatform : public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
	CGrassPlatform(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	virtual int IsBlocking(LPGAMEOBJECT other) {
		CKoopas* koopas = dynamic_cast<CKoopas*>(other);
		if (koopas && koopas->GetState() == KOOPAS_STATE_FALL)
			return 0;
		return 1;
	}

	int IsDirectionColliable(float nx, float ny);
};

typedef CGrassPlatform* LPPLATFORM;