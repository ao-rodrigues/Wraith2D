#pragma once

template<typename T>
class Singleton
{
public:

	/// <summary>
	/// Returns the Singleton instance.
	/// </summary>
	/// <returns>A pointer to the Singleton instance</returns>
	static T& instance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new T();
		}

		return *s_instance;
	}

	/// <summary>
	/// Deletes the Singleton instance
	/// </summary>
	static void deleteInstance()
	{
		delete s_instance;
		s_instance = nullptr;
	}

private:
	static T* s_instance;
};

template<typename T>
T* Singleton<T>::s_instance = nullptr;