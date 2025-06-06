#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "Koopas.h"

#define ID_ANI_BRICK 10000

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
protected:
	int spriteId;
public:
	CBrick(float x, float y, int spriteId) : CGameObject(x, y) {
		this->spriteId = spriteId;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking(LPGAMEOBJECT other) {
		CKoopas* koopas = dynamic_cast<CKoopas*>(other);
		if (koopas && koopas->GetState() == KOOPAS_STATE_FALL)
			return 0;
		return 1;
	}
};