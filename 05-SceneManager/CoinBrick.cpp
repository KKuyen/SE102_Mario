#include "CoinBrick.h"
#include "PlayScene.h"
#include "EffectGiftBoxCoin.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Koopas.h"

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
	RenderBoundingBox();
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

     // Check for CKoopas objects above this brick
     LPSCENE s = CGame::GetInstance()->GetCurrentScene();
     LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
     if (p)
     {
         vector<LPGAMEOBJECT>& objects = p->GetObjects();
         float l, t, r, b;
         this->GetBoundingBox(l, t, r, b);
         for (auto obj : objects)
         {
              CKoopas* koopas = dynamic_cast<CKoopas*>(obj);
             if (koopas && !koopas->IsDeleted())
             {
                 float kl, kt, kr, kb;
                 koopas->GetBoundingBox(kl, kt, kr, kb);
                 // Check if the bottom of the koopas is above the top of the brick and horizontally overlaps
                 if (kb <= t && kr > l && kl < r)
                 {
                     koopas->SetState(KOOPAS_STATE_SHELL);
                 }
             }
         }
     }

     LPGAMEOBJECT effectCoinBox = new CEffectGiftBoxCoin(x, y - 16);
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