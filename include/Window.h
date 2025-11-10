#pragma once

#include <SFML/Graphics.hpp>

class Window
{
public:

	Window(const sf::Vector2u &size = sf::Vector2u(30 ,30), const std::string &title = "Error");
	~Window();

	void setup(const sf::Vector2u &size, const std::string &title);
	void create();

	
	void update();
	void beginDraw(const sf::Color &color);
	void draw(const sf::Drawable &drawable);
	void endDraw();

	bool isDone();

	void destroy();

	sf::Vector2u getSize();

	sf::RenderWindow* getWindow();

private:

	sf::RenderWindow m_window;
	sf::RectangleShape m_close;
	sf::RectangleShape m_bar;

	sf::Vector2u m_size;
	std::string m_title;

	bool m_focus;
	bool m_click;

	bool m_isDone;

};

