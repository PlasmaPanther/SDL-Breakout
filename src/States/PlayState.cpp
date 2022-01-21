#include "PlayState.h"
#include "StateMachine.h"
#include "../Input.h"

PlayState PlayState::Instance;

bool PlayState::onEnter() {
	Player.Place();
	Ball.PlaceBall();
	Blocks.PlaceBlocks();

	Score.Load("Moonrising.ttf", 48, "Score", Colors::WHITE);
	Lives.Load("Moonrising.ttf", 48, "Lives", Colors::WHITE);
	Num_Blocks.Load("Moonrising.ttf", 30, "Blocks left", Colors::WHITE);
	
	printf("Entering Play state\n");
	return true;
}

void PlayState::Update() {

	Player.Update();
 	Ball.Update();
	Blocks.Update();

	
}

void PlayState::Render() {
	
	Blocks.Render();
	Player.Render();
	Ball.Render();

	Score.DrawText(600, 220); //Draws the word "score"...that's it
	Lives.DrawText(615, 50);
	Num_Blocks.DrawText(587, 400);

	Line.DrawLine(Vector2(583, 0), Vector2(583, 600), Colors::GREEN);
}

bool PlayState::onExit() {

	Score.FreeFont(); //Frees the font
	Lives.FreeFont();
	Num_Blocks.FreeFont();

	Ball.Clean(); //these just free the loaded fonts and sfx inside the classes
	Blocks.Clean();

	printf("Playstate exited\n");
	return true;
}

PlayState* PlayState::GetInstance() {
	return &Instance;
}