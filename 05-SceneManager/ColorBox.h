#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CColorBox : public CGameObject
{
protected:
    int widthCells;      // S? ô theo chi?u ngang
    int heightCells;     // S? ô theo chi?u cao
    float cellWidth;
    float cellHeight;
    int baseSpriteId;   // Sprite ID c? s? cho màu (ví d?: 70000 cho Pink)

public:
    bool isPlatform;
    CColorBox(float x, float y, int widthCells, int heightCells, float cellWidth, float cellHeight, int color, bool isPlatform = 0) : CGameObject(x, y)
    {
        this->widthCells = widthCells;
        this->heightCells = heightCells;
        this->cellWidth = cellWidth;
        this->cellHeight = cellHeight;
        // Ánh x? màu sang baseSpriteId
        switch (color)
        {
        case 0: baseSpriteId = 70000; break; // Pink
        case 1: baseSpriteId = 71000; break; // Blue
        case 2: baseSpriteId = 72000; break; // Green
        case 3: baseSpriteId = 73000; break; // White
        default: baseSpriteId = 71000; break; // Default là Blue
        }
        this->isPlatform = isPlatform;
    }

    void Render();
    void Update(DWORD dt) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b);

    int IsDirectionColliable(float nx, float ny);
    int IsBlocking() {
        if (baseSpriteId % 10000 == 70000 || baseSpriteId % 10000 == 71000 || baseSpriteId % 10000 == 72000 || baseSpriteId % 10000 == 73000)
            return 1;
        return 0;
    }
};