#include "ColorBox.h"

#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"

void CColorBox::Render()
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
			else if (row == heightCells - 1)
			{
                if (col == 0)
                    spriteIndex = 7;
                else if (col == widthCells - 1)
                    spriteIndex = 9;
                else
                    spriteIndex = 8;
				
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

    const float SHADOW_CELL_SIZE = 8.0f;
    float shadowX = x + widthCells * CELL_WIDTH - 4;
    float shadowY = y + 4;

    for (int row = 0; row * SHADOW_CELL_SIZE < heightCells * 16 - 8; row++)
    {
        int shadowSpriteId;
        if (row == 0)
            shadowSpriteId = SHADOW_BASE_ID;
        else if (row == heightCells - 1)
            shadowSpriteId = SHADOW_END_ID;
        else
            shadowSpriteId = SHADOW_END_ID;

        LPSPRITE shadowSprite = s->Get(shadowSpriteId);
        if (shadowSprite == nullptr)
        {
            return;
        }

        float renderShadowX = shadowX;
        float renderShadowY = shadowY + row * SHADOW_CELL_SIZE;
        shadowSprite->Draw(renderShadowX, renderShadowY);
    }
}

void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    float CELL_WIDTH_div_2 = CELL_WIDTH / 2;
    l = x - CELL_WIDTH_div_2;
    t = y - CELL_HEIGHT / 2;
    r = l + CELL_WIDTH * this->widthCells - 6.0f;
    b = t + CELL_HEIGHT * this->heightCells;
}

int CColorBox::IsDirectionColliable(float nx, float ny)
{
    if (nx == 0 && ny == -1) return 1;
    else return 0;
}