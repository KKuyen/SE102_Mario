#pragma once

#include "GameObject.h"


#define CELL_WIDTH 16
#define CELL_HEIGHT 16

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
        case 0: baseSpriteId = 70000; break; // Pink
        case 1: baseSpriteId = 71000; break; // Blue
        case 2: baseSpriteId = 72000; break; // Green
        case 3: baseSpriteId = 73000; break; // White
        default: baseSpriteId = 71000; break; // Blue
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