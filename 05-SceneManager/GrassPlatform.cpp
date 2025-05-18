#include "GrassPlatform.h"

#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"

void CGrassPlatform::Render()
{
    if (widthCells <= 0 || heightCells <= 0) return;

    CSprites* s = CSprites::GetInstance();

    for (int row = 0; row < heightCells; row++)
    {
        for (int col = 0; col < widthCells; col++)
        {
            int spriteIndex;
            if (row == 0)
            {
                if (col == 0)
                    spriteIndex = 1;
                else if (col == widthCells - 1)
                    spriteIndex = 3;
                else
                    spriteIndex = 2;
            }
            else
            {
                if (col == 0)
                    spriteIndex = 4;
                else if (col == widthCells - 1)
                    spriteIndex = 6;
                else
                    spriteIndex = 5;
            }

            int spriteId = baseSpriteId + spriteIndex;
            LPSPRITE sprite = s->Get(spriteId);
            if (sprite == nullptr)
            {
                return;
            }
            float renderX = x + col * CELL_WIDTH;
            float renderY = y + row * CELL_HEIGHT;
            sprite->Draw(renderX, renderY);
        }
    }
}

void CGrassPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    float CELL_WIDTH_div_2 = CELL_WIDTH / 2;
    l = x - CELL_WIDTH_div_2- CELL_WIDTH;
    t = y - CELL_HEIGHT / 2;
    r = l + CELL_WIDTH * this->widthCells ;
    b = t + CELL_HEIGHT * this->heightCells;
}

int CGrassPlatform::IsDirectionColliable(float nx, float ny)
{
    if (nx == 0 && ny == -1) return 1;
    else return 0;
}