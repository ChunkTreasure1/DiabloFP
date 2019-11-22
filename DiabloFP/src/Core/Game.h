#pragma once

#include <functional>
#include <memory>

#include "../Gameplay/Player.h"

namespace Diablo
{
	class Game
	{
	public:
		Game();
		~Game();

		void Run();
		void StartMenu();

		//Getting
		inline static Game* Get() { return myInstance; }
		
		inline const float GetMapWidth() { return myMapWidth; }

	private:
		bool myIsRunning;
		bool myIs3D;

		uint32_t myScreenWidth;
		uint32_t myScreenHeight;

		uint32_t myMapWidth;
		uint32_t myMapHeight;

		Player* myPlayer;

	private:
		static Game* myInstance;
	};
}