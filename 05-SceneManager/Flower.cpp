#include "Flower.h"
#include "Mario.h"
#include "Bullet.h"
#include "PlayScene.h"
#include "Game.h"
void CFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x - FLOWER_BBOX_WIDTH / 2;
	top = y - FLOWER_BBOX_HEIGHT / 2;
	right = left + FLOWER_BBOX_WIDTH;
	bottom = top + FLOWER_BBOX_HEIGHT - 1;

}

void CFlower::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

};


void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (mario != nullptr)
	{
		float mario_x, mario_y;
		mario->GetPosition(mario_x, mario_y);
		bool isMarioRight = (mario_x > x);  
		bool isUpFire = (mario_y < 117);
		if (isMarioRight)
		{
			if (state == FLOWER_STATE_LEFT_POP_UP)
				SetState(FLOWER_STATE_RIGHT_POP_UP);
		}
		else
		{
			if (state == FLOWER_STATE_RIGHT_POP_UP)
				SetState(FLOWER_STATE_LEFT_POP_UP);
		}
		
		if (!isUpFire) {
			if (state == FLOWER_STATE_LEFT_UP_FIRE)
			{
				state = FLOWER_STATE_LEFT_DOWN_FIRE;
			}
			if (state == FLOWER_STATE_RIGHT_UP_FIRE)
			{
				state = FLOWER_STATE_RIGHT_DOWN_FIRE;
			}

		}
		else {
			if (state == FLOWER_STATE_LEFT_DOWN_FIRE)
			{
				state = FLOWER_STATE_LEFT_UP_FIRE;
			}
			if (state == FLOWER_STATE_RIGHT_DOWN_FIRE)
			{
				state = FLOWER_STATE_RIGHT_UP_FIRE;
			}
		}
		
	}
	switch (state)
	{
	case FLOWER_STATE_LEFT_POP_UP:
		vy = -FLOWER_POP_UP_SPEED;
 		if (this->initY - y >= FLOWER_POP_UP_HEIGHT) {
			vy = 0;
			SetState(FLOWER_STATE_LEFT_UP_FIRE);
		}
		break;
	case FLOWER_STATE_LEFT_POP_DOWN:
		vy = FLOWER_POP_UP_SPEED;
		if (y >= initY) {
			vy = 0;
			if (start == 0)
				start = GetTickCount64();
			if (GetTickCount64() - start > 1700) {
				SetState(FLOWER_STATE_LEFT_POP_UP);
				start = 0;
			}
		}
		break;
    case FLOWER_STATE_LEFT_UP_FIRE:
	{
		if (start == 0)
			start = GetTickCount64();
		if (mario != nullptr && isFired==false)
		{
			DebugOut(L"[INFO] Fire bullet \n");
			float mario_x, mario_y;
			mario->GetPosition(mario_x, mario_y);
			LPGAMEOBJECT bullet = new CBullet(x, y-6, mario_x, mario_y);
			LPSCENE s = CGame::GetInstance()->GetCurrentScene();
			LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
			p->AddGameObject(bullet);
			isFired = true;
 		}
		if (GetTickCount64() - start > 1700) {
			
			SetState(FLOWER_STATE_LEFT_POP_DOWN);
			isFired = false;
			start = 0;
		}
		
	}
	break;
	case FLOWER_STATE_LEFT_DOWN_FIRE:
		if (start == 0)
			start = GetTickCount64();

		if (GetTickCount64() - start > 1700) {
			SetState(FLOWER_STATE_LEFT_POP_DOWN);
			start = 0;
		}
		break;
	case FLOWER_STATE_RIGHT_POP_UP:
		vy = -FLOWER_POP_UP_SPEED;
		if (this->initY - y >= FLOWER_POP_UP_HEIGHT) {
			SetState(FLOWER_STATE_RIGHT_UP_FIRE);
		}
		break;
	case FLOWER_STATE_RIGHT_POP_DOWN:
		vy = FLOWER_POP_UP_SPEED;
		if (y >= initY) {
			vy = 0;
			if (start == 0)
				start = GetTickCount64();
			if (GetTickCount64() - start > 1700) {
				SetState(FLOWER_STATE_RIGHT_POP_UP);
				start = 0;
			}
		}
		break;
	case FLOWER_STATE_RIGHT_UP_FIRE:
		vy = 0;
		if (start == 0)
			start = GetTickCount64();
		if (GetTickCount64() - start > 1700) {
			SetState(FLOWER_STATE_RIGHT_POP_DOWN);
			start = 0;
		}
		break;
	case FLOWER_STATE_RIGHT_DOWN_FIRE:
		vy = 0;
		if (start == 0)
			start = GetTickCount64();
		if (GetTickCount64() - start > 1700) {
			SetState(FLOWER_STATE_RIGHT_POP_DOWN);
			start = 0;
		}
		break;
	default:
		break;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
 
void CFlower::Render()
{
	CSprites* s = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	switch (state) {
	case FLOWER_STATE_LEFT_POP_UP:
		animations->Get(ID_FLOWER_TURN_LEFT_ANI)->Render(x, y);
		break;
	case FLOWER_STATE_LEFT_POP_DOWN:
		animations->Get(ID_FLOWER_TURN_LEFT_ANI)->Render(x, y);
		break;
	case FLOWER_STATE_LEFT_UP_FIRE:
		s->Get(ID_FLOWER_LEFT_UP_FIRE_SPRITE)->Draw(x, y);
		break;
	case FLOWER_STATE_LEFT_DOWN_FIRE:
		s->Get(ID_FLOWER_LEFT_DOWN_FIRE_SPRITE)->Draw(x, y);
		break;
	case FLOWER_STATE_RIGHT_POP_UP:
		animations->Get(ID_FLOWER_TURN_RIGHT_ANI)->Render(x, y);
		break;
	case FLOWER_STATE_RIGHT_POP_DOWN:
		animations->Get(ID_FLOWER_TURN_RIGHT_ANI)->Render(x, y);
		break;
	case FLOWER_STATE_RIGHT_UP_FIRE:
		s->Get(ID_FLOWER_RIGHT_UP_FIRE_SPRITE)->Draw(x, y);
		break;
	case FLOWER_STATE_RIGHT_DOWN_FIRE:
		s->Get(ID_FLOWER_RIGHT_DOWN_FIRE_SPRITE)->Draw(x, y);
		break;
	default:
		animations->Get(ID_FLOWER_TURN_LEFT_ANI)->Render(x, y);
		break;
			
	}
	//RenderBoundingBox();

}
