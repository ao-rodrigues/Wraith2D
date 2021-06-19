#pragma once

#include "../ECS.h"

class SpriteSystem : public System
{
public:
	using System::System;

	virtual void update() override;
};