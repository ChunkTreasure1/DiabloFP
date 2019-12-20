#pragma once

#define REGISTER_EQUIPMENT(x) EquipmentFactory::Register(x::GetFactoryName(), x::Create);
#define REGISTER_ITEM(x) ItemFactory::Register(x::GetFactoryName(), x::CreateMethod);

#include <memory>

namespace Diablo
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

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

		template<typename T, typename E>
		static Scope<T> static_unique_ptr_cast(Scope<E>&& aPtr)
		{
			return Scope<T>{ static_cast<T*>(aPtr.release()) };
		}
	};
}