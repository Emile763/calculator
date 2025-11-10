#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Window.h"
class Button
{
public:

	Button(sf::Vector2f pos, std::string t, char out);
	
	~Button();

	void render(Window *window);

	bool isPressed(Window *window);

	char getOutput();

private:
	

	sf::Font m_font;
	sf::Text m_text;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	char m_output;
	sf::RectangleShape m_body;

	bool m_click;

};

