#include "NumberText.h"
#include "debug.h"


void CNumberText::Render() {
	if (isPMeter) {
        CSprites* s = CSprites::GetInstance();
        CAnimations* animations = CAnimations::GetInstance();
        animations->Get(NUMBER_TEXT_P_ANI)->Render(x, y);

    }
	else {
        CSprite* sprite = CSprites::GetInstance()->Get(idSprite);
        if (sprite) {
            sprite->Draw(x, y);
        }
        else {
            DebugOut(L"[ERROR] Sprite id %d not found in CNumberText::Render\n", idSprite);
        }
	}
}

void CNumberText::SetIdSprite(int idSp)
{
	this->idSprite = idSp;
}