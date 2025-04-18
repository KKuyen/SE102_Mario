#pragma once

#include "Animation.h"
#include "Animations.h"
#include "Effect.h"
#include "GameManager.h"

#define ID_ANI_POINT_100 610000
#define ID_ANI_POINT_1000 610001

#define ID_ANI_MUSHROOM_EF 120000
 

#define EF_POINT_WIDTH 12
#define EF_POINT_HEIGHT 8

#define POINT_VY_START -0.06f
#define POINT_GRAVITY 0.00005f


class CEffectPoint : public CEffect {
private:
	int point;
 public:
	CEffectPoint(float x, float y, int pointt) : CEffect(x, y) {
		this->point = pointt;
		this->vy = POINT_VY_START;
 		if(pointt>0)
			CGameManager::GetInstance()->points += pointt;
		 
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};