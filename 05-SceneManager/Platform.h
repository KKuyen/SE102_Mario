#pragma once

#include "GameObject.h"
#include "Koopas.h"

// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
	int isVertical; // 0: horizontal, 1: vertical
	int animationId;

public:
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end, int isVertical, int animationId) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
		this->isVertical = isVertical;
		this->animationId = animationId;
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

typedef CPlatform* LPPLATFORM;