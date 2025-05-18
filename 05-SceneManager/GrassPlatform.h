#pragma once

#include "GameObject.h"


#define CELL_WIDTH 16
#define CELL_HEIGHT 16

class CGrassPlatform : public CGameObject
{
protected:
    int widthCells;
    int heightCells;
    int baseSpriteId;

public:
    bool isPlatform;
    CGrassPlatform(float x, float y, int widthCells, int heightCells,  bool isPlatform = 0) : CGameObject(x, y)
    {
        this->widthCells = widthCells;
        this->heightCells = heightCells;
        this->isPlatform = isPlatform;
        this->baseSpriteId = 250000;
    }

    void Render();
    void Update(DWORD dt) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b);

    int IsDirectionColliable(float nx, float ny);
    int IsBlocking() {
        return 1;
    }
};