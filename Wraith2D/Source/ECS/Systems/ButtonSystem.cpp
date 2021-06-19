#include "ButtonSystem.h"
#include "../Components/Button.h"

void ButtonSystem::update()
{
	for (auto& buttonEntity : _entityManager->getEntitiesWithComponentAll<Button>(false, true))
	{
		Button& button = buttonEntity->getComponent<Button>();

		if (!buttonEntity->isEnabled())
		{
			// Reset disabled buttons
			button.setPressed(false);
			continue;
		}

		if (button.getDefaultTextureID() != "")
		{
			button.getSprite().setTexture(button.getDefaultTextureID());
		}

		if (button.mouseHovering() && button.getHoverTextureID() != "")
		{
			button.getSprite().setTexture(button.getHoverTextureID());
		}

		if (button.buttonDown() && button.getDownTextureID() != "")
		{
			button.getSprite().setTexture(button.getDownTextureID());
			button.setPressed(true);
		}

		if (button.buttonReleased())
		{
			button.setPressed(false);
		}
	}
}