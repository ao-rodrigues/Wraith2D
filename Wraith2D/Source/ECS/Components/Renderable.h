#pragma once

#include <SDL.h>
#include "../ECS.h"
#include "Transform.h"
#include "../../RenderLayer.h"

class Renderable : public Component
{
public:
	Renderable(RenderLayer renderLayer, int depth, float relativePosX = 0.f, float relativePosY = 0.f)
		: renderLayer(renderLayer)
		, depth(depth)
		, _relativePosX(relativePosX)
		, _relativePosY(relativePosY)
	{}

	~Renderable()
	{

	}

	virtual void init() override 
	{
		transform = &entity->getComponent <Transform>();
	}

	virtual SDL_Rect* srcRect() = 0;
	virtual SDL_Rect* dstRect() = 0;

	/// <summary>
	/// Get the position offset relative to the Transform.
	/// </summary>
	/// <returns>Position offset relative to Transform</returns>
	inline Vector2 getRelativePosition() { return Vector2(_relativePosX, _relativePosY); }

	/// <summary>
	/// Set the position offset relative to the Transform.
	/// </summary>
	/// <param name="relativePosition">New position offset</param>
	inline void setRelativePosition(Vector2 relativePosition)
	{
		_relativePosX = relativePosition.x;
		_relativePosY = relativePosition.y;
	}

	/// <summary>
	/// Converts the dst coordinates to make them relative to the game camera.
	/// </summary>
	void makeDstRelativeToCamera();
	
	/// <summary>
	/// Returns the texture of this Renderable.
	/// </summary>
	/// <returns>A pointer to the texture</returns>
	inline SDL_Texture* getTexture() { return texture; }

	/// <summary>
	/// Returns the Render Layer of this Renderable.
	/// </summary>
	/// <returns>The Render Layer</returns>
	inline RenderLayer getRenderLayer() const { return renderLayer; }

	/// <summary>
	/// Returns the Flip of this Renderable.
	/// </summary>
	/// <returns>The Flip</returns>
	inline SDL_RendererFlip getFlip() { return flip; }

	/// <summary>
	/// Returns the depth of this Renderable.
	/// </summary>
	/// <returns>The depth of this Renderable</returns>
	inline int getDepth() const { return depth; }

	/// <summary>
	/// Checks whether this Renderable is visible or not.
	/// </summary>
	/// <returns>True if it is, false if not</returns>
	inline bool isVisible() const { return visible; }

	/// <summary>
	/// Returns the Transform component attached to the same Entity as this Renderable component.
	/// </summary>
	/// <returns></returns>
	inline Transform& getTransform() { return *transform; }

protected:
	SDL_Rect _srcRect = { 0, 0, 0, 0 };
	SDL_Rect _dstRect = { 0, 0, 0, 0 };

	float _relativePosX = 0.f;
	float _relativePosY = 0.f;

	SDL_Texture* texture = nullptr;
	RenderLayer renderLayer = RenderLayer::Background;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int depth = 0;
	bool visible = true;
	Transform* transform = nullptr;
};