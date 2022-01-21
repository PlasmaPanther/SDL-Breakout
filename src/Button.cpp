#include "Button.h"

Button::~Button() {
    this->button_text.FreeFont();
}

bool Button::Clicked(const SDL_Event& e) {
    int16_t mouse_X, mouse_Y;
    
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
    {
        //Get the mouse offsets
        mouse_X = e.motion.x;
        mouse_Y = e.motion.y;

        if (e.button.button == SDL_BUTTON_LEFT) {
            mouse_X = e.button.x; //Gets the x pos of the mouse where the left click happend
            mouse_Y = e.button.y;

            //If the mouse is over the button
            if ((mouse_X > object_rect.x) && (mouse_X < object_rect.x + object_rect.w) && (mouse_Y > object_rect.y) && (mouse_Y < object_rect.y + object_rect.h))
            {
                return true;

            }
        }
    }

    return false;
}

void Button::PlaceButton(std::string text, Vector2 _buttonpos, uint32_t buttonwidth, uint32_t buttonheigth) {
	
	object_rect.x = (int)_buttonpos.x;
	object_rect.y = (int)_buttonpos.y;

	object_rect.w = buttonwidth;
	object_rect.h = buttonheigth;

    button_text.Load("Moonrising.ttf", 32, text, Colors::GREEN);

}

void Button::RenderButton() {
    button_text.DrawText(object_rect.x, object_rect.y);
}