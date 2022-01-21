#pragma once
#include "Shape2D.h"
#include "AudioPlayer.h"
#include "Font.h"
#include "ParticleSystem/ParticleEngine.h"

class Ball
{
public:
	Ball() = default;
	~Ball() = default;

	void PlaceBall();

	void Update();
	void Render();

	void Clean();

	static Vector2 GetBallSpeed();

	static void SetBallSpeed(Vector2 _vel);

	static Circle& GetBallCollider();

private:

	Shape2D m_Ball;

	static Circle ball_collider;

	AudioPlayer paddle_hit_sfx;
	AudioPlayer wall_hit_sfx;

	SDL_Rect player_rect;

	Font Player_Lives;

	ParticleEngine BallParticles;

	static Vector2 Velocity;

	bool locked;
	bool speed_changed;

};

