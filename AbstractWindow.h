#pragma once
#include <memory>
#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <boost/noncopyable.hpp>

class CAbstractWindow : private boost::noncopyable
{
public:
	CAbstractWindow();
	virtual ~CAbstractWindow();
	void ShowFixedSize(glm::ivec2 const& size);
	void DoGameLoop();
protected:
	void SetBackgroundColor(glm::vec4 const& color);
	virtual void OnWindowEvent(const SDL_Event &event) = 0;
	virtual void OnUpdateWindow(float deltaSeconds) = 0;
	virtual void OnDrawWindow() = 0;
private:
	class Impl;
	std::unique_ptr<Impl> m_pImpl;
};

