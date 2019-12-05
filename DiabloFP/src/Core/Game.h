#pragma once

#include <memory>
#include <Windows.h>

#include "Gameplay/Entities/Player.h"
#include "Rendering/Renderer.h"
#include "Gameplay/Map/Map.h"

#include "Gameplay/Fighting/FightSystem.h"

namespace Diablo
{
	class Game
	{
	public:
		Game();
		~Game();

		void Run();
		bool StartMenu();

		//Setting
		inline void SetIs3D(bool aState) { myIs3D = aState; aState == true ? Renderer::SetBuffer() : SetBuffer(); }
		inline void SetBuffer() { SetConsoleActiveScreenBuffer(myDefaultConsole); }

		//Getting
		inline static Game* Get() { return myInstance; }
		inline const uint32_t GetMapWidth() { return myMapWidth; }
		inline Map* GetMap() { return myMap; }

		PlayerType GetPlayerType();

	private:
		bool myIsRunning;
		bool myIs3D;

		uint32_t myScreenWidth;
		uint32_t myScreenHeight;

		uint32_t myMapWidth;
		uint32_t myMapHeight;

		Map* myMap;
		Player* myPlayer;
		HANDLE myDefaultConsole;

		std::shared_ptr<FightSystem> myFightSystem;

	private:
		static Game* myInstance;
	};
}