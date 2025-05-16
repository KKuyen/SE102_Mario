#include "DarkBackground.h"

#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"

void CDarkBackground::Render()
{
    if (widthCells <= 0 || heightCells <= 0) return;

    CSprites* s = CSprites::GetInstance();

    for (int row = 0; row < heightCells; row++)
    {
        for (int col = 0; col < widthCells; col++)
        {
            int spriteId;
            if (col == 0)
            {
				spriteId = EDGE_SPRITE_ID;
            }
            else
            {
				spriteId = MAIN_SPRITE_ID;
            }

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

void CDarkBackground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    float CELL_WIDTH_div_2 = CELL_WIDTH / 2;
    l = x - CELL_WIDTH_div_2;
    t = y - CELL_HEIGHT / 2;
    r = l + CELL_WIDTH * this->widthCells;
    b = t + CELL_HEIGHT * this->heightCells;
}

int CDarkBackground::IsDirectionColliable(float nx, float ny)
{
    if (nx == 0 && ny == -1) return 1;
    else return 0;
}