#pragma once

#include <memory>

#include "Enemy.h"

namespace Diablo
{
	class EnemyFactory
	{
	public:
		static std::shared_ptr<Enemy> Create(const glm::vec2& aCharPos);

	private:
		static std::tuple<Stats, std::string, std::shared_ptr<Attack>> GetEnemyStats();
	};
}