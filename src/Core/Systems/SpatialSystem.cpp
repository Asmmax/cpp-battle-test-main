#include "SpatialSystem.hpp"

#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"

namespace sw::core
{
	std::vector<uint32_t> SpatialSystem::findUnitsInRange(
		World& world, const Position& origin, uint32_t minDist, uint32_t maxDist, bool withFlying)
	{
		std::vector<uint32_t> result;

		Bound* map = world.getMap();
		if (!map || minDist > maxDist)
		{
			return result;
		}

		const uint32_t size = maxDist * 2 + 1;
		result.reserve(size * size);

		const int halfRange = static_cast<int>(maxDist);
		for (int dx = -halfRange; dx <= halfRange; dx++)
		{
			for (int dy = -halfRange; dy <= halfRange; dy++)
			{
				Position pos{origin.x + dx, origin.y + dy};

				if (!map->IsInside(pos))
				{
					continue;
				}

				std::vector<uint32_t> units = world.getUnitsByPos(pos);
				for (auto unitId : units)
				{
					if (_hiddenUnits.contains(unitId))
					{
						continue;
					}

					const auto foundIt = _distOffset.find(unitId);
					const uint32_t distOffset = (foundIt == _distOffset.end()) ? 0 : foundIt->second;
					const uint32_t dist = std::max(std::abs(dx), std::abs(dy)) + distOffset;
					if (dist < minDist || dist > maxDist)
					{
						continue;
					}

					if (withFlying || !_flyingUnits.contains(unitId))
					{
						result.push_back(unitId);
					}
				}
			}
		}

		return result;
	}

	void SpatialSystem::setFlying(const Unit& unit)
	{
		_flyingUnits.insert(unit.unitId);
	}

	void SpatialSystem::setHidden(const Unit& unit) 
	{
		_hiddenUnits.insert(unit.unitId);
	}

	void SpatialSystem::setDistOffset(const Unit& unit, uint32_t offset)
	{
		_distOffset.insert({unit.unitId, offset});
	}
}
