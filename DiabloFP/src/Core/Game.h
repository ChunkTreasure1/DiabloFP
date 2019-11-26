#pragma once

#include <memory>
#include <Windows.h>

#include "Gameplay/Player.h"
#include "Rendering/Renderer.h"
#include "Gameplay/Map/Map.h"

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
		inline void SetBuffer() { SetConsoleActiveScreenBuffer(myBuffer); }

		//Getting
		inline static Game* Get() { return myInstance; }
		inline const uint32_t GetMapWidth() { return myMapWidth; }

		//Setting
		inline void SetIs3D(bool aState) { myIs3D = aState; myIs3D == true ? Renderer::SetActiveBuffer() : SetActiveBuffer(); }

	public:
		void SetActiveBuffer() { SetConsoleActiveScreenBuffer(myDefaultConsole); }

	private:
		bool myIsRunning;
		bool myIs3D;

		uint32_t myScreenWidth;
		uint32_t myScreenHeight;

		uint32_t myMapWidth;
		uint32_t myMapHeight;

		HANDLE myBuffer;
		Map* myMap;
		Player* myPlayer;
		HANDLE myDefaultConsole;

	private:
		static Game* myInstance;
	};
}