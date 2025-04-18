#include "Koopas.h"
#include "Game.h"
#include "debug.h"
#include "Goomba.h"
#include "Mario.h"
#include "Platform.h"
#include "Brick.h"
#include "ColorBox.h"
#include "GiftBox.h"
CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->nx = -1;
	SetState(KOOPAS_STATE_WALKING);

}
void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_SHELL_MOVING || state == KOOPAS_STATE_HELD)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPAS_BBOX_WIDTH;
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
	if (state == KOOPAS_STATE_FALL &&
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
	vy += ay * dt;
	vx += ax * dt;
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

		// Tìm đối tượng mà Koopas đang đứng
		for (LPGAMEOBJECT obj : *coObjects)
		{
			// Truyền vào các loại đối tượng
			if (dynamic_cast<CPlatform*>(obj) || dynamic_cast<CColorBox*>(obj) || dynamic_cast<CBrick*>(obj))
			{
				float l, t, r, b;
				obj->GetBoundingBox(l, t, r, b);


				float koopasLeft, koopasTop, koopasRight, koopasBottom;
				GetBoundingBox(koopasLeft, koopasTop, koopasRight, koopasBottom);
				// Kiểm tra xem Koopas có đang đứng trên đối tượng này không
				if (koopasBottom <= t + 1.0f && koopasBottom >= t - 1.0f &&
					koopasLeft <= r && koopasRight >= l)
				{
					isOnPlatform = true;
					platformLeft = l;
					platformRight = r+16;
					break;
				}
			}
		}

		// Nếu đang trên mặt phẳng, kiểm tra rìa
		if (isOnPlatform)
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
	if ((state == KOOPAS_STATE_SHELL ||state == KOOPAS_STATE_HELD ) &&
		revive_start != 0 && GetTickCount64() - revive_start >= KOOPAS_REVIVE_TIME)
	{
		vy = KOOPAS_JUMP_SPEED; // Nảy lên
		ay = KOOPAS_GRAVITY;    // Áp dụng trọng lực
		if(nx<0)
		SetState(KOOPAS_STATE_WALKING);
		else
		{
			SetState(KOOPAS_STATE_WALKING_RIGHT);
		}
	}

	


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING;
	if (state == KOOPAS_STATE_WALKING_RIGHT)
		aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_HELD)
		aniId = ID_ANI_KOOPAS_SHELL;
	else if (state == KOOPAS_STATE_SHELL_MOVING)
		aniId = ID_ANI_KOOPAS_SHELL_MOVING;
	else if (state == KOOPAS_STATE_FALL)
		aniId = ID_ANI_KOOPAS_FALL;



	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	if (ani == nullptr)
	{
		DebugOut(L"[ERROR] Animation ID %d not found!\n", aniId);
		return; // Thoát nếu animation không tồn tại
	}

	ani->Render(x, y);
	RenderBoundingBox();

	
}
void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		nx=-nx;
		revive_start = 0;
		break;
	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED; 
		nx = -nx;
		revive_start = 0;
		break;
	case KOOPAS_STATE_SHELL:
		vx = 0;
		vy = 0;
		ay = KOOPAS_GRAVITY;
		 y += (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_SHELL) / 2;
		 StartReviveTimer(); 
		break;
	case KOOPAS_STATE_HELD:
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
		StartReviveTimer(); 
		
		break;
	case KOOPAS_STATE_SHELL_MOVING:
		vx = nx * KOOPAS_SHELL_MOVING_SPEED;
		ay = KOOPAS_GRAVITY;
		StartReviveTimer(); 
		break;
	case KOOPAS_STATE_FALL:
	
		vx = KOOPAS_FALL_SPEED_HORIZONTAL;
		
		vy = KOOPAS_FALL_SPEED; // Nảy lên
		ay = KOOPAS_GRAVITY; // Trọng lực sẽ kéo xuống
		revive_start = 0; 
		
	
		

		
		
		break;
	}
}