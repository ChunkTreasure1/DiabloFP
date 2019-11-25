#pragma once

#include <functional>
#include <memory>
#include <Windows.h>

#include "Gameplay/Player.h"
#include "Rendering/Renderer.h"

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

		Player* myPlayer;
		HANDLE myDefaultConsole;

	private:
		static Game* myInstance;
	};
}