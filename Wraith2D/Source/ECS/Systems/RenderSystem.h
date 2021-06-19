#pragma once

#include <SDL.h>
#include <vector>
#include <set>

#include "../ECS.h"
#include "../Components/Renderable.h"

class RenderSystem : public System
{
public:
	using System::System;

	void init() override;
	void init(SDL_Window* window, int flags);

	virtual void update() override;

	inline SDL_Renderer* SDLRenderer() { return _renderer; }

	void destroy();

private:
	struct RenderableComparator
	{
		bool operator()(const Renderable* r1, const Renderable* r2) const
		{
			return r1->getDepth() < r2->getDepth();
		}
	};
	

	std::vector<std::multiset<Renderable*, RenderableComparator>> _sortedRenderables;

	SDL_Texture* _cursorTexture;
	SDL_Rect _cursorSrcRect = { 0, 0, 21, 20 };

	SDL_Renderer* _renderer;
};