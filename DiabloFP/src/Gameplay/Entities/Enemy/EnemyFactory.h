#pragma once

#include <memory>

#include "Enemy.h"

namespace Diablo
{
	class EnemyFactory
	{
	public:
		static Ref<Enemy> Create(const glm::vec2& aCharPos);
		static Ref<Enemy> CreateBoss();

	private:
		static std::tuple<Stats, std::string, Ref<Attack>> GetEnemyStats();
	};
}