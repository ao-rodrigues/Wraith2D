#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "Renderable.h"
#include "../../Engine.h"
#include "../../AssetManager.h"


class Text : public Renderable
{
public:
	Text(const std::string& fontID, int depth, const std::string& text, SDL_Color color, unsigned int wrapLength, float relativePosX = 0.f, float relativePosY = 0.f)
		: Renderable(RenderLayer::UI, depth, relativePosX, relativePosY)
		, _fontID(fontID)
		, _text(text)
		, _textColor(color)
		, _wrapLength(wrapLength)
	{
		setText(this->_fontID, this->_text);
	}

	void init() override
	{
		transform = &entity->getComponent<Transform>();
		_dstRect.x = static_cast<int>(transform->position.x + _relativePosX);
		_dstRect.y = static_cast<int>(transform->position.y + _relativePosY);
		makeDstRelativeToCamera();
	}

	~Text()
	{ 
		if (texture != nullptr)
		{
			SDL_DestroyTexture(texture);
		}
	}

	/// <summary>
	/// Sets the text.
	/// </summary>
	/// <param name="fontID">The new font ID</param>
	/// <param name="text">The new text</param>
	void setText(std::string fontID, std::string text)
	{
		this->_fontID = fontID;
		this->_text = text;

		if (texture != nullptr)
		{
			SDL_DestroyTexture(texture);
		}

		SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(AssetManager::instance().getFont(fontID), text.c_str(), _textColor, _wrapLength);
		texture = SDL_CreateTextureFromSurface(Engine::instance().getRenderer(), surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(texture, nullptr, nullptr, &_dstRect.w, &_dstRect.h);
	}

	/// <summary>
	/// Sets the text color.
	/// </summary>
	/// <param name="newColor">The new text color</param>
	void setTextColor(SDL_Color newColor)
	{
		if (texture != nullptr)
		{
			SDL_DestroyTexture(texture);
		}

		SDL_Surface* surf = TTF_RenderText_Blended(AssetManager::instance().getFont(_fontID), _text.c_str(), newColor);
		texture = SDL_CreateTextureFromSurface(Engine::instance().getRenderer(), surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(texture, nullptr, nullptr, &_dstRect.w, &_dstRect.h);
	}

	/// <summary>
	/// Returns the source rectangle.
	/// </summary>
	/// <returns>The source rectangle</returns>
	virtual SDL_Rect* srcRect() override
	{
		return nullptr;
	}

	/// <summary>
	/// Returns the destination rectangle.
	/// </summary>
	/// <returns>The destination rectangle</returns>
	virtual SDL_Rect* dstRect() override
	{
		return &_dstRect;
	}

	/// <summary>
	/// Returns the font ID.
	/// </summary>
	/// <returns>The font ID</returns>
	inline const std::string& getFontID() const { return _fontID; }

	/// <summary>
	/// Returns the text.
	/// </summary>
	/// <returns>The text</returns>
	inline const std::string& getText() const { return _text; }

	/// <summary>
	/// Returns the text color.
	/// </summary>
	/// <returns>The text color</returns>
	inline const SDL_Color& getTextColor() const { return _textColor; }

	/// <summary>
	/// Returns the wrap length in pixels.
	/// </summary>
	/// <returns>The wrap length</returns>
	inline int getWrapLength() const { return _wrapLength; }

private:
	std::string _fontID;
	std::string _text;
	SDL_Color _textColor;
	unsigned int _wrapLength;
};