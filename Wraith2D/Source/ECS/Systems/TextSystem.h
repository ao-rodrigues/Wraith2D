#pragma once

#include "../ECS.h"

class TextSystem : public System
{
public:
	using System::System;

	virtual void update() override;
};
