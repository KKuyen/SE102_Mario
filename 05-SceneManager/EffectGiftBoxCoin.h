#pragma once

#include "Animation.h"
#include "Animations.h"
#include "Effect.h"
#include "GameManager.h"

#define ID_ANI_COINBOX 600000

#define EF_COINBOX_WIDTH 8
#define EF_COINBOX_HEIGHT 16

#define COINBOX_VY_START -0.4f
#define COINBOX_GRAVITY 0.0018f


class CEffectGiftBoxCoin : public CEffect {
private:
	float initY;
	bool calledEffectPoint = false;
public:
	CEffectGiftBoxCoin(float x, float y) : CEffect(x, y) {
		this->initY = y;
		this->vy = COINBOX_VY_START;
		CGameManager::GetInstance()->coins += 1;

	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void EffectPoint();
};