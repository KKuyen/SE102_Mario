
#include "Game.h"
#include "debug.h"
#include "Goomba.h"
#include "Mario.h"
#include "Platform.h"
#include "Brick.h"
#include "ColorBox.h"
#include "GiftBox.h"
#include "WingedKoopas.h"
#include "WIngedGoomba.h"
#include "BreakableBrick.h"
CWingedKoopas::CWingedKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = WINGED_KOOPAS_GRAVITY;
	this->nx = -1;
	lastShakeOffset = 0;
	shakeFrameCounter = 0;
	this->beforeLand = false;
	this->canFly = true;
	this->isReverse = false;
	SetState(WINGED_KOOPAS_STATE_INACTIVE);

}
void CWingedKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
	if (state == WINGED_KOOPAS_STATE_SHELL || state == WINGED_KOOPAS_STATE_SHELL_MOVING || state == WINGED_KOOPAS_STATE_HELD|| state == WINGED_KOOPAS_STATE_REVERSE)
	{
		left = x - WINGED_KOOPAS_BBOX_WIDTH / 2+2;
		top = y - WINGED_KOOPAS_BBOX_HEIGHT_SHELL / 2;
		right = left + WINGED_KOOPAS_BBOX_WIDTH-2;
		bottom = top + WINGED_KOOPAS_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - WINGED_KOOPAS_BBOX_WIDTH / 2;
		top = y - WINGED_KOOPAS_BBOX_HEIGHT / 2;
		right = left + WINGED_KOOPAS_BBOX_WIDTH;
		bottom = top + WINGED_KOOPAS_BBOX_HEIGHT;
	}
}
void CWingedKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CWingedKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CWingedKoopas*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) {
		mario = dynamic_cast<CMario*>(e->obj);
	}
	if (dynamic_cast<CBreakableBrick*>(e->obj)) {
		CBreakableBrick* brick = dynamic_cast<CBreakableBrick*>(e->obj);
		if (state == WINGED_KOOPAS_STATE_SHELL_MOVING)
		{
			nx = -nx;
			vx = -vx;
			brick->SetState(BREAKABLE_BRICK_STATE_BREAK);
		}

	}
	if (state == WINGED_KOOPAS_STATE_REVERSE &&
		(dynamic_cast<CPlatform*>(e->obj) || dynamic_cast<CColorBox*>(e->obj) || dynamic_cast<CBrick*>(e->obj)))
	{
		ax = 0;
		vx = 0;
		vy = 0;
		ay = 0;
		state = WINGED_KOOPAS_STATE_SHELL;
	}
	if (state == WINGED_KOOPAS_STATE_FALL &&
		(dynamic_cast<CPlatform*>(e->obj) || dynamic_cast<CColorBox*>(e->obj) || dynamic_cast<CBrick*>(e->obj)))
	{
		return;
	}
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		if (state == WINGED_KOOPAS_STATE_WALKING)
			SetState(WINGED_KOOPAS_STATE_WALKING_RIGHT); // Từ trái sang phải
		else if (state == WINGED_KOOPAS_STATE_WALKING_RIGHT)
			SetState(WINGED_KOOPAS_STATE_WALKING); // Từ phải sang trái
		else if (state == WINGED_KOOPAS_STATE_SHELL_MOVING)
		{
			if (dynamic_cast<CGoomba*>(e->obj))
			{

				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				goomba->SetState(GOOMBA_STATE_FALL); // Mai rùa tiêu diệt Goomba
			}
			else if (e->obj->IsBlocking())
			{
				vx = -vx;
				nx = -nx;
			}
			if (dynamic_cast<CGiftBox*>(e->obj)) {
				CGiftBox* giftbox = dynamic_cast<CGiftBox*>(e->obj);
				if (giftbox->GetState() == GIFTBOX_STATE_SHOWING)
				{
					giftbox->Open(mario);
				}
			}

		}
	}
}
void CWingedKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)

