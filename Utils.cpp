#include "Utils.h"
#include <iostream>
#include <chrono>
#include <SDL/SDL_error.h>
#include <SDL/SDL.h>

using namespace std;
void CUtils::InitOnceSDL()
{
	static bool didInit = false;
	if (!didInit)
	{
		if (0 != SDL_Init(SDL_INIT_EVERYTHING))
		{
			cerr << "SDL init failed: " << SDL_GetError() << endl;
			abort();
		}
	}
}

void CUtils::ValidateSDLErrors()
{
	string message = SDL_GetError();
	if (message.empty())
	{
		message = "No info about error. KAPPA";
	}
	cerr << "SDL error: " << message.data() << endl;
	abort();
}

CChronometer::CChronometer():m_lastTime(chrono::system_clock::now())
{}

float CChronometer::GrabDeltaTime()
{
	auto newTime = chrono::system_clock::now();
	auto timePassed = chrono::duration_cast<chrono::milliseconds>(newTime - m_lastTime);
	m_lastTime = newTime;
	return 0.001f * float(timePassed.count());
}