#pragma once

#include <vector>
#include <memory>

#include "ECS/ECS.h"
#include "Singleton.h"
#include "ECS/Systems/RenderSystem.h"
#include "Math/Vector2.h"
#include "ECS/Systems/SpriteSystem.h"
#include "ECS/Systems/AnimationSystem.h"
#include "ECS/Systems/ButtonSystem.h"
#include "ECS/Systems/TextSystem.h"

class Engine : public Singleton<Engine>
{
public:

	Engine();
	~Engine();

	/// <summary>
	/// Initializes the engine.
	/// </summary>
	/// <param name="title">The window title</param>
	/// <param name="width">The width of the window</param>
	/// <param name="height">The height of the window</param>
	/// <param name="fullscreen">Flag to set the window fullscreen or not</param>
	/// <param name="vsync">Flag to enable vsync or not</param>
	/// <param name="worldWidth">The width of the game world</param>
	/// <param name="worldHeight">The height of the game world</param>
	void init(const char* title, int width, int height, bool fullscreen, bool vsync, int worldWidth, int worldHeight);

	/// <summary>
	/// Stops the engine.
	/// </summary>
	void quit();

	/// <summary>
	/// Clears the engine
	/// </summary>
	void clear();

	/// <summary>
	/// Handles window and input events
	/// </summary>
	void handleEvents();

	/// <summary>
	/// Updates the engine every frame
	/// </summary>
	void update();

	/// <summary>
	/// Calls the update call to the Render System
	/// </summary>
	void render();

	/// <summary>
	/// Creates an entity with a Transform component pre-applied
	/// </summary>
	/// <returns>A new entity</returns>
	Entity& createEntity();

	/// <summary>
	/// Creates an empty entity with no components pre-applied
	/// </summary>
	/// <returns>A new empty entity</returns>
	Entity& createEmptyEntity();

	/// <summary>
	/// Creates a new System.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns>A reference to the newly-created system</returns>
	template<typename T>
	T& createSystem()
	{
		static_assert(std::is_base_of<System, T>::value, "Type must be derived from System!");
		//T* system = new T(_entityManager);
		//system->init();
		std::unique_ptr<T> systemUniqPtr = std::make_unique<T>(_entityManager);
		systemUniqPtr->init();

		T* system = systemUniqPtr.get();

		_systems.emplace_back(std::move(systemUniqPtr));

		return *system;
	}

	/// <summary>
	/// Checks whether the engine is running.
	/// </summary>
	/// <returns>True if it is running, false if not</returns>
	inline bool isRunning() { return _isRunning; }

	/// <summary>
	/// Returns a pointer to the SDL Renderer.
	/// </summary>
	/// <returns>Pointer to the SDL Renderer</returns>
	inline SDL_Renderer* getRenderer() { return _renderSystem->SDLRenderer(); }

	/// <summary>
	/// Returns an SDL_Rect that defines the game camera.
	/// </summary>
	/// <returns>The game camera</returns>
	inline SDL_Rect getCamera() { return _camera; }

	/// <summary>
	/// Returns the dimensions of the game world.
	/// </summary>
	/// <returns>A Vector2 with the dimensions as (width,height)</returns>
	inline Vector2 getWorldDimensions() { return _worldDimensions; }

	/// <summary>
	/// Returns the time difference between this frame and the last.
	/// </summary>
	/// <returns>The time difference between this frame and the last</returns>
	inline float deltaTime() { return _deltaTime; }

	/// <summary>
	/// Returns the frames per second
	/// </summary>
	/// <returns>Frames per second</returns>
	inline unsigned int FPS() { return _fps; }

private:
	bool _isRunning = false;

	unsigned int _lastFrameTime = 0u;
	unsigned int _lastFPSCountTime = 0u;
	float _deltaTime = 1.f;

	unsigned int _fps = 0;

	SDL_Window* _window = nullptr;
	SDL_Rect _camera = { 0, 0, 0, 0 };
	Vector2 _worldDimensions;
	RenderSystem* _renderSystem = nullptr;
	EntityManager* _entityManager = nullptr;

	SpriteSystem* _spriteSystem = nullptr;
	TextSystem* _textSystem = nullptr;
	AnimationSystem* _animationSystem = nullptr;
	ButtonSystem* _buttonSystem = nullptr;

	std::vector<std::unique_ptr<System>> _systems;
};