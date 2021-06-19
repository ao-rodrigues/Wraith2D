#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <iostream>

class Entity;
class EntityManager;

using EntityID = std::size_t;
using ArchetypeID = std::size_t;
using ComponentID = std::size_t;

class Component
{
public:
	virtual ~Component() {}

	/// <summary>
	/// Initializes the component. 
	/// This is usually the place where a component can get references to other components
	/// in the same Entity.
	/// </summary>
	virtual void init() {}

	Entity* entity = nullptr;
};

class System
{
public:
	System(EntityManager* entityManager)
		: _entityManager(entityManager)
	{ }

	virtual ~System() {}

	/// <summary>
	/// Called upon creation of the system
	/// </summary>
	virtual void init() {}

	/// <summary>
	/// Called every frame in each system
	/// </summary>
	virtual void update() = 0;

protected:
	EntityManager* _entityManager;
};

struct Archetype
{
	Archetype()
	{
		id = s_lastArchetypeID++;
		entities.reserve(10);
	}

	Archetype(std::unordered_set<ComponentID>&& newComponents);

	/// <summary>
	/// Checks whether this Archetype has the component of type supplied as type param.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns>True if it has, false if it doesn't</returns>
	template<typename T>
	inline bool hasComponent()
	{
		return components.count(getComponentID<T>()) > 0;
	}

	/// <summary>
	/// Calculates the Component ID for the component type supplied as type param.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns>Component ID</returns>
	template<typename T>
	static ComponentID getComponentID()
	{
		return typeid(T).hash_code();
	}

	ArchetypeID id;
	std::unordered_set<ComponentID> components;
	std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;

private:
	static ArchetypeID s_lastArchetypeID;
};

class Entity
{
public:
	EntityID id;
	ArchetypeID archetypeID = 0u;
	EntityManager* manager = nullptr;

	Entity(ArchetypeID archetypeID, EntityManager* manager);
	~Entity()
	{
		_componentMap.clear();
	}

	/// <summary>
	/// Checks whether this Entity is active (not marked for removal).
	/// </summary>
	/// <returns>True if active, false if not</returns>
	inline bool isActive() const { return _isActive; }

	/// <summary>
	/// Marks this Entity for removal (inactive).
	/// </summary>
	inline void destroy() { _isActive = false; }

	/// <summary>
	/// Checks whether this Entity is enabled.
	/// </summary>
	/// <returns>True if enabled, false if not</returns>
	inline bool isEnabled() const { return _isEnabled; }

	/// <summary>
	/// Changes the enabled state of this Entity.
	/// </summary>
	/// <param name="enabled">The new enabled state</param>
	inline void setEnabled(bool enabled) { _isEnabled = enabled; }

	/// <summary>
	/// Flags this Entity so that, if it is set inactive this frame, it will only be removed in the next.
	/// </summary>
	/// <param name="destroyNextFrame">The flag value</param>
	inline void setDestroyNextFrame(bool destroyNextFrame) { _destroyNextFrame = destroyNextFrame; }

	/// <summary>
	/// Checks if this Entity is flagged to be destroyed next frame.
	/// </summary>
	/// <returns>True if it is, false if not</returns>
	inline bool destroyNextFrame() { return _destroyNextFrame; }

	/// <summary>
	/// Checks if this Entity has the component supplied as type param.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns>True if it has, false if not</returns>
	template<typename T>
	inline bool hasComponent() const
	{
		return _componentMap.count(Archetype::getComponentID<T>());
	}

	/// <summary>
	/// Returns a reference to this Entity's component of the type supplied as type param.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns>A reference to the component, or nullptr if this Entity doesn't have it</returns>
	template<typename T>
	inline T& getComponent() const
	{
		Component* ptr = _componentMap.at(Archetype::getComponentID<T>()).get();
		return *static_cast<T*>(ptr);
	}

	/// <summary>
	/// Adds a new component of the type supplied as type param to this Entity.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...TArgs"></typeparam>
	/// <param name="...args">The constructor arguments for the component</param>
	/// <returns>A reference to the newly-added component</returns>
	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... args);

private:
	static EntityID s_lastEntityID;
	bool _isActive = true;
	bool _isEnabled = true;
	bool _destroyNextFrame = false;
	std::unordered_map<ComponentID, std::unique_ptr<Component>> _componentMap;
};

