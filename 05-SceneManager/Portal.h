#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
#define PORTAL_BBOX_WIDTH 25
#define PORTAL_BBOX_HEIGHT 25
#define PORTAL_SPRITE 190003
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 


public:
	CPortal(float x, float y,int scene_id) : CGameObject(x, y) {
		this->scene_id = scene_id;
	}
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }
};