{
	if (state == WINGED_KOOPAS_STATE_INACTIVE) {
		float cx, cy;
		CGame::GetInstance()->GetCamPos(cx, cy);
		if (x < cx + 250) {
			SetState(WINGED_KOOPAS_STATE_WALKING);
		}
	}

	// Kiểm tra nếu đang ở trạng thái SHELL, SHELL_MOVING hoặc HELD và đủ thời gian để hồi sinh
	if ((state == WINGED_KOOPAS_STATE_SHELL  || state == WINGED_KOOPAS_STATE_REVERSE) &&
		revive_start != 0)
	{
		ULONGLONG elapsedTime = GetTickCount64() - revive_start;
		const DWORD SHAKE_TIME = 500; // 0.5 seconds

		if (elapsedTime >= WINGED_KOOPAS_REVIVE_TIME - SHAKE_TIME && elapsedTime < WINGED_KOOPAS_REVIVE_TIME)
		{
			shakeFrameCounter++;
			float shakeOffset = (shakeFrameCounter % 10 < 5) ? 1.0f : -1.0f;
			x += shakeOffset - lastShakeOffset;
			lastShakeOffset = shakeOffset;

			DebugOut(L"[DEBUG] Winged Koopas shaking at (%.1f, %.1f), offset=%.2f, frame=%d\n", x, y, shakeOffset, shakeFrameCounter);
		}
		else if (elapsedTime >= WINGED_KOOPAS_REVIVE_TIME)
		{
			y -= 2;
			vy = WINGED_KOOPAS_JUMP_SPEED;
			ay = WINGED_KOOPAS_GRAVITY;
			lastShakeOffset = 0;
			shakeFrameCounter = 0;
			if (nx < 0)
				SetState(WINGED_KOOPAS_STATE_WALKING);
			else
				SetState(WINGED_KOOPAS_STATE_WALKING_RIGHT);
		}
	}
	if (canFly&&state!=WINGED_KOOPAS_STATE_SHELL && state != WINGED_KOOPAS_STATE_SHELL_MOVING)
	{
		// Check if the Winged Koopas is on the ground
		bool isOnGround = false;

		// Iterate through the list of objects to check if it's standing on `a platform, brick, or color box
		for (LPGAMEOBJECT obj : *coObjects)
		{
			if (dynamic_cast<CPlatform*>(obj) || dynamic_cast<CBrick*>(obj) ||
				dynamic_cast<CColorBox*>(obj))
			{
				float l, t, r, b;
				obj->GetBoundingBox(l, t, r, b);

				float koopasLeft, koopasTop, koopasRight, koopasBottom;
				GetBoundingBox(koopasLeft, koopasTop, koopasRight, koopasBottom);

				// Check if the Winged Koopas is on top of the object
				if (koopasBottom <= t + 1.0f && koopasBottom >= t - 1.0f &&
					koopasLeft <= r && koopasRight >= l)
				{
					isOnGround = true;
					break;
				}
			}
		}

		// If on the ground, make it jump
		if (isOnGround&&state!=WINGED_KOOPAS_STATE_FALL&& state != WINGED_KOOPAS_STATE_REVERSE)
		{
			vy = WINGED_KOOPAS_JUMP_SPEED; // Set vertical velocity for jumping
		}
	}
	vy += ay * dt;
	vx += ax * dt;
	if (state == WINGED_KOOPAS_STATE_HELD)
	{
		vx = 0;
		vy = 0;
		ay = 0;
		return;
	}
	





	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CWingedKoopas::Render()
{
	int aniId;
	
		aniId = ID_ANI_WINGED_KOOPAS_GREEN_WALKING;
		if (state == WINGED_KOOPAS_STATE_WALKING_RIGHT)
			aniId = ID_ANI_WINGED_KOOPAS_GREEN_WALKING_RIGHT;
		if (state == WINGED_KOOPAS_STATE_SHELL || state == WINGED_KOOPAS_STATE_HELD)
		{
			if (!isReverse)
				aniId = ID_ANI_WINGED_KOOPAS_GREEN_SHELL;
			else
				aniId = ID_ANI_WINGED_KOOPAS_GREEN_FALL;
		}
			
		else if (state == WINGED_KOOPAS_STATE_SHELL_MOVING)
			if (!isReverse)

				aniId = ID_ANI_WINGED_KOOPAS_GREEN_SHELL_MOVING;
			else
				aniId = ID_ANI_WINGED_KOOPAS_GREEN_SHELL_MOVING_REVERSE;
		else if (state == WINGED_KOOPAS_STATE_FALL|| state == KOOPAS_STATE_REVERSE)
			aniId = ID_ANI_WINGED_KOOPAS_GREEN_FALL;

	
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	if (ani == nullptr)
	{
		DebugOut(L"[ERROR] Animation ID %d not found!\n", aniId);
		return; // Thoát nếu animation không tồn tại
	}

	ani->Render(x, y);
	if (canFly&&(state== WINGED_KOOPAS_STATE_WALKING|| state == WINGED_KOOPAS_STATE_WALKING_RIGHT))
	{
		if(vx<0)
		{
			aniId = ID_ANI_WINGED_GOOMBA_FLYING;
			CAnimations::GetInstance()->Get(aniId)->Render(x + WINGED_KOOPAS_BBOX_WIDTH / 2, y - WINGED_KOOPAS_BBOX_HEIGHT / 2.5);
		}
		if (vx > 0)
		{
			aniId = ID_ANI_WINGED_GOOMBA_FLYING_LEFT;
		CAnimations::GetInstance()->Get(aniId)->Render(x - WINGED_KOOPAS_BBOX_WIDTH / 2, y - WINGED_KOOPAS_BBOX_HEIGHT / 2.5);
		}
	
	}


	//RenderBoundingBox();



}
void CWingedKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	
	switch (state)
	{
	case WINGED_KOOPAS_STATE_INACTIVE:
		vx = 0;
		
		ax = 0;
		break;
	case WINGED_KOOPAS_STATE_WALKING:
		y -= 3;
		vx = -WINGED_KOOPAS_WALKING_SPEED;
		nx = -nx;
		revive_start = 0;
		break;
	case WINGED_KOOPAS_STATE_WALKING_RIGHT:
		y -= 3;
		vx = WINGED_KOOPAS_WALKING_SPEED;
		nx = -nx;
		revive_start = 0;
		break;
	case WINGED_KOOPAS_STATE_SHELL:
	
		vx = 0;
		
		ax = 0;
		

		StartReviveTimer();
		break;
	case WINGED_KOOPAS_STATE_HELD:
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
		StartReviveTimer();

		break;
	case WINGED_KOOPAS_STATE_SHELL_MOVING:
		vx = nx * WINGED_KOOPAS_SHELL_MOVING_SPEED;
		ay = WINGED_KOOPAS_GRAVITY;
		StartReviveTimer();
		break;
	case WINGED_KOOPAS_STATE_FALL:

		vx = nx * WINGED_KOOPAS_FALL_SPEED_HORIZONTAL;

		vy = WINGED_KOOPAS_FALL_SPEED; // Nảy lên
		ay = WINGED_KOOPAS_GRAVITY_FALL; // Trọng lực sẽ kéo xuống
		revive_start = 0;


		break;
	case WINGED_KOOPAS_STATE_REVERSE:
		this->isReverse = true;
		canFly = false;
		vx = nx * WINGED_KOOPAS_FALL_SPEED_HORIZONTAL;

		vy = WINGED_KOOPAS_FALL_SPEED/1.5 ; // Nảy lên
		
		ay = WINGED_KOOPAS_GRAVITY_FALL; // Trọng lực sẽ kéo xuống
	
		StartReviveTimer();

		break;
	}
}