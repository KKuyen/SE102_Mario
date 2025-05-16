#include "HiddenButton.h"
#include "BreakableBrick.h"
#include "GiftBox.h"

void CHiddenButton::Render() {
    if (isActivated==false)
    {
        CAnimations* animations = CAnimations::GetInstance();
        animations->Get(ID_ANI_BREAKABLE_BRICK)->Render(x, y);
        RenderBoundingBox(); // Có thể bật để debug

    }
    else
    {
        CSprites* s = CSprites::GetInstance();
        s->Get(SPRITE_ID_HIDDEN)->Draw(x, y);
        RenderBoundingBox(); // Có thể bật để debug

    }
}

void CHiddenButton::GetBoundingBox(float& l, float& t, float& r, float& b) {
 
    l = x - HIDDEN_BUTTON_BBOX_WIDTH / 2;
    t = y - HIDDEN_BUTTON_BBOX_HEIGHT / 2;
    r = l + HIDDEN_BUTTON_BBOX_WIDTH;
    b = t + HIDDEN_BUTTON_BBOX_HEIGHT;
}