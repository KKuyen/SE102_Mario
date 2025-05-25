#pragma once
#include "GameObject.h"
#include "BreakableBrick.h"

#define BREAKABLE_BRICK_CHAIN_TYPE_HORIZONTAL 1
#define BREAKABLE_BRICK_CHAIN_TYPE_VERTICAL 2

class CBreakableBrickChain : public CGameObject
{
public:
    CBreakableBrickChain(float x, float y, int length, int chainType);
    void Render() {}
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};

typedef CBreakableBrickChain* LPBREAKABLEBRICKCHAIN;