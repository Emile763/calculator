#pragma once
#include "Window.h"
#include "Button.h"
#include <iostream>

using buttonContainer = std::vector<Button>;

class Calculator
{
public:
	Calculator(sf::Font *font);
	~Calculator();

	
	void handleInput();
	void update();
	void render();
	
	Window* getWindow();

	

private:

	void calcul();

	Window m_window;
	buttonContainer m_buttons;
	sf::Font *m_font;
	sf::Text m_input;
	sf::Text m_output;
	std::string m_calcul;
	std::string m_result;
};

