#pragma once
#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define BUTTON_WIDTH 16
#define BUTTON_BBOX_WIDTH 16
#define BUTTON_BBOX_HEIGHT 16
#define ID_ANI_BUTTON_IDLE 14300
#define ID_ANI_BUTTON_CLOSE 14400
#define BUTTON_APPEAR_DURATION 1000
class CButton : public CGameObject {
protected:
   
public:
    bool isActivated; // Trạng thái nút đã được kích hoạt hay chưa
    bool isPressed;                   // Whether the button has been pressed by Mario

    CButton(float x, float y) : CGameObject(x, y) {
        isActivated = true; // Mặc định chưa kích hoạt
        isPressed = false;            // Initially not pressed
                 // Initialize appear start time
    }

    void Render();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    int IsBlocking() { return 1; } // Không chặn va chạm
    int IsCollidable() { return isActivated ? 1 : 0; } // Chỉ va chạm khi đã kích hoạt
    void Activate() { isActivated = true; 
  
    } // Kích hoạt nút
};