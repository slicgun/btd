#include "Application.h"

#include<SFML/Window/Event.hpp>
#include<SFML/Window/Keyboard.hpp>

#include"Clock.h"
#include"../Window.h"

Application::Application()
{
}

void Application::run()
{
	Clock c;

	float lastTime = c.getSeconds();

	while(Window::isOpen())
	{
		float currentTime = c.getSeconds();
		float elapsed = currentTime - lastTime;
		lastTime = currentTime;

		sf::Event e;
		while(Window::pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
				Window::close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			   Window::close();
		}

		for(auto& layer : m_layerStack)
			layer->onUpdate(elapsed);

		Window::update();
	}
}

void Application::pushLayer(const LayerPtr& layer)
{
	m_layerStack.pushLayer(std::forward<LayerPtr>(const_cast<LayerPtr&>(layer)));
}

void Application::popLayer()
{
	m_layerStack.popLayer();
}
