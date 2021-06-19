#pragma once

#include <unordered_set>
#include <SDL.h>
#include "Math/Vector2.h"

class InputManager
{
public:
	/// <summary>
	/// Handles all input events from an SDL_Event
	/// </summary>
	/// <param name="event">The event</param>
	static void handleEvent(const SDL_Event& event);

	/// <summary>
	/// Checks whether a key is down in the current frame.
	/// </summary>
	/// <param name="key">The key</param>
	/// <returns>True if it is, false if not</returns>
	inline static bool keyDown(int key) { return _keysDown.count(key) != 0; }

	/// <summary>
	/// Checks whether a key is up in the current frame.
	/// </summary>
	/// <param name="key">The key</param>
	/// <returns>True if it is, false if not</returns>
	inline static bool keyUp(int key) { return _keysUp.count(key) != 0; }

	/// <summary>
	/// Checks if a key was pressed this frame.
	/// This only returns true in the EXACT frame the key was pressed.
	/// </summary>
	/// <param name="key">The key</param>
	/// <returns>True if it was, false if not</returns>
	inline static bool keyPressed(int key) { return _keysPressed.count(key) != 0; }

	/// <summary>
	/// Checks whether a mouse button is down in the current frame.
	/// </summary>
	/// <param name="button">The mouse button</param>
	/// <returns>true if it was, false if not</returns>
	inline static bool mouseButtonDown(int8_t button) { return _mouseButtonsDown.count(button) != 0; }

	/// <summary>
	/// Checks whether a mouse button is up in the current frame.
	/// </summary>
	/// <param name="button">The mouse button</param>
	/// <returns>True if it is, false if not</returns>
	inline static bool mouseButtonUp(int8_t button) { return _mouseButtonsUp.count(button) != 0; }

	/// <summary>
	/// Checks whether a mouse button was pressed this frame.
	/// This only returns true in the EXACT frame the button was pressed.
	/// </summary>
	/// <param name="button">The mouse button</param>
	/// <returns>True if it was, false if not</returns>
	inline static bool mouseButtonPressed(int8_t button) { return _mouseButtonsPressed.count(button) != 0; }

	/// <summary>
	/// Returns the current mouse position.
	/// </summary>
	/// <returns>A Vector2 with the mouse position</returns>
	inline static Vector2 mousePosition() { return _mousePosition; }

	/// <summary>
	/// Returns the relative movement of the mouse this frame.
	/// </summary>
	/// <returns>A Vector2 with the relative mouse movement</returns>
	inline static Vector2 mouseDelta() { return _mouseDelta; }

	/// <summary>
	//	Returns the mouse wheel movement.
	/// </summary>
	/// <returns>A Vector2 with the mouse movement in the form (horizontal,vertical)</returns>
	inline static Vector2 mouseWheel() { return _mouseWheel; }

	/// <summary>
	/// Clears all input events.
	/// </summary>
	static void clearEvents();

	/// <summary>
	/// Clears all input events that are only valid for one frame.
	/// </summary>
	static void clearFrameEvents();

private:
	static std::unordered_set<int> _keysDown;
	static std::unordered_set<int> _keysUp;
	static std::unordered_set<int> _keysPressed;

	static std::unordered_set<int8_t> _mouseButtonsDown;
	static std::unordered_set<int8_t> _mouseButtonsUp;
	static std::unordered_set<int8_t> _mouseButtonsPressed;

	static Vector2 _mousePosition;
	static Vector2 _mouseDelta;
	static Vector2 _mouseWheel;
};
