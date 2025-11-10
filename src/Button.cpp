#include "Button.h"

Button::Button(sf::Vector2f pos, std::string t, char out) : m_position(pos), m_output(out), m_size(50,50), m_text(t, m_font, 20), m_click(0)
{
	
	if (!m_font.loadFromFile("arial.ttf"))
	{

	}
	
	m_body.setSize(m_size - sf::Vector2f(1.f, 1.f));
	
	
	
	m_text.setPosition(m_position.x * m_size.x+ m_size.x/3, (m_position.y+2) * m_size.y);
	
	std::cout << m_position.x << " : " << m_position.y;

	m_body.setFillColor(sf::Color(100, 100, 100));
	m_body.setPosition((m_position.x * m_size.x), ((m_position.y +2)* m_size.y)+1);
	
	std::cout << m_output << std::endl;
}

Button::~Button()
{

}

void Button::render(Window *window)
{
	
	window->draw(m_body);
	m_text.setFont(m_font);
	window->draw(m_text);
	
	
	
	
}


bool Button::isPressed(Window *window)
{
	if (m_click)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_click = false;
			if (sf::Mouse::getPosition(*window->getWindow()).x / m_size.x > m_position.x  &&
				sf::Mouse::getPosition(*window->getWindow()).x / m_size.x < m_position.x + 1 &&
				sf::Mouse::getPosition(*window->getWindow()).y / m_size.y > m_position.y +2  &&
				sf::Mouse::getPosition(*window->getWindow()).y / m_size.y < m_position.y + 3)
			{
				
				return true;

			}
				
		}
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))	
	{
		m_click = true;
		
	}

	if (sf::Mouse::getPosition(*window->getWindow()).x / m_size.x > m_position.x  &&
		sf::Mouse::getPosition(*window->getWindow()).x / m_size.x < m_position.x + 1 &&
		sf::Mouse::getPosition(*window->getWindow()).y / m_size.y > m_position.y + 2 &&
		sf::Mouse::getPosition(*window->getWindow()).y / m_size.y < m_position.y + 3)
	{
		m_body.setFillColor(sf::Color(75, 75, 75));
		m_text.setFillColor(sf::Color(205, 205, 205));
	}
	else
	{
		m_body.setFillColor(sf::Color(100, 100, 100));
		m_text.setFillColor(sf::Color::White);
	}

	return false;
}

char Button::getOutput()
{
	return m_output;
}