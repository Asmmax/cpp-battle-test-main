#pragma once

#include <functional>
#include <vector>

namespace sw::core
{
	class EventBus
	{
	private:
		template <typename TEvent>
		using Handler = std::function<void(TEvent)>;

		template <typename TEvent>
		static std::vector<Handler<TEvent>>& getHandlers()
		{
			static std::vector<Handler<TEvent>> handlers;
			return handlers;
		}

	public:
		template <typename TEvent>
		static void subscribe(Handler<TEvent> handler)
		{
			getHandlers<TEvent>().push_back(std::move(handler));
		}

		template <typename TEvent>
		static void publish(TEvent&& eventData)
		{
			for (auto& handler : getHandlers<TEvent>())
			{
				handler(eventData);
			}
		}
	};
}
