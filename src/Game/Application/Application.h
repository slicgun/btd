#pragma once

#include"../Window.h"
#include"LayerStack.h"

#include<vector>

class Application
{
public:
	Application();
	~Application() = default;

	void run();
	Window& getWindow() { return Window::get(); }
	sf::RenderWindow& getSFMLWindow() { return Window::getWindow(); }

	void pushLayer(const LayerPtr& layer);
	void popLayer();
private:
	LayerStack m_layerStack;
};