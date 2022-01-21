#include "ParticleEngine.h"
#include <cstdlib>
#include <time.h>

#pragma warning (disable : 4244) //disable conversion warnings

ParticleEngine::ParticleEngine() {
	Spawned = false;
	RandomizedSpeed = false;
	LimitedLife = false;

	particle_Width = 0;
	particle_Height = 0;

	startingX = 0;
	startingY = 0;
}

ParticleEngine::~ParticleEngine() {
	if (!Particles_Vector.empty()) {
		Particles_Vector.clear();
		Particles_Vector.shrink_to_fit();
	}
}

void ParticleEngine::Render() {
	if (Spawned) {
		for (int i = 0; i < Particles_Vector.size(); ++i) {
			if (Particles_Vector[i].isAlive()) {
				Particles_Vector[i].DrawRect(20 * i + 3, 34 * i + 50, 100 * i + 10, 255);
			}
		}
	}
}

void ParticleEngine::Update() {
	srand(time(0));

	if (Spawned) {
		if (RandomizedSpeed == false) {
			for (int i = 0; i < Particles_Vector.size(); ++i) {

				//Randomize X and Y speeds
				int randomX = rand() % 6 + (-3);
				int randomY = rand() % 6 + (-3);

				if (randomX == 0) {
					randomX = 2; //make sure there are no idle particles
				}

				if (randomY == 0) {
					randomY = 2;
				}

				Particles_Vector[i].SetSpeed(Vector2(randomX, randomY)); //apply randomized speed
				RandomizedSpeed = true;
			}
		}

		if (RandomizedSpeed) {
			for (int i = 0; i < Particles_Vector.size(); ++i) {
				if (Particles_Vector[i].isAlive()) {
					Particles_Vector[i].MoveRect(Particles_Vector[i].GetSpeed()); //Move particles by getting applied speed

					//Boundary check (if particles are outside the screen)
					if (Particles_Vector[i].GetRect().x > 800 || Particles_Vector[i].GetRect().x + Particles_Vector[i].GetRect().w < 0 || Particles_Vector[i].GetRect().y + Particles_Vector[i].GetRect().h < 0 || Particles_Vector[i].GetRect().y > 600) {
						Particles_Vector[i].SetAliveStatus(false);
					}
				}
			}
		}

		if (LimitedLife && RandomizedSpeed) {
			for (int i = 0; i < Particles_Vector.size(); ++i) {
				if (Particles_Vector[i].isAlive()) {
					Particles_Vector[i].LifetimeUpdate(); //check to see if a particle is near the end of its life; if it is set its status to dead
				}
			}
		}
	}
}

void ParticleEngine::Update(int x, int y) {
	//This function is the same as the one above except you can pass custom x, y values when particles respawns
	srand(time(0));

	if (Spawned) {
		if (RandomizedSpeed == false) {
			for (int i = 0; i < Particles_Vector.size(); ++i) {

				//Randomize X and Y speeds
				int randomX = rand() % 6 + (-3);
				int randomY = rand() % 6 + (-3);

				Particles_Vector[i].SetSpeed(Vector2(randomX, randomY)); //apply them
				RandomizedSpeed = true;
			}
		}

		if (RandomizedSpeed) {
			for (int i = 0; i < Particles_Vector.size(); i++) {
				if (Particles_Vector[i].isAlive()) {
					Particles_Vector[i].MoveRect(Particles_Vector[i].GetSpeed()); //Move particles by getting applied speed

					//Boundary check
					if (Particles_Vector[i].GetRect().x > 800 || Particles_Vector[i].GetRect().x + Particles_Vector[i].GetRect().w < 0 || Particles_Vector[i].GetRect().y + Particles_Vector[i].GetRect().h < 0 || Particles_Vector[i].GetRect().y > 600) {
						Particles_Vector[i].SetAliveStatus(false);
					}
				}
			}
		}

		if (LimitedLife && RandomizedSpeed) {
			for (int i = 0; i < Particles_Vector.size(); ++i) {
				if (Particles_Vector[i].isAlive()) {
					Particles_Vector[i].LifetimeUpdate();
				}

				if (!Particles_Vector[i].isAlive()) {
					Particles_Vector[i].SetAliveStatus(true);
					Particles_Vector[i].PlaceRect(Vector2(x, y), particle_Width, particle_Height);
				}

			}
		}
	}
}

void ParticleEngine::Spawn(int ammount, int x, int y, int w, int h, bool limitedLife, int lifetime_ms) {
	srand(time(0));

	startingX = x;
	startingY = y;

	particle_Width = w;
	particle_Height = h;

	Particles_Vector.resize(ammount);

	for (int i = 0; i < Particles_Vector.size(); ++i) {
		Particles_Vector[i].PlaceRect(Vector2(startingX + rand() % 35, startingY + rand() % 35), particle_Width, particle_Height);
		Particles_Vector[i].SetLifetime(lifetime_ms + rand() % 250); //randomize lifetime 
		Particles_Vector[i].SetAliveStatus(true);
	}

	Spawned = true;
	RandomizedSpeed = false;
	LimitedLife = limitedLife;
}

void ParticleEngine::Spawn(int ammount, int x, int y, int w, int h) {
	srand(time(0));

	startingX = x;
	startingY = y;

	particle_Width = w;
	particle_Height = h;

	Particles_Vector.resize(ammount);

	for (int i = 0; i < Particles_Vector.size(); ++i) {
		Particles_Vector[i].PlaceRect(Vector2(startingX + rand() % 35, startingY + rand() % 35), particle_Width, particle_Height);
		Particles_Vector[i].SetAliveStatus(true);
	}

	Spawned = true;
	RandomizedSpeed = false;
}

void ParticleEngine::ClearParticles() {
	Particles_Vector.clear();
	Particles_Vector.shrink_to_fit();
}
