#pragma once
#include "GameObject.h"
#include "BreakableBrick.h"

#define BREAKABLE_BRICK_CHAIN_TYPE_HORIZONTAL 1
#define BREAKABLE_BRICK_CHAIN_TYPE_VERTICAL 2

class CBreakableBrickChain : public CGameObject
{
public:
	int chainType; // 1 for horizontal, 2 for vertical
    int length;
    CBreakableBrickChain(float x, float y, int length, int chainType);
    void Render() {
        //RenderBoundingBox();

    
    }
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
        vx = vy = 0;
    }
    void GetBoundingBox(float& l, float& t, float& r, float& b);
};

typedef CBreakableBrickChain* LPBREAKABLEBRICKCHAIN;