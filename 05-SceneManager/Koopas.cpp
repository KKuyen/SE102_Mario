#include "Koopas.h"
#include "Game.h"
#include "debug.h"
#include "Goomba.h"
#include "Mario.h"
#include "Platform.h"
#include "Brick.h"
#include "ColorBox.h"
#include "GiftBox.h"
#include "BreakableBrick.h"
#include "GrassPlatform.h"
#include "CoinBrick.h"
#include "BreakableBrickChain.h"

CKoopas::CKoopas(float x, float y,int color) :CGameObject(x, y)
{
	this->ax = 0;
	lastShakeOffset = 0;
	shakeFrameCounter = 0;
	this->ay = KOOPAS_GRAVITY;
	this->nx = -1;
	this->color = color;
	SetState(KOOPAS_STATE_WALKING);
	this->isReverse = false;

}
void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_SHELL_MOVING || state == KOOPAS_STATE_HELD || state == KOOPAS_STATE_REVERSE)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2 + 2;
		top = y - KOOPAS_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPAS_BBOX_WIDTH - 2;
		bottom = top + KOOPAS_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}
void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) {
		mario = dynamic_cast<CMario*>(e->obj);
	}
	if (dynamic_cast<CBreakableBrick*>(e->obj)) {
		CBreakableBrick*	brick = dynamic_cast<CBreakableBrick*>(e->obj);
		if (state == KOOPAS_STATE_SHELL_MOVING)
		{
			nx = -nx;
			vx = -vx;
			
			brick->SetState(BREAKABLE_BRICK_STATE_BREAK);
		}

	}
	if (state == KOOPAS_STATE_REVERSE &&
		(dynamic_cast<CPlatform*>(e->obj) || dynamic_cast<CBreakableBrickChain*>(e->obj)  || dynamic_cast<CGrassPlatform*>(e->obj) || dynamic_cast<CColorBox*>(e->obj) || dynamic_cast<CBrick*>(e->obj)))
	{

		ax = 0;
		vx = 0;
		vy = 0;
		ay = 0;
		state = KOOPAS_STATE_SHELL;
	}
	if (state == KOOPAS_STATE_FALL &&
		(dynamic_cast<CPlatform*>(e->obj) || dynamic_cast<CGrassPlatform*>(e->obj) || dynamic_cast<CColorBox*>(e->obj) || dynamic_cast<CBrick*>(e->obj)))
	{
		return;
	}
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		if (state == KOOPAS_STATE_WALKING)
			SetState(KOOPAS_STATE_WALKING_RIGHT); // Từ trái sang phải
		else if (state == KOOPAS_STATE_WALKING_RIGHT)
			SetState(KOOPAS_STATE_WALKING); // Từ phải sang trái
		else if (state == KOOPAS_STATE_SHELL_MOVING)
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
void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if(x>2230&&y>185)
	{
		isDeleted = true;
	}
	vy += ay * dt;
	vx += ax * dt;

	//DebugOut(L"[Koopas] revive condition: %d\n", (GetTickCount64() - revive_start) >= KOOPAS_REVIVE_TIME);

	if (state == KOOPAS_STATE_HELD)
	{
		vx = 0;
		vy = 0;
		ay = 0;
		return;
	}
	// Kiểm tra rìa mặt phẳng
	if (state == KOOPAS_STATE_WALKING || state == KOOPAS_STATE_WALKING_RIGHT)
	{
		bool isOnPlatform = false;
		float platformLeft, platformRight;
		CScene* currentScene = CGame::GetInstance()->GetCurrentScene();

		// Tìm đối tượng mà Koopas đang đứng
		for (LPGAMEOBJECT obj : *coObjects)
		{
			// Truyền vào các loại đối tượng
			if (dynamic_cast<CCoinBrick*>(obj) || dynamic_cast<CBreakableBrickChain*>(obj) || dynamic_cast<CGrassPlatform*>(obj) || dynamic_cast<CPlatform*>(obj) ||( dynamic_cast<CBreakableBrick*>(obj) && currentScene->GetId() == 1)|| (dynamic_cast<CColorBox*>(obj) && dynamic_cast<CColorBox*>(obj)->isPlatform == 1) || dynamic_cast<CBrick*>(obj))
			{

				float l, t, r, b;
				obj->GetBoundingBox(l, t, r, b);
				if (dynamic_cast<CBreakableBrickChain*>(obj))
				{
					l -= 16;
				}
 


				float koopasLeft, koopasTop, koopasRight, koopasBottom;
				GetBoundingBox(koopasLeft, koopasTop, koopasRight, koopasBottom);
				// Kiểm tra xem Koopas có đang đứng trên đối tượng này không
				if (koopasBottom <= t + 1.0f && koopasBottom >= t - 1.0f &&
					koopasLeft <= r && koopasRight >= l)
				{


					isOnPlatform = true;
					platformLeft = l - 6;
					platformRight = r + 6;
					break;
				}
			}
		}

		// Nếu đang trên mặt phẳng, kiểm tra rìa
		if (isOnPlatform&&color==1)
		{
			float nextX = x + vx * dt; // Vị trí tiếp theo của Koopas

			if (state == KOOPAS_STATE_WALKING && nextX <= platformLeft + KOOPAS_BBOX_WIDTH / 2)
			{
				// Gặp rìa trái, quay sang phải
				SetState(KOOPAS_STATE_WALKING_RIGHT);
			}
			else if (state == KOOPAS_STATE_WALKING_RIGHT && nextX >= platformRight - KOOPAS_BBOX_WIDTH / 2)
			{
				// Gặp rìa phải, quay sang trái
				SetState(KOOPAS_STATE_WALKING);
			}
		}
	}


	// Kiểm tra nếu đang ở trạng thái SHELL, SHELL_MOVING hoặc HELD và đủ thời gian để hồi sinh
	if ((state == KOOPAS_STATE_SHELL || state ==KOOPAS_STATE_HELD || state == KOOPAS_STATE_REVERSE) &&
		revive_start != 0)
	{
		ULONGLONG elapsedTime = GetTickCount64() - revive_start;
		const DWORD SHAKE_TIME = 500; // 0.5 seconds in milliseconds

		// Shaking period (0.5s before revival)
		if (elapsedTime >= KOOPAS_REVIVE_TIME - SHAKE_TIME && elapsedTime < KOOPAS_REVIVE_TIME)
		{
			// Toggle-based shaking
			shakeFrameCounter++;
			float shakeOffset = (shakeFrameCounter % 10 < 5) ? 1.0f : -1.0f; // Alternate ±1 every 5 frames
			x += shakeOffset - lastShakeOffset; // Apply relative to previous offset
			lastShakeOffset = shakeOffset;

			DebugOut(L"[DEBUG] Winged Koopas shaking at (%.1f, %.1f), offset=%.2f, frame=%d\n", x, y, shakeOffset, shakeFrameCounter);
		}
		// Revival
		else if (elapsedTime >=KOOPAS_REVIVE_TIME)
		{
			y -= 2;
			vy = KOOPAS_JUMP_SPEED; // Nảy lên
			ay = KOOPAS_GRAVITY;
			// Reset any shaking offset
			
			    // Áp dụng trọng lực
			lastShakeOffset = 0; // Reset shaking
			shakeFrameCounter = 0; // Reset frame counter
			if (nx < 0)
				SetState(KOOPAS_STATE_WALKING);
			else
				SetState(KOOPAS_STATE_WALKING_RIGHT);
		}
	}




	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	int aniId;
	
	if (color == 1)
	{
		
		aniId = ID_ANI_KOOPAS_WALKING;
		

		if (state == KOOPAS_STATE_WALKING_RIGHT)
			aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
		if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_HELD)
		{
			if (!isReverse)
				aniId = ID_ANI_KOOPAS_SHELL;
			else
				aniId = ID_ANI_KOOPAS_FALL;
		}

		else if (state == KOOPAS_STATE_SHELL_MOVING)
		{
			if (!isReverse)

				aniId = ID_ANI_KOOPAS_SHELL_MOVING;
			else
				aniId = ID_ANI_KOOPAS_SHELL_MOVING_REVERSE;
		}


		else if (state == KOOPAS_STATE_FALL || state == KOOPAS_STATE_REVERSE)
			aniId = ID_ANI_KOOPAS_FALL;




	}
	else
	{

		aniId = ID_ANI_KOOPAS_GREEN_WALKING;
	
		if (state == KOOPAS_STATE_WALKING_RIGHT)
			aniId = ID_ANI_KOOPAS_GREEN_WALKING_RIGHT;
		if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_HELD)
		{
			if (!isReverse)
				aniId = ID_ANI_KOOPAS_GREEN_SHELL;
			else
				aniId = ID_ANI_KOOPAS_GREEN_FALL;
		}

		else if (state == KOOPAS_STATE_SHELL_MOVING)
		{
			if (!isReverse)

				aniId = ID_ANI_KOOPAS_GREEN_SHELL_MOVING;
			else
				aniId = ID_ANI_KOOPAS_GREEN_SHELL_MOVING_REVERSE;
		}
		else if (state == KOOPAS_STATE_FALL || state == KOOPAS_STATE_REVERSE)
			aniId = ID_ANI_KOOPAS_GREEN_FALL;

	}
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	if (ani == nullptr)
	{
		DebugOut(L"[ERROR] Animation ID %d not found!\n", aniId);
		return; // Thoát nếu animation không tồn tại
	}

	ani->Render(x, y);

	//RenderBoundingBox();


}
void CKoopas::SetState(int state)
{
	
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		y -= 2;
		this->isReverse = false;

		vx = -KOOPAS_WALKING_SPEED;
		nx = -nx;
		revive_start = 0;
		break;
	case KOOPAS_STATE_WALKING_RIGHT:
		y -= 2;
		this->isReverse = false;
		vx = KOOPAS_WALKING_SPEED;
		nx = -nx;
		revive_start = 0;
		break;
	case KOOPAS_STATE_SHELL:
		y -= 2;
		
		vx = 0;
		
		ax = 0;
		


		StartReviveTimer();
		break;
	case KOOPAS_STATE_HELD:
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
	     if(revive_start==0)
		StartReviveTimer();

		break;
	case KOOPAS_STATE_SHELL_MOVING:
		vx = nx * KOOPAS_SHELL_MOVING_SPEED;
		vy = 0;
		ay = KOOPAS_GRAVITY;
		StartReviveTimer();
		break;
	case KOOPAS_STATE_FALL:

		vx = nx * KOOPAS_FALL_SPEED_HORIZONTAL;

		vy = KOOPAS_FALL_SPEED; // Nảy lên
		ay = KOOPAS_GRAVITY_FALL; // Trọng lực sẽ kéo xuống
		revive_start = 0;
		break;

	case KOOPAS_STATE_REVERSE:
		this->isReverse = true;
		vx = nx * KOOPAS_FALL_SPEED_HORIZONTAL;

		vy = KOOPAS_FALL_SPEED * 2; // Nảy lên
		vy = KOOPAS_FALL_SPEED * 2; // Nảy lên
		ay = KOOPAS_GRAVITY_FALL; // Trọng lực sẽ kéo xuống
		StartReviveTimer();







		break;
	}
}