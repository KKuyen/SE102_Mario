#pragma once

#include "GameObject.h"


#define CELL_WIDTH 16
#define CELL_HEIGHT 16
#define PINK_BASE_ID 70000
#define BLUE_BASE_ID 71000
#define GREEN_BASE_ID 72000
#define WHITE_BASE_ID 73000
#define SHADOW_BASE_ID 74000
#define SHADOW_END_ID 75000



class CColorBox : public CGameObject
{
protected:
    int widthCells;      
    int heightCells;     
    int baseSpriteId;   

public:
    bool isPlatform;
    CColorBox(float x, float y, int widthCells, int heightCells,   int color, bool isPlatform = 0) : CGameObject(x, y)
    {
        this->widthCells = widthCells;
        this->heightCells = heightCells;
        switch (color)
        {
        case 0: baseSpriteId = PINK_BASE_ID; break; // Pink
        case 1: baseSpriteId = BLUE_BASE_ID; break; // Blue
        case 2: baseSpriteId = GREEN_BASE_ID; break; // Green
        case 3: baseSpriteId = WHITE_BASE_ID; break; // White
        default: baseSpriteId = BLUE_BASE_ID; break; // Blue
        }
        this->isPlatform = isPlatform;
    }

    void Render();
    void Update(DWORD dt) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b);

    int IsDirectionColliable(float nx, float ny);
    int IsBlocking() {
        return 1;
    }
};