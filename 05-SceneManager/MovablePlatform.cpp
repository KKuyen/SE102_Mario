#include "MovablePlatform.h"

void CMovablePlatform::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_MOVABLE_PLATFORM1)->Draw(x, y);
	s->Get(ID_MOVABLE_PLATFORM2)->Draw(x+16, y);
	s->Get(ID_MOVABLE_PLATFORM3)->Draw(x+16*2, y);

	//RenderBoundingBox();
}

void CMovablePlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PLATFORM_WIDTH / 2;
	t = y - PLATFORM_HEIGHT / 2;
	r = l + PLATFORM_WIDTH;
	b = t + PLATFORM_HEIGHT;
}