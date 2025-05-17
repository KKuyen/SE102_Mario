#include "GiftBox.h"
#include "PlayScene.h"
#include "EffectGiftBoxCoin.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "GreenMushroom.h"

CGiftBox::CGiftBox(float x, float y, int animationId, int type) :CGameObject(x, y)
{
	this->animationId = animationId;
	this->initY = y;
	this->type = type;
	this->isBoxHidden = 0;
	this->SetState(GIFTBOX_STATE_SHOWING);
}
void CGiftBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == GIFTBOX_STATE_HIDDEN)
	{
		CSprites* s = CSprites::GetInstance();
		s->Get( SPRITE_ID_HIDDEN)->Draw(x, y);
		if (type == 1 && isBoxHidden==0)
		{
			isBoxHidden = 1;
 		}
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
		vy = 0;
	}
	if (type == 1 && state == GIFTBOX_STATE_HIDDEN && isBoxHidden == 1)
	{
		OpenMushroomBox(mario);
		isBoxHidden = 2;
	}
	 
	CGameObject::Update(dt);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}
void CGiftBox::Open(CMario* mario)
{
	this->mario = mario;
	if (state == GIFTBOX_STATE_HIDDEN || state==GIFTBOX_STATE_BOUNCE)
	{
		return;
	}
	if (type == 0)
	{
		OpenCoinBox();
	}
	else if (type == 2)
	{
		if (mario->level == MARIO_LEVEL_SMALL)
		{
			OpenMushroomBox(mario);
		}
		else
		{
			OpenLeafBox();
		}
 	}
	else if (type == 3)
	{
		OpenGreenMushroomBox(mario);
	}
 	SetState(GIFTBOX_STATE_BOUNCE);
	vy = -GIFTBOX_BOUNCE_SPEED;
}
//void CGiftBox::Open()
//{
//	if (state == GIFTBOX_STATE_HIDDEN || state==GIFTBOX_STATE_BOUNCE)
//	{
//		return;
//	}
//	if (type == 0)
//	{
//		OpenCoinBox();
//	}
//	SetState(GIFTBOX_STATE_BOUNCE);
//	vy = -GIFTBOX_BOUNCE_SPEED;
//}
void CGiftBox::OpenCoinBox()
{
 		LPGAMEOBJECT effectCoinBox = new CEffectGiftBoxCoin(x, y -16 );
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddGameObject(effectCoinBox);
 
	
		
}
void CGiftBox::OpenLeafBox()
{
	LPGAMEOBJECT leaf = new CLeaf(x, y);
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	p->PushBackGameObject(leaf);
}
void CGiftBox::OpenMushroomBox(CMario* mario)
{
	LPGAMEOBJECT mushroom = new CMushroom(x, y, mario);
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	p->AddGameObject(mushroom);
}
void CGiftBox::OpenGreenMushroomBox(CMario* mario)
{
	LPGAMEOBJECT mushroom = new CGreenMushroom(x, y, mario);
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	p->AddGameObject(mushroom);
}

void CGiftBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BOX_BBOX_WIDTH / 2 + 2;
	t = y - BOX_BBOX_HEIGHT / 2+1;
	r = l + BOX_BBOX_WIDTH;
	b = t + BOX_BBOX_HEIGHT;
}