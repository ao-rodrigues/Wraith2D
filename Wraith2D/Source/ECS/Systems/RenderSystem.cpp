#include "RenderSystem.h"

#include <iostream>
#include "../Components/Sprite.h"
#include "../Components/Text.h"

#include "../../InputManager.h"


void RenderSystem::init()
{
	_sortedRenderables.reserve(RenderLayer::Count);
	for (std::size_t i = 0; i < RenderLayer::Count; i++)
	{
		_sortedRenderables.emplace_back(std::multiset<Renderable*, RenderableComparator>());
	}
}

void RenderSystem::init(SDL_Window* window, int flags)
{
	_renderer = SDL_CreateRenderer(window, -1, flags);

	if (!_renderer)
	{
		std::cerr << SDL_GetError() << std::endl;
	}

	AssetManager::instance().loadTexture("Cursor", "Assets/Textures/pointer.png");

	SDL_ShowCursor(0);
	_cursorTexture = AssetManager::instance().getTexture("Cursor");
}

void RenderSystem::update()
{
	auto renderableEntities = _entityManager->getEntitiesWithComponentAny<Sprite, Text>();
	for (auto& entity : renderableEntities)
	{
		if (entity->hasComponent<Sprite>())
		{
			Sprite& sprite = entity->getComponent<Sprite>();
			_sortedRenderables[sprite.getRenderLayer()].emplace(&sprite);
		}
		
		if (entity->hasComponent<Text>())
		{
			Text& text = entity->getComponent<Text>();
			_sortedRenderables[text.getRenderLayer()].emplace(&text);
		}
	}

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);

	for (auto& layer : _sortedRenderables)
	{
		for (auto& renderable : layer)
		{
			if (renderable->isVisible())
			{
				SDL_RenderCopyEx(_renderer, renderable->getTexture(), renderable->srcRect(), renderable->dstRect(), renderable->getTransform().rotation, nullptr, renderable->getFlip());
			}
		}

		layer.clear();
	}

	Vector2 mousePos = InputManager::mousePosition();
	SDL_Rect cursorDstRect = { mousePos.x, mousePos.y, _cursorSrcRect.w, _cursorSrcRect.h };
	SDL_RenderCopy(_renderer, _cursorTexture, &_cursorSrcRect, &cursorDstRect);

	SDL_RenderPresent(_renderer);
}

void RenderSystem::destroy()
{
	_sortedRenderables.clear();
	SDL_DestroyRenderer(_renderer);
}