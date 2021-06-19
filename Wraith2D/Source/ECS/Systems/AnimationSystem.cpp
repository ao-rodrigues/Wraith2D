#include "AnimationSystem.h"

#include "../Components/Animation.h"

void AnimationSystem::update()
{
	for (auto& animEntity : _entityManager->getEntitiesWithComponentAll<Animation>())
	{
		Animation& animation = animEntity->getComponent<Animation>();
		Animation::AnimationInfo animInfo = animation.getCurrentAnimation();

		if (!animInfo.loop && (animation.getCurrentFrame() == animInfo.numFrames - 1)) continue;

		int nextFrame = static_cast<int>((SDL_GetTicks() / animInfo.frameDelay) % animInfo.numFrames);
		animation.getSprite().srcRect()->x = animation.getSprite().srcRect()->w * nextFrame;
		animation.setCurrentFrame(nextFrame);

		if (animInfo.loop && animation.getCurrentFrame() == animInfo.numFrames - 1)
		{
			animation.reset();
		}
	}
}