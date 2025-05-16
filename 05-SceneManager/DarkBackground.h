#pragma once

#include "GameObject.h"


#define CELL_WIDTH 16
#define CELL_HEIGHT 16
#define EDGE_SPRITE_ID 190001
#define MAIN_SPRITE_ID 190002

class CDarkBackground : public CGameObject
{
protected:
    int widthCells;
    int heightCells;

public:
    bool isPlatform;
    CDarkBackground(float x, float y, int widthCells, int heightCells) : CGameObject(x, y)
    {
        this->widthCells = widthCells;
        this->heightCells = heightCells;
    }

    void Render();
    void Update(DWORD dt) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b);

    int IsDirectionColliable(float nx, float ny);
    int IsBlocking() {
        return 0;
    }
};