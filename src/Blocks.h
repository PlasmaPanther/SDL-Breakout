#pragma once
#include "AudioPlayer.h"
#include "Font.h"
#include "ParticleSystem/ParticleEngine.h"

class Blocks: public Shape2D
{
public:
	Blocks() = default;
	~Blocks() = default;

	void PlaceBlocks();

	void Update();
	void Render();

	void Clean();

private:

	void Reset();

	int num_blocks;
	Font NumBlocksText;

	Font PlayerScoreText; //will be used to render the player score to text
	int player_score; //this will hold the player score; its easier to control it from here

	std::vector<Shape2D>blocks_vector; //and this will hold the blocks
	std::vector<ParticleEngine> block_ParticlesVector; //this will hold particles so every block has one

	AudioPlayer block_hit_sfx;

};

