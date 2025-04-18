#pragma once

#include "Animation.h"
#include "Animations.h"
#include "Effect.h"
#include "GameManager.h"


#define EF_SMOKE_WIDTH 11
#define EF_SMOKE_HEIGHT 11

#define SMOKE_ANI	620000


class CEffectSmoke : public CEffect {
  public:
	CEffectSmoke(float x, float y) : CEffect(x, y) {
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};