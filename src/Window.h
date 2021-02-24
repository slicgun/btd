#pragma once

#include"Singleton.h"

#include<SFML/Graphics/RenderWindow.hpp>

class Window : public Singleton<Window>
{
public:
	friend class Singleton<Window>;

	static sf::RenderWindow& getWindow() { return get().m_window; }

	///this looks bad, and should be cleaned up at a later date
	static bool isOpen() { return get().getWindow().isOpen(); }
	static void update() { get().getWindow().display(); }
	static void close() { get().getWindow().close(); }
	static bool pollEvent(sf::Event& event) { return get().getWindow().pollEvent(event); }
	static float aspectRatio() { return static_cast<float>(width) / static_cast<float>(720); }
public:
	static constexpr uint32_t width = 1280;
	static constexpr uint32_t height = 720;
private:
	sf::RenderWindow m_window;
private:
	Window()
	{
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 4;
		settings.minorVersion = 6;
		m_window.create(sf::VideoMode(width, height), "Bloons TD", sf::Style::Default, settings);
	}
};