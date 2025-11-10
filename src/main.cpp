#include "Calculator.h"

int main()
{

	sf::Font font;
	if (font.openFromFile("font/NotoSans-Regular.ttf"))
	{

	}
	Calculator calculator(font);
	
	while (!calculator.getWindow()->isDone())
	{

		calculator.handleInput();
		calculator.update();
		calculator.render();
		
		
	}

	return 0;
}