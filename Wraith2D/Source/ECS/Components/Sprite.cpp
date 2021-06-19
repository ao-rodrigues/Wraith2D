#include "Sprite.h"
#include "../../Engine.h"

void Sprite::init()
{
	transform = &entity->getComponent<Transform>();
	texture = AssetManager::instance().getTexture(_textureID);

	_srcRect.x = _srcX;
	_srcRect.y = _srcY;
	_srcRect.w = _srcWidth;
	_srcRect.h = _srcHeight;

	_dstRect.x = static_cast<int>(transform->position.x + _relativePosX);
	_dstRect.y = static_cast<int>(transform->position.y + _relativePosY);
	_dstRect.w = static_cast<int>(_dstWidth * transform->scale.x);
	_dstRect.h = static_cast<int>(_dstHeight * transform->scale.y);

	makeDstRelativeToCamera();
}