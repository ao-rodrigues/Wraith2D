#pragma once

#include "../ECS.h"
#include "Sprite.h"

class Button : public Component
{
public:
	Button() 
		: _defaultTextureID("")
		, _hoverTextureID("")
		, _downTextureID("")
	{}

	Button(const std::string& defaultTextureID, const std::string& hoverTextureID, const std::string& downTextureID)
		: _defaultTextureID(defaultTextureID)
		, _hoverTextureID(hoverTextureID)
		, _downTextureID(downTextureID)
	{ }

	void init() override
	{
		_sprite = &entity->getComponent<Sprite>();
	}

	/// <summary>
	/// Returns the texture ID of the button in its default state.
	/// </summary>
	/// <returns>The default texture ID</returns>
	inline std::string getDefaultTextureID() { return _defaultTextureID; }

	/// <summary>
	/// Sets the texture ID of the Button in its default state.
	/// </summary>
	/// <param name="defaultTextureID">The new texture ID</param>
	inline void setDefaultTextureID(const std::string& defaultTextureID) { _defaultTextureID = defaultTextureID; }

	/// <summary>
	/// Returns the texture ID of the button in its hovered state.
	/// </summary>
	/// <returns>The hover texture ID</returns>
	inline std::string getHoverTextureID() { return _hoverTextureID; }

	/// <summary>
	/// Sets the texture ID of the Button in its hovered state.
	/// </summary>
	/// <param name="hoverTextureID">The new texture ID</param>
	inline void setHoverTextureID(const std::string hoverTextureID) { _hoverTextureID = hoverTextureID; }

	/// <summary>
	/// Returns the texture ID of the button in its down state.
	/// </summary>
	/// <returns>The down texture ID</returns>
	inline std::string getDownTextureID() { return _downTextureID; }

	/// <summary>
	/// Sets the texture ID of the Button in its down state.
	/// </summary>
	/// <param name="downTextureID">The new texture ID</param>
	inline void setDownTextureID(const std::string& downTextureID) { _downTextureID = downTextureID; }

	/// <summary>
	/// Checks whether the button was pressed or not.
	/// </summary>
	/// <returns>True if it was, false if not</returns>
	inline bool wasPressed() { return _pressed; }

	/// <summary>
	/// Sets the button's pressed state.
	/// </summary>
	/// <param name="pressed">The new pressed state</param>
	inline void setPressed(bool pressed) { _pressed = pressed; }

	/// <summary>
	/// Returns the Sprite component attached to the same Entity as this Button component.
	/// </summary>
	/// <returns></returns>
	inline Sprite& getSprite() { return *_sprite; }

	/// <summary>
	/// Checks whether the mouse is hovering the button or not.
	/// </summary>
	/// <returns>True if the mouse is hovering, false if not.</returns>
	bool mouseHovering();

	/// <summary>
	/// Checks whether the button is currently being held down.
	/// </summary>
	/// <returns>True if it is, false if not.</returns>
	bool buttonDown();

	/// <summary>
	/// Checkes whether this button was released this frame.
	/// </summary>
	/// <returns>True if it was, false if not.</returns>
	bool buttonReleased();

private:
	std::string _defaultTextureID;
	std::string _hoverTextureID;
	std::string _downTextureID;

	bool _pressed = false;

	Sprite* _sprite = nullptr;
};
