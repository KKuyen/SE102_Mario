#include "EffectPoint.h"

void CEffectPoint::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* ani = CAnimations::GetInstance();

	switch (point)
	{
	case 100:
		sprites->Get(ID_ANI_POINT_100)->Draw(x, y);
		break;
	case 0:
		ani->Get(ID_ANI_MUSHROOM_EF)->Render(x, y);
		break;
	default:
		sprites->Get(ID_ANI_POINT_100)->Draw(x, y);
		break;
	}
	//RenderBoundingBox();
}

void CEffectPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - EF_POINT_WIDTH / 2;
	t = y - EF_POINT_HEIGHT / 2;
	r = l + EF_POINT_WIDTH - 1;
	b = t + EF_POINT_HEIGHT;
}

void CEffectPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += POINT_GRAVITY * dt;
	y += vy * dt;
	if (vy > 0) {
		this->Delete();
	}
	CGameObject::Update(dt, coObjects);
}