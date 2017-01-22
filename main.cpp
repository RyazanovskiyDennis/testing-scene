#include <SDL/SDL.h>
#include "AbstractWindow.h"
#include <glm/glm.hpp>
#undef main
class CWindow : public CAbstractWindow
{
protected:
	void OnWindowEvent(const SDL_Event &event) override
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				SDL_Event esc_exit(event);
				esc_exit.type = SDL_QUIT;
				SDL_PushEvent(&esc_exit);
				break;
			case SDLK_r:
				SetBackgroundColor({1,0,0,1});
				break;
			case SDLK_g:
				SetBackgroundColor({ 0, 1, 0, 1 });
				break;
			case SDLK_b:
				SetBackgroundColor({ 0, 0, 1, 1 });
				break;
			}
		}
	}
	void OnUpdateWindow(float deltaSeconds) override
	{
		(void)deltaSeconds;
	}
	void OnDrawWindow()override
	{}
};

int main(int argc, char*argv[])
{
	CWindow window;
	window.ShowFixedSize({ 800, 600 });
	window.DoGameLoop();
	system("pause");
	return 0;
}

