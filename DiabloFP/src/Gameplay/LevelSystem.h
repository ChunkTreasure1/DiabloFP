#pragma once

#include <functional>

namespace Diablo
{
	class LevelSystem
	{
	public:

		//Adding
		static inline void AddXPToPlayer(uint32_t someXP) { myPlayerXP += someXP; Update(); }
		static inline void AddLevelToPlayer(uint32_t someLevel) { myPlayerLevel += someLevel; Update(); }
		static inline void IncreseDifficulty(uint32_t someDiff = 1) { myDifficulty += someDiff; Update(); }

		//Getting
		static inline const uint32_t GetPlayerXP() { return myPlayerXP; }
		static inline const uint32_t GetPlayerLevel() { return myPlayerLevel; }
		static inline const uint32_t GetDifficulty() { return myDifficulty; }

	private:
		static void Update();
		static void AddStat();

	private:
		static uint32_t myPlayerXP;
		static uint32_t myPlayerLevel;
		static uint32_t myDifficulty;
	};
}