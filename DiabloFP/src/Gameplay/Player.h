#pragma once

namespace Diablo
{
	class Player
	{
	public:
		Player();
		~Player() = default;

		//Setting
		inline void SetXPos(float aPos) { myXPos = aPos; }
		inline void SetYPos(float aPos) { myYPos = aPos; }
		inline void SetAngle(float anAngle) { myAngle = anAngle; }

		//Getting
		inline const float GetXPos() { return myXPos; }
		inline const float GetYPos() { return myYPos; }
		inline const float GetAngle() { return myAngle; }

		inline const float GetSpeed() { return mySpeed; }
		inline const float GetFOV() { return myFOV; }
		inline const float GetDepth() { return myDepth; }

		inline static Player* Get() { return myInstance; }

	private:
		float myXPos;
		float myYPos;
		float myFOV;

		float myDepth;
		float mySpeed;
		float myAngle;

	private:
		static Player* myInstance;
	};
}