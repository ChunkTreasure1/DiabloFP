#pragma once

#include <functional>

namespace Diablo
{
	class Renderer
	{
	public:
		static void Initialize(uint32_t aWidth, uint32_t aHeight);
		static void SetActiveBuffer();
		static void Draw(float aDeltaTime);

	private:
		static uint32_t myWidth;
		static uint32_t myHeight;
	};
}