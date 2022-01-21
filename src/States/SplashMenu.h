#pragma once
#include "GameState.h"
#include "../Font.h"

class SplashMenu: public GameState
{
public:

	void Update();
	void Render();

	bool onEnter();
	bool onExit();

	static SplashMenu* GetInstance();

private:
	static SplashMenu Instance;

	Font Title;

	Font PressEnterKey;
	Font PressExitKey;
};

