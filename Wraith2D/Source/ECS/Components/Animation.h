#pragma once

#include <SDL.h>
#include "../ECS.h"
#include "Sprite.h"

class Animation : public Component
{
public:
	struct AnimationInfo
	{
		AnimationInfo(const std::string& name, const std::string& textureID, unsigned int numFrames, unsigned int frameDelay, bool loop, unsigned int rowIndex)
			: name(name)
			, textureID(textureID)
			, numFrames(numFrames)
			, frameDelay(frameDelay)
			, loop(loop)
			, rowIndex(rowIndex)
		{ }

		std::string name;
		std::string textureID;
		unsigned int numFrames = 1;
		unsigned int frameDelay = 0;
		bool loop = true;
		unsigned int rowIndex = 0;
	};

	Animation(const std::string& textureID, unsigned int numFrames, unsigned int frameDelay, bool loop = true, unsigned int rowIndex = 0)
	{
		AnimationInfo animation(_currentAnimation, textureID, numFrames, frameDelay, loop, rowIndex);
		_animations.emplace(_currentAnimation, animation);
	}

	Animation(const std::vector<AnimationInfo>& animations)
	{
		for (auto& anim : animations)
		{
			_animations.emplace(anim.name, anim);
		}

		_currentAnimation = animations[0].name;
	}

	~Animation()
	{

	}

	void init() override;

	/// <summary>
	/// Adds a new animation.
	/// </summary>
	/// <param name="animation">The new animation</param>
	void addAnimation(AnimationInfo animation)
	{
		_animations.emplace(animation.name, animation);
	}

	/// <summary>
	/// Changes the current active animation.
	/// </summary>
	/// <param name="animation">The new animation ID</param>
	void setAnimation(const std::string& animation)
	{
		if (_animations.count(animation))
		{
			_currentAnimation = animation;
			AnimationInfo animInfo = _animations.at(_currentAnimation);
			_sprite->setTexture(animInfo.textureID, animInfo.rowIndex);
			reset();
		}
	}

	/// <summary>
	/// Returns the current animation.
	/// </summary>
	/// <returns>A struct with the animation info</returns>
	inline AnimationInfo getCurrentAnimation()
	{
		return _animations.at(_currentAnimation);
	}

	/// <summary>
	/// Sets the current frame to the first frame.
	/// </summary>
	void reset()
	{
		_currentFrame = 0;
	}

	/// <summary>
	/// Returns all the animations.
	/// </summary>
	/// <returns>A vector with all the animations</returns>
	inline const std::unordered_map<std::string, AnimationInfo>& getAnimations() { return _animations; }

	/// <summary>
	/// Returns the index of the current frame.
	/// </summary>
	/// <returns>Index of the current frame</returns>
	inline unsigned int getCurrentFrame() { return _currentFrame; }

	/// <summary>
	/// Sets the frame index of the current animation
	/// </summary>
	/// <param name="nextFrame">The new index</param>
	inline void setCurrentFrame(unsigned int nextFrame) { _currentFrame = nextFrame; }

	/// <summary>
	/// Returns the Sprite component attached to the same Entity as this Animation component.
	/// </summary>
	/// <returns>A reference to the Sprite component</returns>
	inline Sprite& getSprite() { return *_sprite; }

private:
	std::unordered_map<std::string, AnimationInfo> _animations;
	std::string _currentAnimation = "Default";
	unsigned int _currentFrame = 0;
	Sprite* _sprite = nullptr;
};

