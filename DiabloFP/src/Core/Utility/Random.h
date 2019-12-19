#pragma once
#include <random>

namespace Diablo
{
	class Random
	{
	public:
		Random() = delete;

		static int Int(int aMin, int aMax)
		{
			std::random_device tempDev;
			std::mt19937 tempRand(tempDev());
			std::uniform_int_distribution<std::mt19937::result_type> tempDist(aMin, aMax);

			return tempDist(tempRand);
		}

		static float Float(float aMin, float aMax)
		{
			return float(Int(aMin, aMax)) / float(Int(aMin, aMax)) * 0.5f;
		}
	};
}