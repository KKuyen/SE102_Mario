#pragma once

#include "Scene.h"

class CSampleKeyHandler: public CSceneKeyHandler
{
public:
	bool holdingS;
	bool alreadySit;
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSampleKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {
		holdingS = false;
		alreadySit = false;
	};
};
