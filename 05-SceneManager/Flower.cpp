#include "Flower.h"
#include "Mario.h"

void CFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x - FLOWER_BBOX_WIDTH / 2;
	top = y - FLOWER_BBOX_HEIGHT / 2;
	right = left + FLOWER_BBOX_WIDTH;
	bottom = top + FLOWER_BBOX_HEIGHT - 1;

}

void CFlower::OnNoCollision(DWORD dt)
{
 
};


void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
 
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
	case FLOWER_STATE_LEFT_FIRE:
		s->Get(ID_FLOWER_TURN_LEFT_FIRE_SPRITE)->Draw(x, y);
		break;
	case FLOWER_STATE_RIGHT_POP_UP:
		animations->Get(ID_FLOWER_TURN_RIGHT_ANI)->Render(x, y);
		break;
	case FLOWER_STATE_RIGHT_POP_DOWN:
		animations->Get(ID_FLOWER_TURN_RIGHT_ANI)->Render(x, y);
		break;
	case FLOWER_STATE_RIGHT_FIRE:
		s->Get(ID_FLOWER_TURN_RIGHT_FIRE_SPRITE)->Draw(x, y);
		break;
	default:
		animations->Get(ID_FLOWER_TURN_LEFT_ANI)->Render(x, y);
		break;
			
	}
	//RenderBoundingBox();

}
