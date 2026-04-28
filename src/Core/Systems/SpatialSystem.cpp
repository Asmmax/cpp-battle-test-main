#include "SpatialSystem.hpp"

#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"

namespace sw::core
{
	std::vector<uint32_t> SpatialSystem::findUnitsInPoint(World& world, const Position& point, bool withFlying)
	{
		std::vector<uint32_t> result;

		std::vector<uint32_t> units = world.getUnitsByPos(point);
		for (auto unitId : units)
		{
			if (isHidden(unitId))
			{
				continue;
			}

			if (withFlying || !isFlying(unitId))
			{
				result.push_back(unitId);
			}
		}

		return result;
	}

	std::vector<uint32_t> SpatialSystem::findUnitsInRange(
		World& world, const Position& origin, uint32_t minDist, uint32_t maxDist, bool withFlying)
	{
		std::vector<uint32_t> result;

		Bound* map = world.getMap();
		if (!map || minDist > maxDist)
		{
			return result;
		}

		const int range = static_cast<int>(maxDist);
		const uint32_t size = maxDist * 2 + 1;
		result.reserve(size * size);

		for (int dx = -range; dx <= range; dx++)
		{
			for (int dy = -range; dy <= range; dy++)
			{
				Position pos{origin.x + dx, origin.y + dy};

				if (!map->IsInside(pos))
				{
					continue;
				}

				std::vector<uint32_t> units = findUnitsInPoint(world, pos, withFlying);
				for (auto unitId : units)
				{
					const uint32_t dist = distanceTo(unitId, pos, origin);
					if (dist >= minDist && dist <= maxDist)
					{
						result.push_back(unitId);
					}
				}
			}
		}

		return result;
	}

	void SpatialSystem::setFlying(uint32_t unitId)
	{
		_flyingUnits.insert(unitId);
	}

	bool SpatialSystem::isFlying(uint32_t unitId) const
	{
		return _flyingUnits.contains(unitId);
	}

	void SpatialSystem::setHidden(uint32_t unitId) 
	{
		_hiddenUnits.insert(unitId);
	}

	bool SpatialSystem::isHidden(uint32_t unitId) const
	{
		return _hiddenUnits.contains(unitId);
	}

	void SpatialSystem::setDistOffset(uint32_t unitId, uint32_t offset)
	{
		_distOffset.insert({unitId, offset});
	}

	uint32_t SpatialSystem::distanceTo(uint32_t unitId, const Position& unitPos, const Position& origin) const
	{
		const int dx = static_cast<int>(unitPos.x) - static_cast<int>(origin.x);
		const int dy = static_cast<int>(unitPos.y) - static_cast<int>(origin.y);

		const auto it = _distOffset.find(unitId);
		const uint32_t offset = (it != _distOffset.end()) ? it->second : 0;
		const uint32_t base = std::max(static_cast<uint32_t>(std::abs(dx)), static_cast<uint32_t>(std::abs(dy)));
		return base + offset;
	}
}
