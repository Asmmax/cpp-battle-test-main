#pragma once

#include "IAction.hpp"

#include <string>
#include <memory>

namespace sw::core
{
	class AAction : public IAction
	{
	private:
		std::string _id;
		std::shared_ptr<IAction> _next;

	public:
		AAction(std::string id, std::shared_ptr<IAction> next);

		virtual void operator()(Unit& self, World& world) override;

		virtual bool isValid(Unit& self, World& world) const override;

	protected:
		virtual void prepare(Unit& self, World& world) = 0;
		virtual bool canAct(Unit& self, World& world) const = 0;
		virtual void act(Unit& self, World& world) = 0;
	};
}
