#include "BreakableBrickChain.h"
#include "Game.h"
#include "PlayScene.h"

CBreakableBrickChain::CBreakableBrickChain(float x, float y, int length, int chainType)
    : CGameObject(x, y)
{
    float brickWidth = BREAKABLE_BRICK_BBOX_WIDTH;
    float brickHeight = BREAKABLE_BRICK_BBOX_HEIGHT;

    // Create bricks based on chain type
    CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    for (int i = 0; i < length; i++)
    {
        float brickX = x;
        float brickY = y;

        if (chainType == BREAKABLE_BRICK_CHAIN_TYPE_HORIZONTAL)
        {
            brickX += i * brickWidth;
        }
        else // BREAKABLE_BRICK_CHAIN_TYPE_VERTICAL
        {
            brickY += i * brickHeight;
        }

        CBreakableBrick* brick = new CBreakableBrick(brickX, brickY);
        scene->PushBackGameObject(brick); // Add each brick to the scene
    }
}
