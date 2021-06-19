#include "Button.h"
#include "../../InputManager.h"
#include "../../Math/Vector2.h"

bool Button::mouseHovering()
{
	Vector2 mousePos = InputManager::mousePosition();

	return mousePos.x > _sprite->dstRect()->x && mousePos.x < _sprite->dstRect()->x + _sprite->dstRect()->w
		&& mousePos.y > _sprite->dstRect()->y && mousePos.y < _sprite->dstRect()->y + _sprite->dstRect()->h;
}

bool Button::buttonDown()
{
	return mouseHovering() && InputManager::mouseButtonDown(SDL_BUTTON_LEFT);
}

bool Button::buttonReleased()
{
	return wasPressed() && InputManager::mouseButtonUp(SDL_BUTTON_LEFT);;
}
