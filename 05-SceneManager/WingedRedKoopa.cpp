#include "WingedRedKoopa.h"
#include "Game.h"
#include "debug.h"
#include "Goomba.h"
#include "Mario.h"
#include "Platform.h"
#include "Brick.h"
#include "ColorBox.h"
#include "GiftBox.h"
#include "GrassPlatform.h"
CWingedRedKoopa::CWingedRedKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->nx = -1;
	this->color = 1;
	SetState(KOOPAS_STATE_DOWN);


}
void CWingedRedKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
}
void CWingedRedKoopa::OnNoCollision(DWORD dt)
{
		if (state == KOOPAS_STATE_UP)
		{
			y -= KOOPAS_VERTICAL_MOVE_SPEED * dt;
		}
		else if (state == KOOPAS_STATE_DOWN)
		{
			y += KOOPAS_VERTICAL_MOVE_SPEED * dt;
		}
		else if (state == KOOPAS_STATE_WALKING)
		{
			y -= KOOPAS_FALL_SPEED * dt;
		}

}

void CWingedRedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

		if (state == KOOPAS_STATE_UP && y <= MIN_VERTICAL_MOVE)
		{
			SetState(KOOPAS_STATE_DOWN);
		}
		else if (state == KOOPAS_STATE_DOWN && y >= MAX_VERTICAL_MOVE)
		{
			SetState(KOOPAS_STATE_UP);
		}

	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CWingedRedKoopa::Render()
{
		int aniId = ID_ANI_WINGED_RED_KOOPA;
		if (state == KOOPAS_STATE_WALKING)
		{
			aniId = ID_ANI_KOOPAS_WALKING;

		}
		LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
		if (ani == nullptr)
		{
			DebugOut(L"[ERROR] Animation ID %d not found!\n", aniId);
			return; 
		}
		ani->Render(x, y);
	
	//RenderBoundingBox();


}
void CWingedRedKoopa::SetState(int state)
{
	CGameObject::SetState(state);

}
