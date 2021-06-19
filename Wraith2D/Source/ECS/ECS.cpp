#include "ECS.h"

#include <SDL.h>

/**
* /////////////////////////////////////////////////////////////////
* ************************ Archetype ******************************
* /////////////////////////////////////////////////////////////////
*/

ArchetypeID Archetype::s_lastArchetypeID = 0u;

Archetype::Archetype(std::unordered_set<ComponentID>&& newComponents)
	: components(newComponents)
{
	//entities.reserve(100);
	std::cout << "New archetype!!!" << std::endl;
	id = s_lastArchetypeID++;
	//components = newComponents;
}


/**
* /////////////////////////////////////////////////////////////////
* ************************** Entity *******************************
* /////////////////////////////////////////////////////////////////
*/

EntityID Entity::s_lastEntityID = 0u;

Entity::Entity(ArchetypeID archetypeID, EntityManager* manager)
	: archetypeID(archetypeID)
	, manager(manager)
{
	id = s_lastEntityID++;
	//_componentMap.reserve(50);
}


/**
* /////////////////////////////////////////////////////////////////
* *********************** EntityManager ***************************
* /////////////////////////////////////////////////////////////////
*/

EntityManager::EntityManager()
{
	_entityArchetypes.reserve(50);

	Archetype* emptyArchetype = new Archetype();
	std::unique_ptr<Archetype> uPtr(emptyArchetype);

	// Create an "empty" archetype that stores all entities with no components
	_entityArchetypes.emplace_back(std::move(uPtr));
}

void EntityManager::refresh()
{
	for (auto& arch : _entityArchetypes)
	{	
		for (auto it = arch->entities.begin(); it != arch->entities.end();)
		{
			if (!it->second->isActive() && !it->second->destroyNextFrame())
			{
				it = arch->entities.erase(it);
			}
			else
			{
				if (!it->second->isActive() && it->second->destroyNextFrame())
				{
					it->second->setDestroyNextFrame(false);
				}

				++it;
			}
		}
	}

	if (SDL_GetTicks() - _lastCleanupTime >= CLEANUP_INTERVAL)
	{
		_entityArchetypes.erase(std::remove_if(_entityArchetypes.begin() + 1, _entityArchetypes.end(),
			[](const std::unique_ptr<Archetype>& archetype)
			{
				return archetype->entities.size() == 0;
			}
		), _entityArchetypes.end());

		_lastCleanupTime = SDL_GetTicks();
	}

}

Entity& EntityManager::createEntity()
{
	//Entity* newEntity = new Entity(_entityArchetypes[0]->id, this);
	//newEntity->manager = this;
	std::unique_ptr<Entity> entityUniqPtr = std::make_unique<Entity>(_entityArchetypes[0]->id, this);
	Entity* newEntity = entityUniqPtr.get();

	// Store in no-components archetype
	_entityArchetypes[0]->entities.emplace(entityUniqPtr->id, std::move(entityUniqPtr));

	return *newEntity;
}