#include "Button.h"
#include "BreakableBrick.h"

void CButton::Render() {
    if (isActivated)
    {
        if (!isPressed)
        {
            
            CAnimations* animations = CAnimations::GetInstance();
            animations->Get(ID_ANI_BUTTON_IDLE)->Render(x, y);
            //RenderBoundingBox(); // Có thể bật để debug }
        }
        else
        {
            CAnimations* animations = CAnimations::GetInstance();
            animations->Get(ID_ANI_BUTTON_CLOSE)->Render(x, y);
            //RenderBoundingBox(); // Có thể bật để debug }
        }
      
    }
    else
    {

    }
}
void CButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
   
}

void CButton::GetBoundingBox(float& l, float& t, float& r, float& b) {
    if (!isActivated||isPressed) return; // Không có bounding box nếu chưa kích hoạt
    l = x -BUTTON_BBOX_WIDTH / 2;
    t = y -BUTTON_BBOX_HEIGHT / 2;
    r = l + BUTTON_BBOX_WIDTH;
    b = t + BUTTON_BBOX_HEIGHT;
}