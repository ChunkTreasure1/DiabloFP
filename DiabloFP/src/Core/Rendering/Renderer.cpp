#include "Renderer.h"

#include <Windows.h>
#include <string>
#include <vector>
#include <Algorithm>

#include "Gameplay/Player.h"

namespace Diablo
{
	struct RendererStorage
	{
		wchar_t* Screen;
		HANDLE Console;
		DWORD BytesWritten;

		std::wstring Map;
	};

	static RendererStorage* sData = nullptr;
	uint32_t Renderer::myHeight = 0;
	uint32_t Renderer::myWidth = 0;
	uint32_t Renderer::myMapSize = 0;

	void Renderer::Initialize(uint32_t aWidth, uint32_t aHeight)
	{
		myWidth = aWidth;
		myHeight = aHeight;

		sData = new RendererStorage();
		sData->Screen = new wchar_t[myWidth * myHeight];
		sData->Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		sData->BytesWritten = 0;
	}

	void Renderer::Update(uint32_t aMapSize, const std::wstring& aMap)
	{
		myMapSize = aMapSize;
		sData->Map = aMap;
	}

	void Renderer::SetBuffer()
	{
		SetConsoleActiveScreenBuffer(sData->Console);
	}

	void Renderer::Draw(float aDeltaTime)
	{
		Player* tempPlayer = Player::Get();

		for (int x = 0; x < myWidth; x++)
		{
			// For each column, calculate the projected ray angle into world space
			float fRayAngle = (tempPlayer->GetAngle() - tempPlayer->GetFOV() / 2.0f) + ((float)x / (float)myWidth) * tempPlayer->GetFOV();

			// Find distance to wall
			float fStepSize = 0.1f;		  // Increment size for ray casting, decrease to increase										
			float fDistanceToWall = 0.0f; //                                      resolution

			bool bHitWall = false;		// Set when ray hits wall block
			bool bBoundary = false;		// Set when ray hits boundary between two wall blocks

			float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
			float fEyeY = cosf(fRayAngle);

			// Incrementally cast ray from player, along ray angle, testing for 
			// intersection with a block
			while (!bHitWall && fDistanceToWall < tempPlayer->GetDepth())
			{
				fDistanceToWall += fStepSize;
				int nTestX = (int)(tempPlayer->GetXPos() + fEyeX * fDistanceToWall);
				int nTestY = (int)(tempPlayer->GetYPos() + fEyeY * fDistanceToWall);

				// Test if ray is out of bounds
				if (nTestX < 0 || nTestX >= myMapSize || nTestY < 0 || nTestY >= myMapSize)
				{
					bHitWall = true;			// Just set distance to maximum depth
					fDistanceToWall = tempPlayer->GetDepth();
				}
				else
				{
					// Ray is inbounds so test to see if the ray cell is a wall block
					if (sData->Map.c_str()[nTestX * myMapSize + nTestY] == '#')
					{
						// Ray has hit wall
						bHitWall = true;

						// To highlight tile boundaries, cast a ray from each corner
						// of the tile, to the player. The more coincident this ray
						// is to the rendering ray, the closer we are to a tile 
						// boundary, which we'll shade to add detail to the walls
						std::vector<std::pair<float, float>> p;

						// Test each corner of hit tile, storing the distance from
						// the player, and the calculated dot product of the two rays
						for (int tx = 0; tx < 2; tx++)
							for (int ty = 0; ty < 2; ty++)
							{
								// Angle of corner to eye
								float vy = (float)nTestY + ty - tempPlayer->GetYPos();
								float vx = (float)nTestX + tx - tempPlayer->GetXPos();
								float d = sqrt(vx * vx + vy * vy);
								float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
								p.push_back(std::make_pair(d, dot));
							}

						// Sort Pairs from closest to farthest
						sort(p.begin(), p.end(), [](const std::pair<float, float>& left, const std::pair<float, float>& right) { return left.first < right.first; });

						// First two/three are closest (we will never see all four)
						float fBound = 0.01;
						if (acos(p.at(0).second) < fBound) bBoundary = true;
						if (acos(p.at(1).second) < fBound) bBoundary = true;
						if (acos(p.at(2).second) < fBound) bBoundary = true;
					}
				}
			}

			// Calculate distance to ceiling and floor
			int nCeiling = (float)(myHeight / 2.0) - myHeight / ((float)fDistanceToWall);
			int nFloor = myHeight - nCeiling;

			// Shader walls based on distance
			short nShade = ' ';
			if (fDistanceToWall <= tempPlayer->GetDepth() / 4.0f)			nShade = 0x2588;	// Very close	
			else if (fDistanceToWall < tempPlayer->GetDepth() / 3.0f)		nShade = 0x2593;
			else if (fDistanceToWall < tempPlayer->GetDepth() / 2.0f)		nShade = 0x2592;
			else if (fDistanceToWall < tempPlayer->GetDepth())				nShade = 0x2591;
			else											nShade = ' ';		// Too far away

			if (bBoundary)		nShade = ' '; // Black it out

			for (int y = 0; y < myHeight; y++)
			{
				// Each Row
				if (y <= nCeiling)
					sData->Screen[y * myWidth + x] = ' ';
				else if (y > nCeiling&& y <= nFloor)
					sData->Screen[y * myWidth + x] = nShade;
				else // Floor
				{
					// Shade floor based on distance
					float b = 1.0f - (((float)y - myHeight / 2.0f) / ((float)myHeight / 2.0f));
					if (b < 0.25)		nShade = '#';
					else if (b < 0.5)	nShade = 'x';
					else if (b < 0.75)	nShade = '.';
					else if (b < 0.9)	nShade = '-';
					else				nShade = ' ';
					sData->Screen[y * myWidth + x] = nShade;
				}
			}
		}

		// Display Stats
		swprintf_s(sData->Screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", tempPlayer->GetXPos(), tempPlayer->GetYPos(), tempPlayer->GetAngle(), 1.0f / aDeltaTime);

		// Display Map
		for (int nx = 0; nx < myMapSize; nx++)
			for (int ny = 0; ny < myMapSize; ny++)
			{
				sData->Screen[(ny + 1) * myWidth + nx] = sData->Map[ny * myMapSize + nx];
			}
		sData->Screen[((int)tempPlayer->GetXPos() + 1) * myWidth + (int)tempPlayer->GetYPos()] = 'P';

		// Display Frame
		sData->Screen[myWidth * myHeight - 1] = '\0';
		WriteConsoleOutputCharacter(sData->Console, sData->Screen, myWidth * myHeight, { 0,0 }, &sData->BytesWritten);
	}
}