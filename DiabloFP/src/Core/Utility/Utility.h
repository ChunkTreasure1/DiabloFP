#pragma once
 
#define REGISTER_EQUIPMENT(x) EquipmentFactory::Register(x::GetFactoryName(), x::Create);
#define REGISTER_ITEM(x) ItemFactory::Register(x::GetFactoryName(), x::CreateMethod);

namespace Diablo
{
	class Utility
	{
	public:
		Utility() = delete;

		static int Rounded(float aVal)
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