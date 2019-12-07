#pragma once
 
namespace Diablo
{
	class Utility
	{
	public:
		Utility() = delete;

		static int GetRounded(float aVal)
		{
			if (aVal != 0)
			{
				aVal += 0.5f;;
				return (int)aVal;
			}
			else
			{
				return 0;
			}
		}
	};
}