#pragma once

#include "Gameplay/Entities/Enemy/Enemy.h"

#include <memory>

namespace Diablo
{
	enum class FightExit
	{
		EnemyKilled = 0,
		PlayerKilled,
		Fleed
	};

	class FightSystem
	{
	public:
		FightSystem();
		~FightSystem();

		//Getting
		static inline std::shared_ptr<FightSystem>& Get() { return mypInstance; }

		void GameOver();
		FightExit FightEnemy(std::shared_ptr<Enemy>& apEnemy);

	private:
		bool AttackPlayer(std::shared_ptr<Enemy>& apEnemy);
		bool AttackPlayer(std::shared_ptr<Enemy>& apEnemy, uint32_t aValue);
		bool AttackEnemy(std::shared_ptr<Enemy>& apEnemy, std::shared_ptr<Attack>& apAttack);

	private:
		static std::shared_ptr<FightSystem> mypInstance;
	};
}