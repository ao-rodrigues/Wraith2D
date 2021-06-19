#pragma once

#include "../ECS.h"

class AnimationSystem : public System
{
public:
	using System::System;

	virtual void update() override;
};