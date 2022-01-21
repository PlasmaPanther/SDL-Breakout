#include "GameOverState.h"
#include "../Application.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "SplashMenu.h"

GameOverState GameOverState::Instance;

bool GameOverState::onEnter() {
	GameOverText.Load("Moonrising.ttf", 32, "Game Over", Colors::RED);
	PlayAgain.Load("Moonrising.ttf", 32, "Would you like to play again?", Colors::RED);

	YesButton.PlaceButton("Yes", Vector2(300, 400), 64, 32);
	NoButton.PlaceButton("No", Vector2(430, 400), 64, 32);
	
	printf("entering game over state\n");
	return true;
}

void GameOverState::Render() {
	GameOverText.DrawText(305, 200);
	PlayAgain.DrawText(120, 300);

	YesButton.RenderButton();
	NoButton.RenderButton();
}

void GameOverState::Update() {
	if (YesButton.Clicked(Application::GetEvent())) {
		StateMachine::switchState(PlayState::GetInstance());
	}

	if (NoButton.Clicked(Application::GetEvent())) {
		StateMachine::switchState(SplashMenu::GetInstance());
	}
}

bool GameOverState::onExit() {
	GameOverText.FreeFont();
	PlayAgain.FreeFont();
	
	printf("left game over state\n");
	return true;
}

GameOverState* GameOverState::GetInstance() {
	return &Instance;
}