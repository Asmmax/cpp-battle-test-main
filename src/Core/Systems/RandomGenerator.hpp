#pragma once

#include <vector>
#include <random>

namespace sw::core
{
	class RandomGenerator
	{
	private:
		uint32_t _seed{};
		std::mt19937 _engine;

	public:
		RandomGenerator() :
				_seed(std::random_device{}()),
				_engine(_seed)
		{}

		explicit RandomGenerator(uint32_t customSeed) :
				_seed(customSeed),
				_engine(_seed)
		{}

		template <typename T>
		uint32_t choose(const std::vector<T>& sample)
		{
			if (sample.empty())
			{
				return static_cast<uint32_t>(-1);
			}

			std::uniform_int_distribution<size_t> dist(0, sample.size() - 1);

			return dist(_engine);
		}
	};
}
