#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CEffect : public CGameObject {
public:
	CEffect(float x, float y) : CGameObject(x, y) {};
	virtual void Render() = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
	int IsBlocking() { return 0; }
}; 
