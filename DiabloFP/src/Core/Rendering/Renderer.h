#pragma once

#include <functional>
#include <string>

namespace Diablo
{
	class Renderer
	{
	public:
		static void Initialize(uint32_t aWidth, uint32_t aHeight);
		static void Update(uint32_t aMapSize, const std::wstring& aMap);

		static void SetBuffer();
		static void Draw(float aDeltaTime);

	private:
		static uint32_t myWidth;
		static uint32_t myHeight;
		static uint32_t myMapSize;
	};
}