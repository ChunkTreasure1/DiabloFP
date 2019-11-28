#pragma once

#include <memory>

#include "Enemy.h"

namespace Diablo
{
	class EnemyFactory
	{
	public:
		static std::shared_ptr<Enemy> CreateEnemy();

	private:
		static std::tuple<Stats, std::string, std::shared_ptr<Attack>> GetEnemyStats();
	};
}