class EntityManager
{
public:
	EntityManager();
	~EntityManager()
	{
		_entityArchetypes.clear();
	}

	/// <summary>
	/// Deletes all inactive entities and empty archetypes.
	/// </summary>
	void refresh();

	/// <summary>
	/// Creates a new entity with a Transform component pre-applied.
	/// </summary>
	/// <returns>A new entity</returns>
	Entity& createEntity();

	/// <summary>
	/// Returns all entities that contain all of the supplied components.
	/// </summary>
	/// <typeparam name="...Ts">Component type</typeparam>
	/// <param name="includeInactive">If true, this query will include entities marked for removal.</param>
	/// <param name="includeDisabled">If true, this query will include disabled entities.</param>
	/// <returns>Vector with all entities with all of the supplied components</returns>
	template<typename... Ts>
	std::vector<Entity*> getEntitiesWithComponentAll(bool includeInactive = false, bool includeDisabled = false);

	/// <summary>
	/// Returns all entities that contain any of the supplied components.
	/// </summary>
	/// <typeparam name="...Ts">Component type</typeparam>
	/// <param name="includeInactive">If true, this query will include entities marked for removal.</param>
	/// <param name="includeDisabled">If true, this query will include disabled entities.</param>
	/// <returns>Vector with all entities with any of the supplied components</returns>
	template<typename... Ts>
	std::vector<Entity*> getEntitiesWithComponentAny(bool includeInactive = false, bool includeDisabled = false);

	/// <summary>
	/// Returns all entities that contain none of the supplied components.
	/// </summary>
	/// <typeparam name="...Ts">Component type</typeparam>
	/// <param name="includeInactive">If true, this query will include entities marked for removal.</param>
	/// <param name="includeDisabled">If true, this query will include disabled entities.</param>
	/// <returns>Vector with all entities with none of the supplied components</returns>
	template<typename... Ts>
	std::vector<Entity*> getEntitiesWithComponentNone(bool includeInactive = false, bool includeDisabled = false);

	/// <summary>
	/// Returns all entities that contain exactly all of the supplied components.
	/// </summary>
	/// <typeparam name="...Ts">Component type</typeparam>
	/// <param name="includeInactive">If true, this query will include entities marked for removal.</param>
	/// <param name="includeDisabled">If true, this query will include disabled entities.</param>
	/// <returns>Vector with all entities with exactly all of the supplied components</returns>
	template<typename... Ts>
	std::vector<Entity*> getEntitiesWithComponentExact(bool includeInactive = false, bool includeDisabled = false);

private:
	friend class Entity;
	std::vector<std::unique_ptr<Archetype>> _entityArchetypes;

	unsigned int _lastCleanupTime = 0;
	const unsigned int CLEANUP_INTERVAL = 60000;

	/// <summary>
	/// Updates the archetypes with the new component(s) of the supplied Entity.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="entity">The entity with the new component(s)</param>
	template<typename T>
	void updateArchetypes(Entity* entity);
};


/**
* /////////////////////////////////////////////////////////////////
* ************************** Entity *******************************
* /////////////////////////////////////////////////////////////////
*/

template<typename T, typename... TArgs>
T& Entity::addComponent(TArgs&&... args)
{
	std::unique_ptr<Component> compUniqPtr = std::make_unique<T>(std::forward<TArgs>(args)...);
	compUniqPtr->entity = this;
	compUniqPtr->init();

	T* newComponent = dynamic_cast<T*>(compUniqPtr.get());

	ComponentID componentID = Archetype::getComponentID<T>();
	_componentMap.emplace(componentID, std::move(compUniqPtr));

	manager->updateArchetypes<T>(this);

	return *newComponent;
}

/**
* /////////////////////////////////////////////////////////////////
* *********************** EntityManager ***************************
* /////////////////////////////////////////////////////////////////
*/


