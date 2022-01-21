#pragma once
#include "../Button.h" //includes font
#include "GameState.h"

class GameOverState: public GameState
{
public:
	void Update();
	void Render();

	bool onEnter();
	bool onExit();

	static GameOverState* GetInstance();

private:

	static GameOverState Instance;

	Font GameOverText;
	Font PlayAgain;

	Button YesButton;
	Button NoButton;

};

