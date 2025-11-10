#include "Window.h"

Window::Window(const sf::Vector2u &size, const std::string &title) : m_focus(true), m_click(false)
{
	setup(size, title);
}

Window::~Window()
{
}

void Window::setup(const sf::Vector2u &size, const std::string &title)
{
	m_size = size;
	m_isDone = false;
	m_title = title;

	m_close.setSize({20, 20});
	m_close.setFillColor(sf::Color::Red);
	m_close.setPosition(sf::Vector2f(float(m_size.x) - 20, 0));
	m_bar.setSize({float(m_size.x), 20.f});
	m_bar.setFillColor(sf::Color(20, 20, 20));
	m_bar.setPosition(sf::Vector2f(0, 0));
	create();
}

void Window::create()
{
	m_window.create(sf::VideoMode({m_size.x, m_size.y}, 32), m_title, sf::Style::None);
}

void Window::update()
{

	while (const std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::FocusLost>())
			m_focus = false;
		if (event->is<sf::Event::FocusGained>())
			m_focus = true;

		if (event->is<sf::Event::Closed>())
			m_isDone = true;
	}

	if (m_focus)
	{

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			m_click = true;
		}
		if (m_click)
		{
			if (sf::Mouse::getPosition(m_window).x < int(m_size.x) - 20 && sf::Mouse::getPosition(m_window).x > 0 && sf::Mouse::getPosition(m_window).y < 20 && sf::Mouse::getPosition(m_window).y > 0)
			{
				sf::Vector2i mPos = {sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y};
				while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					m_window.setPosition(sf::Mouse::getPosition() - mPos);
			}
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				m_click = false;

			if (!m_click && sf::Mouse::getPosition(m_window).x < int(m_size.x) && sf::Mouse::getPosition(m_window).x > int(m_size.x) - 20 && sf::Mouse::getPosition(m_window).y < 20 && sf::Mouse::getPosition(m_window).y > 0)
			{
				m_isDone = true;
			}
			else if (m_click && sf::Mouse::getPosition(m_window).x < int(m_size.x) && sf::Mouse::getPosition(m_window).x > int(m_size.x) - 20 && sf::Mouse::getPosition(m_window).y < 20 && sf::Mouse::getPosition(m_window).y > 0)
			{
				m_close.setFillColor(sf::Color(200, 0, 0));
			}
			else
				m_close.setFillColor(sf::Color::Red);
		}
	}
}

void Window::beginDraw(const sf::Color &color)
{
	m_window.clear(color);
}
void Window::draw(const sf::Drawable &drawable)
{
	m_window.draw(drawable);
}
void Window::endDraw()
{
	draw(m_bar);
	draw(m_close);
	m_window.display();
}

bool Window::isDone()
{
	return m_isDone;
}

void Window::destroy()
{
	m_window.close();
}

sf::Vector2u Window::getSize()
{
	return m_size;
}

sf::RenderWindow *Window::getWindow()
{
	return &m_window;
}