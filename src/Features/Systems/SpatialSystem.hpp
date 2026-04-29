#pragma once

#include <Core/Infra/Singleton.hpp>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace sw::core
{
	class Position;
	class Unit;
	class World;
}

namespace sw::features
{
	class SpatialSystem : public core::Singleton<SpatialSystem>
	{
	private:
		std::unordered_map<uint32_t, uint32_t> _distOffset{};
		std::unordered_set<uint32_t> _flyingUnits{};
		std::unordered_set<uint32_t> _hiddenUnits{};

	public:
		std::vector<uint32_t> findUnitsInPoint(
			core::World& world, const core::Position& point, bool withFlying = false);
		std::vector<uint32_t> findUnitsInRange(
			core::World& world,
			const core::Position& origin,
			uint32_t minDist,
			uint32_t maxDist,
			bool withFlying = false);

		void setFlying(uint32_t unitId);
		bool isFlying(uint32_t unitId) const;

		void setHidden(uint32_t unitId);
		bool isHidden(uint32_t unitId) const;

		void setDistOffset(uint32_t unitId, uint32_t offset);
		uint32_t distanceTo(uint32_t unitId, const core::Position& unitPos, const core::Position& origin) const;
	};
}
