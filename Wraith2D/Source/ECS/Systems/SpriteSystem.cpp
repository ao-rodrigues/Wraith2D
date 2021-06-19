#include "SpriteSystem.h"
#include <stdlib.h>

#include "../Components/Sprite.h"

void SpriteSystem::update()
{
	auto spriteEntities = _entityManager->getEntitiesWithComponentAll<Sprite>();
	for (auto& spriteEntity : spriteEntities)
	{
		Sprite& sprite = spriteEntity->getComponent<Sprite>();

		sprite.srcRect()->w = sprite.getSrcWidth();
		sprite.srcRect()->h = sprite.getSrcHeight();
		sprite.dstRect()->x = static_cast<int>(std::round(sprite.getTransform().position.x + sprite.getRelativePosition().x * sprite.getTransform().scale.x));
		sprite.dstRect()->y = static_cast<int>(std::round(sprite.getTransform().position.y + sprite.getRelativePosition().y * sprite.getTransform().scale.y));
		sprite.dstRect()->w = static_cast<int>(std::round(sprite.getDstWidth() * sprite.getTransform().scale.x));
		sprite.dstRect()->h = static_cast<int>(std::round(sprite.getDstHeight() * sprite.getTransform().scale.y));

		sprite.makeDstRelativeToCamera();
	}
}