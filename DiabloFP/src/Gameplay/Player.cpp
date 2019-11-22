#include "Player.h"

namespace Diablo
{
	Player* Player::myInstance = nullptr;

	Player::Player()
		: myDepth(16.f), myFOV(3.14159f / 4.f), mySpeed(5.f),
		myXPos(14.7f), myYPos(5.09f), myAngle(0)
	{
		myInstance = this;
	}
}