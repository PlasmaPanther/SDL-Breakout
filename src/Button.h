#pragma once
#include "Font.h"

class Button: public Object2D
{
public:
	Button() = default;
	~Button();
	
	void PlaceButton(std::string text, Vector2 _buttonpos, uint32_t buttonwidth, uint32_t buttonheigth);
	void RenderButton();

	bool Clicked(const SDL_Event& e);

private:
	Font button_text;
};

