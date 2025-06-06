#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_HIDDEN_BUTTON 12000 // ID cho animation của Hidden Button
#define HIDDEN_BUTTON_WIDTH 15
#define HIDDEN_BUTTON_BBOX_WIDTH 15
#define HIDDEN_BUTTON_BBOX_HEIGHT 15
#define HIDDEN_BUTTON_TYPE_BUTTON 1
#define HIDDEN_BUTTON_TYPE_GIFT_BOX_LEAF 2
#define HIDDEN_BUTTON_TYPE_GIFT_BOX_GREEN_MUSHROOM 3
class CHiddenButton : public CGameObject {
protected:
   // Trạng thái nút đã được kích hoạt hay chưa

public:
    float type;
    bool isActivated;
    CHiddenButton(float x, float y, float type) : CGameObject(x, y) {
        isActivated = false; // Mặc định chưa kích hoạt
        this->type = type;
    }

    void Render();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    int IsBlocking() { return 1; } // Không chặn va chạm
    int IsCollidable() { return 1; } // Chỉ va chạm khi đã kích hoạt
    void Activate() { isActivated = true; } // Kích hoạt nút
};