#include "BomerangBro.h"
#include "Koopas.h"

CBomerangBro::CBomerangBro(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = BOMERANG_BRO_GRAVITY;
	die_start = -1;
	SetState(BOMERANG_BRO_STATE_WALKING_RIGHT);
	mario = nullptr;

}

void CBomerangBro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

		left = x - BOMERANG_BRO_BBOX_WIDTH / 2;
		top = y - BOMERANG_BRO_BBOX_HEIGHT / 2;
		right = left + BOMERANG_BRO_BBOX_WIDTH;
		bottom = top + BOMERANG_BRO_BBOX_HEIGHT;
}

void CBomerangBro::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBomerangBro::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CBomerangBro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (mario != nullptr)
	{
		float mario_x, mario_y;
		mario->GetPosition(mario_x, mario_y);
		bool isMarioRight = (mario_x > x);
		if (isMarioRight && vx < 0) {
			vx = -vx;
		}
		else if (!isMarioRight && vx > 0) {
			vx = -vx;
		}
	
			
	}

	if ((state == BOMERANG_BRO_STATE_DIE) && (GetTickCount64() - die_start > BOMERANG_BRO_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if (vx <  0)
	{
		if (state == BOMERANG_BRO_STATE_WALKING_RIGHT)
			SetState(BOMERANG_BRO_STATE_WALKING_LEFT);
	}
	else if (vx > 0)
	{
		if (state == BOMERANG_BRO_STATE_WALKING_LEFT)
			SetState(BOMERANG_BRO_STATE_WALKING_RIGHT);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBomerangBro::Render()
{
	int aniId;
	if (state == BOMERANG_BRO_STATE_WALKING_RIGHT) {
		aniId = ID_ANI_BOMERANG_BRO_WALKING_RIGHT;
	}
	else if (state== BOMERANG_BRO_STATE_WALKING_LEFT) {
		aniId = ID_ANI_BOMERANG_BRO_WALKING_LEFT;
	}
 
	if (state == BOMERANG_BRO_STATE_DIE)
	{
		aniId = ID_ANI_BOMERANG_BRO_DIE;
		CSprites* s = CSprites::GetInstance();
		s->Get(aniId)->Draw(x, y);

	}
	else if (state == BOMERANG_BRO_STATE_FALL)
	{
		aniId = ID_ANI_BOMERANG_BRO_DIE;
		CSprites* s = CSprites::GetInstance();
		s->Get(aniId)->Draw(x, y);
	}
	else {
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	}


}

void CBomerangBro::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOMERANG_BRO_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case BOMERANG_BRO_STATE_WALKING_RIGHT:
		vx = -BOMERANG_BRO_WALKING_SPEED;
		break;
	case BOMERANG_BRO_STATE_FALL:
		die_start = GetTickCount64();
		vx = nx * BOMERANG_BRO_FALL_SPEED_HORIZONTAL;
		vy = BOMERANG_BRO_FALL_SPEED; // N?y lên
		ay = BOMERANG_BRO_GRAVITY; // Tr?ng l?c s? kéo xu?ng
		break;
	}
}
