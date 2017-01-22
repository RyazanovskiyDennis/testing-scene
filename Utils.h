#pragma once
#include <SDL/SDL.h>
#include <memory>
#include <chrono>

namespace detail
{
	struct SDLWindowDeleter
	{
		void operator()(SDL_Window *ptr) {SDL_DestroyWindow(ptr);}
	};
	struct SDLGLContextDeleter
	{
		void operator()(SDL_GLContext ptr) { SDL_GL_DeleteContext(ptr); }
	};
}
using SDLWindowPtr = std::unique_ptr<SDL_Window, detail::SDLWindowDeleter>;
using SDLGLContextPtr = std::unique_ptr<void, detail::SDLGLContextDeleter>;


class CUtils
{
public:
	CUtils() = delete;
	static void InitOnceSDL();
	static void ValidateSDLErrors();
};

class CChronometer
{
public:
	CChronometer();
	float GrabDeltaTime();
private:
	std::chrono::system_clock::time_point m_lastTime;
};

