#include "Renderable.h"
#include "../../Engine.h"

void Renderable::makeDstRelativeToCamera()
{
	// Make final destination relative to camera
	SDL_Rect camera = Engine::instance().getCamera();
	_dstRect.x -= camera.x;
	_dstRect.y -= camera.y;
}