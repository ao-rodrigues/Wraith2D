#include "Animation.h"
#include "../../Engine.h"

void Animation::init()
{
	_sprite = &entity->getComponent<Sprite>();
	AnimationInfo animInfo = _animations.at(_currentAnimation);
	_sprite->setTexture(animInfo.textureID, animInfo.rowIndex);
}