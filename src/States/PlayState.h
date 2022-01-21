#pragma once
#include "GameState.h"
#include "../Ball.h"
#include "../Blocks.h"
#include "../Player.h"

class PlayState: public GameState
{
public:
	void Update();
	void Render();

	bool onEnter();
	bool onExit();

	static PlayState* GetInstance();
	
private:
	static PlayState Instance;
	
	Blocks Blocks;
	Player Player;
	Ball Ball;

	Font Lives;
	Font Score;
	Font Num_Blocks;

	Shape2D Line;
};

