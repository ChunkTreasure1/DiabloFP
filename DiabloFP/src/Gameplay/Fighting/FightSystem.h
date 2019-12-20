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
		static inline Ref<FightSystem>& Get() { return mypInstance; }

		void GameOver();
		FightExit FightEnemy(Ref<Enemy>& apEnemy);

	private:
		bool AttackPlayer(Ref<Enemy>& apEnemy);
		bool AttackPlayer(Ref<Enemy>& apEnemy, uint32_t aValue);
		bool AttackEnemy(Ref<Enemy>& apEnemy, Ref<Attack>& apAttack);

	private:
		static Ref<FightSystem> mypInstance;
	};
}