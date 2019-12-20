#pragma once

#include <memory>

#include "Enemy.h"

namespace Diablo
{
	class EnemyFactory
	{
	public:
		static Ref<Enemy> Create(const glm::vec2& aCharPos);

	private:
		static std::tuple<Stats, std::string, Ref<Attack>> GetEnemyStats();
	};
}