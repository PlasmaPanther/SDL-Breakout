#pragma once
#include "../Shape2D.h"

class Particle: public Shape2D //inheriting from this class will allow us to use render, update and more functions
{
public:
	Particle();
	~Particle() = default;
	
	//\brief Returns lifetime of particle
	float GetLifetime();

	//\brief Returns true if particle is alive, false otherwise
	bool isAlive();

	//\brief Sets particle lifetime
	//\param ms - Lifetime in milliseconds
	void SetLifetime(float ms);

	//\brief Sets particle status to either dead or alive
	//\param status - true for alive, false for dead
	void SetAliveStatus(bool status);

	//\brief Uses timer to check if a particle has reached the end of its lifetime
	void LifetimeUpdate();

private:
	float lifetime;
	float starting_lifetime;

	bool alive;
};

