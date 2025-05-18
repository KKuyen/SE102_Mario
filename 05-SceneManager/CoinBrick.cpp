#include "CoinBrick.h"
#include "PlayScene.h"
#include "EffectGiftBoxCoin.h"
#include "Mushroom.h"
#include "Leaf.h"

CCoinBrick::CCoinBrick(float x, float y, int quantity) :CGameObject(x, y)
{
	this->quantity = quantity;
	this->initY = y;
 	this->isBoxHidden = 0;
	currentQuantity = 0;
	this->SetState(GIFTBOX_STATE_SHOWING);
}
void CCoinBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == GIFTBOX_STATE_HIDDEN)
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(SPRITE_ID_HIDDEN)->Draw(x, y);
		if (  isBoxHidden == 0)
		{
			isBoxHidden = 1;
		}
		return;
	}
	animations->Get(ANI)->Render(x, y);
	//RenderBoundingBox();
}
void CCoinBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (state == GIFTBOX_STATE_BOUNCE)
	{
		vy += GIFTBOX_GRAVITY * dt;
		y += vy * dt;
	}
	if (y > initY && state == GIFTBOX_STATE_BOUNCE) {
		if (currentQuantity >= quantity)
		{
			SetState(GIFTBOX_STATE_HIDDEN);
		}
		else
		{
			SetState(GIFTBOX_STATE_SHOWING);
		}
		y = initY;
		vy = 0;
	}

	CGameObject::Update(dt);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}
 
void CCoinBrick::OpenCoinBox()
{
	if (state == GIFTBOX_STATE_HIDDEN || state == GIFTBOX_STATE_BOUNCE)
	{
		return;
	}
 
	LPGAMEOBJECT effectCoinBox = new CEffectGiftBoxCoin(x, y - 16);
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	p->AddGameObject(effectCoinBox);
	currentQuantity++;

	SetState(GIFTBOX_STATE_BOUNCE);
	vy = -GIFTBOX_BOUNCE_SPEED;

}
 
void CCoinBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BOX_BBOX_WIDTH / 2 + 2;
	t = y - BOX_BBOX_HEIGHT / 2 + 1;
	r = l + BOX_BBOX_WIDTH;
	b = t + BOX_BBOX_HEIGHT;
}