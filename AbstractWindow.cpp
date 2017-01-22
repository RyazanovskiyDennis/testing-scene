#include "AbstractWindow.h"
#include "Utils.h"
#include <GL/freeglut.h>
#include <SDL/SDL.h>
#include <SDL/SDL_video.h>
#include <glm/glm.hpp>
#include <iostream>
using namespace std;
namespace
{
	const char WINDOW_TITLE[] = "SDL + OpenGL Demo";
}
class CAbstractWindow::Impl
{
public:
	void ShowFixedSize(glm::ivec2 const& size)
	{
		CUtils::InitOnceSDL();
		m_pWindow.reset(SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			size.x, size.y, SDL_WINDOW_OPENGL));
		m_pGLContext.reset(SDL_GL_CreateContext(m_pWindow.get()));
		if (!m_pGLContext)
		{
			CUtils::ValidateSDLErrors();
		}
	}

	void SetBackgroundColor(const glm::vec4 &color){ m_clearColor = color; }
	void Clear() const
	{
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void SwapBuffers()
	{
		SDL_GL_SwapWindow(m_pWindow.get());
	}
private:
	SDLWindowPtr m_pWindow;
	SDLGLContextPtr m_pGLContext;
	glm::vec4 m_clearColor;
};
CAbstractWindow::CAbstractWindow() :m_pImpl(new Impl){}
CAbstractWindow::~CAbstractWindow(){}

void CAbstractWindow::ShowFixedSize(const glm::ivec2 &size) {m_pImpl->ShowFixedSize(size);}

void CAbstractWindow::DoGameLoop()
{
	SDL_Event event;
	CChronometer chronometer;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				cout << "OLOLOLO" << endl;
			}
			else OnWindowEvent(event);
		}
		if (running)
		{
			m_pImpl->Clear();
			const float deltaSeconds = chronometer.GrabDeltaTime();
			OnUpdateWindow(deltaSeconds);
			OnDrawWindow();
			m_pImpl->SwapBuffers();
		}
	}
}

void CAbstractWindow::SetBackgroundColor(const glm::vec4 &color) {m_pImpl->SetBackgroundColor(color);}