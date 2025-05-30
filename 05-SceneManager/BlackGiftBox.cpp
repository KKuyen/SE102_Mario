#include "BlackGiftBox.h"
#include "Leaf.h"
#include "EffectPoint.h"
#include "PlayScene.h"

void CBlackGiftBox::Render() {
	if (isEaten) return;
	int aniId = GetAniId();
	CSprites::GetInstance()->Get(aniId)->Draw(x, y);
}

void CBlackGiftBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GIFTBOX_BBOX_WIDTH / 2 + 1;
	t = y - GIFTBOX_BBOX_HEIGHT / 2;
	r = l + GIFTBOX_BBOX_WIDTH - 1;
	b = t + GIFTBOX_BBOX_HEIGHT;
}

void CBlackGiftBox::OpenGiftBox()
{
	int sprite;
	switch(type)
	{
	case 1: // Mushroom
		sprite = ID_ANI_MUSHROOM_EF;
		break;
	case 2: // Star
		sprite = ID_ANI_STAR_EF;
		break;
	case 3: // Flower
		sprite = ID_ANI_FLOWER_EF;
		break;
	default:
		sprite = ID_ANI_MUSHROOM_EF;
		break;
	}
	LPGAMEOBJECT effectCoinBox = new CEffectPoint(x, y, sprite);
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
	p->PushBackGameObject(effectCoinBox);
	isEaten = true;
}

void CBlackGiftBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - timer_rotate > TIMER_ROTATE)
	{
		timer_rotate = GetTickCount64();
		this->state = this->state + 1;
		if (this->state >= 3)
		{
			this->state = 0;
		}
	}

	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

int CBlackGiftBox::GetAniId()
{
	if (state == GIFTBOX_SPECIAL_STATE_MUSHROOM)
	{
		return ID_ANI_MUSHROOM;
	}
	else if (state == GIFTBOX_SPECIAL_STATE_STAR)
	{
		return ID_ANI_STAR;
	}
	else
		return ID_ANI_FLOWERBLUE;
}
