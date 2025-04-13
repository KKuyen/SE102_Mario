#include "Mushroom.h"
#include "Mario.h"
 
void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

		left = x - MUSHROOM_BBOX_WIDTH / 2;
		top = y - MUSHROOM_BBOX_HEIGHT / 2;
		right = left + MUSHROOM_BBOX_WIDTH;
		bottom = top + MUSHROOM_BBOX_HEIGHT;
	
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};
 

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (state == MUSHROOM_STATE_EATEN)
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_MUSHROOM_SPRITE)->Draw(x, y);
	RenderBoundingBox();

}
