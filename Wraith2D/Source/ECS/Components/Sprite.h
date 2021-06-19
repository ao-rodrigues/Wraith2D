#pragma once

#include <SDL.h>
#include <vector>
#include "Renderable.h"
#include "../../AssetManager.h"
#include "../../RenderLayer.h"


class Sprite : public Renderable
{
public:
	Sprite(RenderLayer renderLayer, int depth, const std::string& textureID, int srcX, int srcY, int width, int height, float relativePosX = 0.f, float relativePosY = 0.f)
		: Renderable(renderLayer, depth, relativePosX, relativePosY)
		, _textureID(textureID)
		, _srcX(srcX)
		, _srcY(srcY)
		, _srcWidth(width)
		, _srcHeight(height)
		, _dstWidth(width)
		, _dstHeight(height)
	{
	}

	Sprite(RenderLayer renderLayer, int depth, const std::string& textureID, int srcX, int srcY, int srcWidth, int srcHeight, int dstWidth, int dstHeight, float relativePosX, float relativePosY)
		: Renderable(renderLayer, depth, relativePosX, relativePosY)
		, _textureID(textureID)
		, _srcX(srcX)
		, _srcY(srcY)
		, _srcWidth(srcWidth)
		, _srcHeight(srcHeight)
		, _dstWidth(dstWidth)
		, _dstHeight(dstHeight)
	{ }

	~Sprite()
	{
		
	}

	void init() override;

	/// <summary>
	/// Returns the srcRect of this Sprite.
	/// </summary>
	/// <returns>The srcRect</returns>
	virtual SDL_Rect* srcRect() override
	{
		return &_srcRect;
	}

	/// <summary>
	/// Sets the source dimensions.
	/// </summary>
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	inline void setSrcDimensions(int w, int h)
	{
		_srcRect.w = w;
		_srcRect.h = h;
	}

	/// <summary>
	/// Returns the dstRect.
	/// </summary>
	/// <returns>The dstRect</returns>
	virtual SDL_Rect* dstRect() override
	{
		return &_dstRect;
	}

	/// <summary>
	/// Sets the texture for this Sprite.
	/// </summary>
	/// <param name="newTextureID">The new texture ID</param>
	inline void setTexture(const std::string& newTextureID)
	{
		_textureID = newTextureID;
		texture = AssetManager::instance().getTexture(_textureID);
	}

	/// <summary>
	/// Sets the texture for this Sprite and its row index.
	/// Useful for spritesheets that have multiple rows.
	/// </summary>
	/// <param name="newTextureID">The new texture ID</param>
	/// <param name="rowIndex">The index of the row inside the texture</param>
	inline void setTexture(const std::string& newTextureID, int rowIndex)
	{
		setTexture(newTextureID);
		_srcRect.y = rowIndex * _dstHeight;
	}

	/// <summary>
	/// Returns the texture ID of this Sprite.
	/// </summary>
	/// <returns>The texture ID</returns>
	inline const std::string& getTextureID() const { return _textureID; }

	/// <summary>
	/// Sets the visible state of this Sprite.
	/// </summary>
	/// <param name="visible">The visible state</param>
	inline void setVisible(bool visible)
	{
		this->visible = visible;
	}

	/// <summary>
	/// Returns the X coordinate of the source rectangle.
	/// </summary>
	/// <returns>X coord of the source rectangle</returns>
	inline int getSrcX() const { return _srcX; }

	/// <summary>
	/// Sets the X coord of the source rectangle.
	/// </summary>
	/// <param name="newSrcX">The new X coord</param>
	inline void setSrcX(int newSrcX) { _srcX = newSrcX; }

	/// <summary>
	/// Returns the Y coordinate of the source rectangle.
	/// </summary>
	/// <returns>Y coord of the source rectangle</returns>
	inline int getSrcY() const { return _srcY; }

	/// <summary>
	/// Sets the Y coord of the source rectangle.
	/// </summary>
	/// <param name="newSrcY">The new Y coord</param>
	inline void setSrcY(int newSrcY) { _srcY = newSrcY; }

	/// <summary>
	/// Returns the width of the source rectangle.
	/// </summary>
	/// <returns>The width of the source rectangle</returns>
	inline int getSrcWidth() const { return _srcWidth; }

	/// <summary>
	/// Sets the width of the source rectangle.
	/// </summary>
	/// <param name="newSrcWidth">The new width</param>
	inline void setSrcWidth(int newSrcWidth) { _srcWidth = newSrcWidth; }

	/// <summary>
	/// Returns the height of the source rectangle.
	/// </summary>
	/// <returns>The height of the source rectangle</returns>
	inline int getSrcHeight() const { return _srcHeight; }

	/// <summary>
	/// Sets the height of the source rectangle.
	/// </summary>
	/// <param name="newSrcHeight">The new height</param>
	inline void setSrcHeight(int newSrcHeight) { _srcHeight = newSrcHeight; }

	/// <summary>
	/// Returns the width of the destination rectangle.
	/// </summary>
	/// <returns>The width of the destination rectangle</returns>
	inline int getDstWidth() const { return _dstWidth; }

	/// <summary>
	/// Sets the width of the destination rectangle.
	/// </summary>
	/// <param name="newDstWidth">The new width</param>
	inline void setDstWidth(int newDstWidth) { _dstWidth = newDstWidth; }

	/// <summary>
	/// Returns the height of the destination rectangle.
	/// </summary>
	/// <returns>The height of the destination rectangle</returns>
	inline int getDstHeight() const { return _dstHeight; }

	/// <summary>
	/// Sets the height of the destination rectangle.
	/// </summary>
	/// <param name="newDstHeight">The new height</param>
	inline void setDstHeight(int newDstHeight) { _dstHeight = newDstHeight; }

private:
	int _srcX = 0;
	int _srcY = 0;

	int _srcWidth = 0;
	int _srcHeight = 0;

	int _dstWidth = 0;
	int _dstHeight = 0;

	std::string _textureID = "";
};