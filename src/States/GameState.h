#pragma once
#include <string>

//Game States will inherit from this class
class GameState
{
public:

	virtual ~GameState() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;
	
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

};

