#pragma once
#include "Shape2D.h"

class Player
{
public:
	Player() = default;
	~Player() = default;

	void Place();

	void Update();
	void Render();

	static int GetLives();
	static void SetLives(int val);

	static uint32_t GetScore();
	static void SetScore(int val);

	static SDL_Rect& GetPlayerRect();

private:
	Shape2D m_Player;

	static SDL_Rect Player_Rect;

	static int lives;

	static uint32_t score;
};

