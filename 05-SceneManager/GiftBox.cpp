#include "GiftBox.h"
#include "PlayScene.h"
#include "EffectGiftBoxCoin.h"
#include "Mushroom.h"

CGiftBox::CGiftBox(float x, float y, int animationId, int type) :CGameObject(x, y)
{
	this->animationId = animationId;
	this->initY = y;
	this->type = type;
	this->SetState(GIFTBOX_STATE_SHOWING);
}
void CGiftBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == GIFTBOX_STATE_HIDDEN)
	{
		CSprites* s = CSprites::GetInstance();
		s->Get( SPRITE_ID_HIDDEN)->Draw(x, y);
		return;
	}
	animations->Get(this->animationId)->Render(x, y);
	//RenderBoundingBox();
}
void CGiftBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (state == GIFTBOX_STATE_BOUNCE)
	{
		vy += GIFTBOX_GRAVITY * dt;
		y += vy * dt;
	}
	if (y > initY && state == GIFTBOX_STATE_BOUNCE) {
		SetState(GIFTBOX_STATE_HIDDEN);
		y = initY;
	}
	CGameObject::Update(dt);
	//CCollision::GetInstance()->Process(this, dt, coObjects);

}
void CGiftBox::Open()
{
	if (state == GIFTBOX_STATE_HIDDEN || state==GIFTBOX_STATE_BOUNCE)
	{
		return;
	}
	OpenGiftBox();
	SetState(GIFTBOX_STATE_BOUNCE);
	vy = -GIFTBOX_BOUNCE_SPEED;
}
void CGiftBox::OpenGiftBox()
{
	if (this->type == 0){
		LPGAMEOBJECT effectCoinBox = new CEffectGiftBoxCoin(x, y - 16);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddGameObject(effectCoinBox);
	}
	else if (this->type == 1)
	{
		LPGAMEOBJECT mushroom = new CMushroom(x, y - 16);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddGameObject(mushroom);
	}
	
		
}
void CGiftBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BOX_BBOX_WIDTH / 2 + 2;
	t = y - BOX_BBOX_HEIGHT / 2+1;
	r = l + BOX_BBOX_WIDTH;
	b = t + BOX_BBOX_HEIGHT;
}