#pragma once

#include "../ECS.h"

class ButtonSystem : public System
{
public:
	using System::System;

	virtual void update() override;
};
