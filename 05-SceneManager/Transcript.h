#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define SPRITE_ID 210000
#define TRANSCRIPT_WIDTH 263
#define TRANSCRIPT_HEIGHT 74

class CTranscript : public CGameObject {
protected:

public:
	CTranscript(float x, float y) : CGameObject(x, y)
	{

	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};