template<typename T>
void EntityManager::updateArchetypes(Entity* entity)
{
	ArchetypeID archetypeID = entity->archetypeID;
	std::unordered_set<ComponentID> entityComponents;
	std::unique_ptr<Entity> entityUPtr;

	for (auto& archetype : _entityArchetypes)
	{
		if (archetype->id == archetypeID)
		{
			// Grab the components this entity already has
			entityComponents = archetype->components;
			entityUPtr = std::move(archetype->entities.at(entity->id));
			// Remove entity from old archetype
			archetype->entities.erase(entityUPtr->id);
			break;
		}
	}

	// Add new component type
	entityComponents.emplace(Archetype::getComponentID<T>());

	// Check if new archetype already exists and add entity to it if true
	for (auto& archetype : _entityArchetypes)
	{
		bool containsAll = true;

		for (auto& component : entityComponents)
		{
			containsAll = containsAll && archetype->components.count(component);
		}

		if (containsAll && archetype->components.size() == entityComponents.size())
		{
			entityUPtr->archetypeID = archetype->id;
			archetype->entities.emplace(entityUPtr->id, std::move(entityUPtr));
			return;
		}
	}

	// Archetype doesn't exist yet, create a new one
	std::unique_ptr<Archetype> archetypeUPtr = std::make_unique<Archetype>(std::move(entityComponents));

	entityUPtr->archetypeID = archetypeUPtr->id;
	archetypeUPtr->entities.emplace(entityUPtr->id, std::move(entityUPtr));

	_entityArchetypes.emplace_back(std::move(archetypeUPtr));
}

template<typename... Ts>
std::vector<Entity*> EntityManager::getEntitiesWithComponentAll(bool includeInactive, bool includeDisabled)
{
	std::vector<ComponentID> components;
	components.insert(components.end(), { Archetype::getComponentID<Ts>()... });

	std::vector<Entity*> entities;

	for (auto& archetype : _entityArchetypes)
	{
		bool containsAll = true;

		// Check if this archetype has ALL of the supplied components
		for (auto& component : components)
		{
			containsAll = containsAll && archetype->components.count(component);
		}

		if (containsAll)
		{
			for (auto& entity : archetype->entities)
			{
				if (!entity.second->isActive() && !includeInactive || !entity.second->isEnabled() && !includeDisabled) continue;

				entities.emplace_back(entity.second.get());
			}
		}
	}

	return entities;
}

template<typename... Ts>
std::vector<Entity*> EntityManager::getEntitiesWithComponentAny(bool includeInactive, bool includeDisabled)
{
	std::vector<ComponentID> components;
	components.insert(components.end(), { Archetype::getComponentID<Ts>()... });

	std::vector<Entity*> entities;

	for (auto& archetype : _entityArchetypes)
	{
		bool containsAny = false;

		// Check if this archetype has ANY of the supplied components
		for (auto& component : components)
		{
			containsAny = containsAny || archetype->components.count(component);
		}

		if (containsAny)
		{
			for (auto& entity : archetype->entities)
			{
				if (!entity.second->isActive() && !includeInactive || !entity.second->isEnabled() && !includeDisabled) continue;

				entities.emplace_back(entity.second.get());
			}
		}
	}

	return entities;
}

template<typename... Ts>
std::vector<Entity*> EntityManager::getEntitiesWithComponentNone(bool includeInactive, bool includeDisabled)
{
	std::vector<ComponentID> components;
	components.insert(components.end(), { Archetype::getComponentID<Ts>()... });

	std::vector<Entity*> entities;

	for (auto& archetype : _entityArchetypes)
	{
		bool containsNone = true;

		// Check if this archetype has ANY of the supplied components
		for (auto& component : components)
		{
			containsNone = containsNone && !archetype->components.count(component);
		}

		if (containsNone)
		{
			for (auto& entity : archetype->entities)
			{
				if (!entity.second->isActive() && !includeInactive || !entity.second->isEnabled() && !includeDisabled) continue;

				entities.emplace_back(entity.second.get());
			}
		}
	}

	return entities;
}

template<typename... Ts>
std::vector<Entity*> EntityManager::getEntitiesWithComponentExact(bool includeInactive, bool includeDisabled)
{
	std::vector<ComponentID> components;
	components.insert(components.end(), { Archetype::getComponentID<Ts>()... });

	std::vector<Entity*> entities;

	for (auto& archetype : _entityArchetypes)
	{
		bool containsAll = true;

		// First check if this archetype contains all of the supplied components
		for (auto& component : components)
		{
			containsAll = containsAll && archetype->components.count(component);
		}

		// Now check if it also contains the EXACT number of components
		if (containsAll && archetype->components.size() == components.size())
		{
			for (auto& entity : archetype->entities)
			{
				if (!entity.second->isActive() && !includeInactive || !entity.second->isEnabled() && !includeDisabled) continue;

				entities.emplace_back(entity.second.get());
			}

			return entities;
		}
	}

	return entities;
}