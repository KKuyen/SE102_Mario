#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_HIDDEN_BUTTON 12000 // ID cho animation của Hidden Button
#define HIDDEN_BUTTON_WIDTH 16
#define HIDDEN_BUTTON_BBOX_WIDTH 16
#define HIDDEN_BUTTON_BBOX_HEIGHT 16

class CHiddenButton : public CGameObject {
protected:
   // Trạng thái nút đã được kích hoạt hay chưa

public:
    bool isActivated;
    CHiddenButton(float x, float y) : CGameObject(x, y) {
        isActivated = false; // Mặc định chưa kích hoạt
    }

    void Render();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    int IsBlocking() { return 1; } // Không chặn va chạm
    int IsCollidable() { return 1; } // Chỉ va chạm khi đã kích hoạt
    void Activate() { isActivated = true; } // Kích hoạt nút
};