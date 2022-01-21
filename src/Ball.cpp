#include "Ball.h"
#include "Player.h"
#include "Input.h"

#pragma warning (disable : 4244) //disable conversion warnings

Circle Ball::ball_collider;
Vector2 Ball::Velocity;

void Ball::PlaceBall() {

	player_rect = Player::GetPlayerRect();

	locked = true;
	speed_changed = false; //Will be used to speed up the ball like in the classic

	m_Ball.PlaceCircle(Vector2(ball_collider.x = player_rect.x + player_rect.w / 2, ball_collider.y = player_rect.y - 16), 14); //place ball_collider ontop of the paddle

	ball_collider = m_Ball.GetCircle(); //Gets Shape2D Circle

	BallParticles.Spawn(16, ball_collider.x, ball_collider.y, 5, 5, true, 300); //prepare particles

	this->Player_Lives.LoadToText("Moonrising.ttf", 48, Player::GetLives(), Colors::GREEN);

	Velocity.x = 7;
	Velocity.y = -7;
}

void Ball::Update() {
	int score = Player::GetScore();
	player_rect = Player::GetPlayerRect();

	if (score >= 30 && speed_changed == false) {
		Velocity.x = 9;
		Velocity.y = -9;

		speed_changed = true; //ensures this if statement doesn't hit again
	}

	if (locked) {
		m_Ball.GetCircle().x = player_rect.x + player_rect.w / 2; //Places the ball on the center of the paddle
		m_Ball.GetCircle().y = player_rect.y - 16; //and right on top of it
	}

	if (Input::Keydown(SDL_SCANCODE_SPACE)) {
		locked = false;
	}

	if (!locked) {
		m_Ball.MoveCircle(Vector2(Velocity.x, Velocity.y));
		ball_collider = m_Ball.GetCircle(); //Get current ball_collider position
		BallParticles.Update(ball_collider.x, ball_collider.y); //so we can place the particles on it


	 //===================Boundary collision=========================//
		if (ball_collider.x + ball_collider.radius >= 580) { //check right side
			ball_collider.x = 580 - ball_collider.radius;
			wall_hit_sfx.PlaySFX("wall.wav", 0, -1);

			Velocity.x *= -1; //reverse X speed
		}

		if (ball_collider.x - ball_collider.radius <= 0) { //check left side
			ball_collider.x = 0 + ball_collider.radius;
			wall_hit_sfx.PlaySFX("wall.wav", 0, -1);

			Velocity.x *= -1;
		}

		if (ball_collider.y - ball_collider.radius <= 0) { //check top side
			ball_collider.y = 0 + ball_collider.radius;
			wall_hit_sfx.PlaySFX("wall.wav", 0, -1);

			Velocity.y *= -1;
		}

		if (ball_collider.y + ball_collider.radius >= 600) { //check bottom side

			locked = true; //place the ball back on the paddle
			Velocity.y *= -1;

			int lives = Player::GetLives();

			lives -= 1;
			Player::SetLives(lives);

			Player_Lives.ChangeToText(lives, Colors::GREEN);
		}
	}

	Player_Lives.DrawText(660, 110);
	//==============================================================//

	//=======================Player Collision======================//
	if (Shape2D::CircleToRectCollision(ball_collider, player_rect) && !locked) { //if the ball_collider is moving and collides with the paddle
		Velocity.y *= -1; //turn it into negative y speed to move up

		paddle_hit_sfx.PlaySFX("paddle.wav", 0, -1);

		if (ball_collider.x >= player_rect.x - player_rect.w && ball_collider.x <= player_rect.x + 30) { //more than 0, less than 30
			Velocity.x = -7; //if left side of the paddle is hit; set x speed to -7(move ball_collider to the left)
			if (speed_changed) {
				Velocity.x = -9;
			}
		}

		if (ball_collider.x >= player_rect.x + 31 && ball_collider.x <= player_rect.x + player_rect.w / 2) { //more than 31, less than 60
			Velocity.x = -4;
		}

		if (ball_collider.x >= player_rect.x + 61 && ball_collider.x <= player_rect.x + 90) { //more than 61, less than 90
			Velocity.x = 4;
		}

		if (ball_collider.x >= player_rect.x + player_rect.w - 30 && ball_collider.x <= player_rect.x + player_rect.w) {
			Velocity.x = 7; //if right side of the paddle is hit; set x speed to 7(move ball_collider to the right)
			if (speed_changed) {
				Velocity.x = 9;
			}
		}

	}
	//=============================================================//
}

void Ball::Render() {
	m_Ball.DrawCircle(0, 255, 255, 255);

	if (!locked) {
		BallParticles.Render(); //render particles only when the ball_collider is moving
	}
}

void Ball::Clean() {
	this->Player_Lives.FreeFont(); //frees the loaded font
	this->paddle_hit_sfx.FreeSFX();
	this->wall_hit_sfx.FreeSFX();

	BallParticles.ClearParticles();
}

Vector2 Ball::GetBallSpeed()
{
	return Velocity;
}

void Ball::SetBallSpeed(Vector2 _vel)
{
	Velocity = _vel;
}

Circle& Ball::GetBallCollider() {
	return ball_collider;
}