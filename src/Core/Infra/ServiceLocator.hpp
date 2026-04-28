#pragma once

#include <assert.h>
#include <memory>

namespace sw::core
{
	class ServiceLocator
	{
	public:
		template <typename ServiceType>
		static void set(std::unique_ptr<ServiceType> service)
		{
			getStorage<ServiceType>() = std::move(service);
		}

		template <typename ServiceType>
		static ServiceType& get()
		{
			ServiceType* ptr = getStorage<ServiceType>().get();
			assert(ptr && "Service was not registered");
			return *ptr;
		}

	private:
		template <typename ServiceType>
		static std::unique_ptr<ServiceType>& getStorage()
		{
			static std::unique_ptr<ServiceType> storage = nullptr;
			return storage;
		}
	};
}
