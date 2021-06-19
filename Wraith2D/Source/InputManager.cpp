#include "InputManager.h"

std::unordered_set<SDL_Keycode> InputManager::_keysDown;
std::unordered_set<SDL_Keycode> InputManager::_keysUp;
std::unordered_set<SDL_Keycode> InputManager::_keysPressed;

std::unordered_set<int8_t> InputManager::_mouseButtonsDown;
std::unordered_set<int8_t> InputManager::_mouseButtonsUp;
std::unordered_set<int8_t> InputManager::_mouseButtonsPressed;

Vector2 InputManager::_mousePosition;
Vector2 InputManager::_mouseDelta;
Vector2 InputManager::_mouseWheel;

void InputManager::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (!_keysPressed.count(event.key.keysym.sym))
		{
			_keysPressed.emplace(event.key.keysym.sym);
		}

		_keysDown.emplace(event.key.keysym.sym);
		_keysUp.erase(event.key.keysym.sym);
		break;

	case SDL_KEYUP:
		_keysUp.emplace(event.key.keysym.sym);
		_keysDown.erase(event.key.keysym.sym);
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (!_mouseButtonsPressed.count(event.button.button))
		{
			_mouseButtonsPressed.emplace(event.button.button);
		}

		_mouseButtonsDown.emplace(event.button.button);
		_mouseButtonsUp.erase(event.button.button);
		break;

	case SDL_MOUSEBUTTONUP:
		_mouseButtonsUp.emplace(event.button.button);
		_mouseButtonsDown.erase(event.button.button);
		break;

	case SDL_MOUSEMOTION:
		_mousePosition.x = static_cast<int>(event.motion.x);
		_mousePosition.y = static_cast<int>(event.motion.y);

		_mouseDelta.x = static_cast<int>(event.motion.xrel);
		_mouseDelta.y = static_cast<int>(event.motion.yrel);
		break;

	case SDL_MOUSEWHEEL:
		_mouseWheel.x = static_cast<int>(event.wheel.x);
		_mouseWheel.y = static_cast<int>(event.wheel.y);
		break;

	default:
		break;
	}
}

void InputManager::clearEvents()
{
	_keysUp.clear();
	_keysDown.clear();

	_mouseButtonsDown.clear();
	_mouseButtonsUp.clear();

	_mousePosition = { 0.f, 0.f };
	_mouseDelta = { 0.f, 0.f };
	_mouseWheel = { 0.f, 0.f };
}

void InputManager::clearFrameEvents()
{
	_keysPressed.clear();
	_mouseButtonsPressed.clear();
}
