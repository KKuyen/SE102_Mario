#pragma once

#include "Scene.h"

class CSampleKeyHandler: public CSceneKeyHandler
{
public:
	bool holdingS;
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSampleKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {
		holdingS = false;
	};
};
