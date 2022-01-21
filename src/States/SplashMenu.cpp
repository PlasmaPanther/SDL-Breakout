#include "SplashMenu.h"
#include "../Input.h"
#include "StateMachine.h"
#include "PlayState.h"
#include "../Application.h"

SplashMenu SplashMenu::Instance;

bool SplashMenu::onEnter() {
	Title.Load("Moonrising.ttf", 48, "Breakout", Colors::RED);

	PressEnterKey.Load("Moonrising.ttf", 28, "Press Enter key to start", Colors::RED);
	PressExitKey.Load("Moonrising.ttf", 28, "Press Esc key to exit", Colors::RED);

	printf("Entering Splash Menu\n");
	
	return true;
}

void SplashMenu::Update() {

	if (Input::Keydown(SDL_SCANCODE_RETURN)) {
		StateMachine::switchState(PlayState::GetInstance());
	}

	if(Input::Keydown(SDL_SCANCODE_ESCAPE)){
		Application::ShutDown();
	}

}

void SplashMenu::Render() {
	Title.DrawText(280, 200);

	PressEnterKey.DrawText(220, 300);
	PressExitKey.DrawText(250, 400);

}

bool SplashMenu::onExit() {
	Title.FreeFont();

	PressEnterKey.FreeFont();
	PressExitKey.FreeFont();

	printf("Exiting Splash menu\n");
	return true;
}

SplashMenu* SplashMenu::GetInstance() {
	return &Instance;
}