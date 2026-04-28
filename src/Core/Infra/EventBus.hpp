#pragma once

#include <vector>
#include <functional>

namespace sw::core
{
	class EventBus
	{
	private:
		template <typename EventType>
		using Handler = std::function<void(EventType)>;

		template <typename EventType>
		static std::vector<Handler<EventType>>& getHandlers()
		{
			static std::vector<Handler<EventType>> handlers;
			return handlers;
		}

	public:
		template <typename EventType>
		static void subscribe(Handler<EventType> handler)
		{
			getHandlers<EventType>().push_back(std::move(handler));
		}

		template <typename EventType>
		static void publish(EventType&& eventData)
		{
			for (auto& handler : getHandlers<EventType>())
			{
				handler(eventData);
			}
		}
	};
}
