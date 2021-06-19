#pragma once

#include "../ECS.h"
#include "../../Math/Vector2.h"

class Transform : public Component
{
public:
	Transform() 
	{
		scale.x = 1.f;
		scale.y = 1.f;
	}

	Transform(float xPos, float yPos)
	{
		position.x = xPos;
		position.y = yPos;
		scale.x = 1.f;
		scale.y = 1.f;
	}

	Transform(float xPos, float yPos, float xScale, float yScale)
	{
		position.x = xPos;
		position.y = yPos;
		scale.x = xScale;
		scale.y = yScale;
	}

	~Transform()
	{

	}

	/// <summary>
	/// The position in world coordinates
	/// </summary>
	Vector2 position;

	/// <summary>
	/// The scale in world coordinates
	/// </summary>
	Vector2 scale = { 1, 1 };

	/// <summary>
	/// The rotation
	/// </summary>
	float rotation = 0.f;
};