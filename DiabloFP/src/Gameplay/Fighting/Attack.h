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
		inline const float GetBaseDamage() { return myBaseDamage; }

	protected:
		Attack(const std::string& aName)
			: myName(aName), myDamage(0), mySpeed(0), myBaseDamage(0)
		{}

		float mySpeed;
		float myDamage;
		float myBaseDamage;

		std::string myName;
	};
}