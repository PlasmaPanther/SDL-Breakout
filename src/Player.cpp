#include "Player.h"
#include "Input.h"
#include "States/StateMachine.h"
#include "States/GameOverState.h"

SDL_Rect Player::Player_Rect;
int Player::lives;
uint32_t Player::score;

void Player::Place() {

	m_Player.PlaceRect(Vector2(300, 580), 120, 10);
	Player_Rect = m_Player.GetRect(); //Gets Shape2D Rectangle

	lives = 5;
	score = 0;
}

void Player::Update() {

	if (Input::Keydown(SDL_SCANCODE_RIGHT)) {
		m_Player.MoveRect(Vector2(10, 0));
	}
	else if (Input::Keydown(SDL_SCANCODE_LEFT)) {
		m_Player.MoveRect(Vector2(-10, 0));
	}

	if (m_Player.GetRect().x <= 0) { //Check left side
		m_Player.GetRect().x = 0;
	}

	if (m_Player.GetRect().x + m_Player.GetRect().w >= 580) { //Check right side
		m_Player.GetRect().x = 580 - m_Player.GetRect().w; //and keep in bounds
	}

	if (lives == 0) {
		StateMachine::switchState(GameOverState::GetInstance());
	}

	Player_Rect = m_Player.GetRect(); //Keep tracking player position
}

void Player::Render() {
	m_Player.DrawRect(0, 255, 0, 255);
}

int Player::GetLives() {
	return lives;
}

void Player::SetLives(int val) {
	lives = val;
}

uint32_t Player::GetScore() {
	return score;
}

void Player::SetScore(int val) {
	score = val;
}

SDL_Rect& Player::GetPlayerRect() {
	return Player_Rect;
}
