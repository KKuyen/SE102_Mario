#include "EffectGiftBoxCoin.h"
#include "PlayScene.h"
#include "EffectPoint.h"

void CEffectGiftBoxCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COINBOX)->Render(x, y);

	//RenderBoundingBox();
}

void CEffectGiftBoxCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - EF_COINBOX_WIDTH / 2;
	t = y - EF_COINBOX_HEIGHT / 2;
	r = l + EF_COINBOX_WIDTH - 1;
	b = t + EF_COINBOX_HEIGHT;
}

void CEffectGiftBoxCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += COINBOX_GRAVITY * dt;
	y += vy * dt;
	if (y > initY) {
		if (!calledEffectPoint) {
			calledEffectPoint = true;
			EffectPoint();
		}
	}
	CGameObject::Update(dt, coObjects);
}

void CEffectGiftBoxCoin::EffectPoint() {
	if (calledEffectPoint = true) {
		LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 100);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->AddGameObject(effectPoint);

		this->Delete();
	}
}