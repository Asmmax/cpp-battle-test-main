#pragma once

#include <assert.h>
#include <memory>

namespace sw::core
{
	class ServiceLocator
	{
	public:
		template <typename TService>
		static void set(std::unique_ptr<TService> service)
		{
			getStorage<TService>() = std::move(service);
		}

		template <typename TService>
		static TService& get()
		{
			TService* ptr = getStorage<TService>().get();
			assert(ptr && "Service was not registered");
			return *ptr;
		}

	private:
		template <typename TService>
		static std::unique_ptr<TService>& getStorage()
		{
			static std::unique_ptr<TService> storage{};
			return storage;
		}
	};
}
