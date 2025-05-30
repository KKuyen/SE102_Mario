#include "HiddenButton.h"
#include "BreakableBrick.h"
#include "GiftBox.h"

void CHiddenButton::Render() {
    if (isActivated==false)
    {
        CAnimations* animations = CAnimations::GetInstance();
        animations->Get(ID_ANI_BREAKABLE_BRICK)->Render(x, y);
        //RenderBoundingBox();  

    }
    else
    {
        if (type == HIDDEN_BUTTON_TYPE_BUTTON)
        {
            CSprites* s = CSprites::GetInstance();
            s->Get(SPRITE_ID_HIDDEN)->Draw(x, y);
            //RenderBoundingBox();  
        }
        else
        {

        }
        

    }
}

void CHiddenButton::GetBoundingBox(float& l, float& t, float& r, float& b) {  
   if (type != HIDDEN_BUTTON_TYPE_BUTTON && isActivated == true) // Fixed assignment operator '=' to comparison operator '=='  
   {  
      
   }
   else
   {
       l = x - HIDDEN_BUTTON_BBOX_WIDTH / 2;
       t = y - HIDDEN_BUTTON_BBOX_HEIGHT / 2 +1;
       r = l + HIDDEN_BUTTON_BBOX_WIDTH;
       b = t + HIDDEN_BUTTON_BBOX_HEIGHT;
   }
 
  
}