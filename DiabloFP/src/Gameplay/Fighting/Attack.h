#pragma once

#include <string>

namespace Diablo
{
	class Attack
	{
	public:

		//Setting
		inline void SetSpeed(float aSpeed) { mySpeed = aSpeed; }
		inline void SetDamage(float aDamage) { myDamage = aDamage; }
		inline void SetName(std::string& aName) { myName = aName; }

		//Getting
		inline float GetSpeed() const { return mySpeed; }
		inline float GetDamage() const { return myDamage; }
		inline std::string GetName() const { return myName; }

	protected:
		Attack(const std::string& aName)
			: myName(aName)
		{}

		float mySpeed;
		float myDamage;

		std::string myName;
	};
}