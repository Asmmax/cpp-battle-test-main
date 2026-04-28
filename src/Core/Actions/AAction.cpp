#include "AAction.hpp"

#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"

namespace sw::core
{
	AAction::AAction(std::string id, std::shared_ptr<IAction> next) :
			_id(std::move(id)),
			_next(std::move(next))
	{}

	void AAction::operator()(Unit& self, World& world)
	{
		prepare(self, world);

		if (canAct(self, world))
		{
			act(self, world);
			return;
		}
		if (_next)
		{
			(*_next)(self, world);
		}
	}

	bool AAction::isValid(Unit& self, World& world) const
	{
		if (canAct(self, world))
		{
			return true;
		}
		if (!_next)
		{
			return false;
		}
		return _next->isValid(self, world);
	}
}
