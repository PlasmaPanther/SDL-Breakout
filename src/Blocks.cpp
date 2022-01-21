#include "Blocks.h"
#include "Player.h"
#include "Ball.h"

#pragma warning (disable : 4244) //disable conversion warnings

void Blocks::PlaceBlocks() {

	player_score = Player::GetScore();
	num_blocks = 64;

	blocks_vector.resize(num_blocks);
	block_ParticlesVector.resize(num_blocks);

	PlayerScoreText.LoadToText("Moonrising.ttf", 48, player_score, Colors::GREEN);
	NumBlocksText.LoadToText("Moonrising.ttf", 48, num_blocks, Colors::GREEN);

	int x_offset = 8, y_offset = 10; //starting coordinates

	for (int i = 0; i < blocks_vector.size(); ++i) {
		
		blocks_vector[i].PlaceRect(Vector2(x_offset, y_offset), 67, 12);

		x_offset += 72; //move each block 72 pixels starting from their top left corner (72 - 67 = 5 pixels apart)
		if (x_offset > 580) {
			y_offset += 40; //move down
			x_offset = 8; //reset x offset
		}
	}
}

void Blocks::Update() {

	for (int i = 0; i < blocks_vector.size(); ++i) {

		if (blocks_vector[i].CircleToRectCollision(Ball::GetBallCollider(), blocks_vector[i].GetRect())) {

			block_hit_sfx.PlaySFX("block.wav", 0, -1);
			
			//Place particles on hit block
			block_ParticlesVector[i].Spawn(16, blocks_vector[i].GetRect().x, blocks_vector[i].GetRect().y, 10, 10, true, 300);

			Vector2 ball_Yspeed = Ball::GetBallSpeed();

			ball_Yspeed.y *= -1; //reverse y speed
			Ball::SetBallSpeed(ball_Yspeed); //apply new speed

			blocks_vector[i].Kill(); //Sets the hit block x, y, w and h to 0
			
			num_blocks -= 1;

			NumBlocksText.ChangeToText(num_blocks, Colors::GREEN);

			//=======Block Scores=======//
			if (i >= 32) { //if the hit block is the 32nd and higher
				player_score += 1; // +1 to the score
			}
			
			if (i <= 31 && i >= 15) { //if the hit block is between the 31st and 15th
				player_score += 3; // +3 to the score
			}

			if (i <= 14) { //if the hit block is lower or the same as the 14th
				player_score += 5; // +5 to the score
			}

			Player::SetScore(player_score);
			PlayerScoreText.ChangeToText(player_score, Colors::GREEN);
			//==========================//
		}

		block_ParticlesVector[i].Update(); //Update particles when a block is hit
	}

	NumBlocksText.DrawText(660, 460); //Draws remaining blocks
	PlayerScoreText.DrawText(660, 290);

	if (num_blocks == 0) {
		this->Reset();
	}
}

void Blocks::Render() {

	for (int i = 0; i < blocks_vector.size(); i++) {
		blocks_vector[i].DrawRect(22 + i * 99, 44 + i * 10, 33 + i * 6, 255);
		block_ParticlesVector[i].Render();
	}
}

void Blocks::Clean() {
	this->NumBlocksText.FreeFont();
	this->PlayerScoreText.FreeFont();
	this->block_hit_sfx.FreeSFX();

	blocks_vector.clear();
	blocks_vector.shrink_to_fit(); //sets vector capacity to 0

	block_ParticlesVector.clear();
	block_ParticlesVector.shrink_to_fit();
}

void Blocks::Reset() {
	num_blocks = 64;
	int x_offset = 8, y_offset = 10; //starting coordinates

	//====used only to reset ball position====
	SDL_Rect tmp_player_rect = Player::GetPlayerRect();
	Circle tmp_circle = Ball::GetBallCollider();
	//========================================

	PlaceCircle(Vector2(tmp_circle.x = tmp_player_rect.x + tmp_player_rect.w / 2, tmp_circle.y = tmp_player_rect.y - 16), 14);

	for (int i = 0; i < blocks_vector.size(); ++i) {
		blocks_vector[i].PlaceRect(Vector2(x_offset, y_offset), 67, 12);
		x_offset += 72; //move each block 72 pixels starting from their top left corner (72 - 67 = 5 pixels apart)
		if (x_offset > 580) {
			y_offset += 36; //move down
			x_offset = 8; //reset x offset
		}
	}
}