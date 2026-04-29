#pragma once

namespace sw::core
{
	template <typename TDerived>
	class Singleton
	{
	protected:
		Singleton() = default;
		~Singleton() = default;

	public:
		Singleton(const Singleton& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;

		Singleton(Singleton&& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;

		static TDerived& getInstance()
		{
			static TDerived instance;
			return instance;
		}
	};
}
