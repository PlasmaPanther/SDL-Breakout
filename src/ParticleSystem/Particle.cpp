#include "Particle.h"
#include "../TimerModule.h"

Particle::Particle() {
	lifetime = 0;
	starting_lifetime = 0;
	alive = false;
}

void Particle::LifetimeUpdate() {
	float life_decrement = TimerModule::GetDelta() * 1000.0f;
	
	lifetime -= life_decrement;

	if (lifetime <= 0) {
		alive = false;
		lifetime = starting_lifetime; //reset lifetime
	}
}

void Particle::SetLifetime(float ms) {
	lifetime = ms;
	starting_lifetime = lifetime;
}

void Particle::SetAliveStatus(bool status) {
	alive = status;
}

float Particle::GetLifetime() {
	return lifetime;
}

bool Particle::isAlive() {
	return alive;
}