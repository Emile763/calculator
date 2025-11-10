#include "Calculator.h"

Calculator::Calculator(sf::Font &font)
	: m_window({300, 400}, "Calculator"), m_input(font), m_output(font), m_calcul(""), m_result("=")
{

	m_input.setCharacterSize(30);
	m_output.setCharacterSize(20);
	m_input.setPosition({0, 20});
	m_output.setPosition({100, 40});

	m_buttons.reserve(10 + 8);
	int i = 9;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 2; x >= 0; x--)
		{
			m_buttons.emplace_back(sf::Vector2f{float(x), float(y)}, std::to_string(i), i + '0', font);
			i--;
		}
	}

	m_buttons.emplace_back(sf::Vector2f{1.f, 3.f}, "0", '0', font);
	m_buttons.emplace_back(sf::Vector2f{3.f, 0.f}, "+", '+', font);
	m_buttons.emplace_back(sf::Vector2f{3.f, 1.f}, "-", '-', font);
	m_buttons.emplace_back(sf::Vector2f{3.f, 2.f}, "*", '*', font);
	m_buttons.emplace_back(sf::Vector2f{3.f, 3.f}, "=", '=', font);
	m_buttons.emplace_back(sf::Vector2f{2.f, 3.f}, "/", '/', font);
	m_buttons.emplace_back(sf::Vector2f{0.f, 3.f}, ".", '.', font);
	m_buttons.emplace_back(sf::Vector2f{4.f, 0.f}, "<-", '<', font);
	m_buttons.emplace_back(sf::Vector2f{4.f, 1.f}, "C", 'C', font);
}

Calculator::~Calculator()
{
}

void Calculator::handleInput()
{
	for (std::size_t i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i].isPressed(&m_window))
		{
			char out = m_buttons[i].getOutput();

			if (m_calcul.size() != 0 && out == '=')
			{
				calcul();
			}
			else if (m_calcul.size() != 0 && out == '<')
			{
				m_calcul.pop_back();
				m_input.setString(m_calcul);
			}
			else if (out == 'C')
			{
				m_calcul.clear();
				m_result.clear();
				m_output.setString(m_result);
				m_input.setString(m_calcul);
			}
			else if (m_calcul.size() != 0 && m_calcul[m_calcul.size() - 1] >= '0' && m_calcul[m_calcul.size() - 1] <= '9')
			{
				m_calcul.push_back(out);
				m_input.setString(m_calcul);
			}
			else if (out >= '0' && out <= '9')
			{

				// std::cout << "chiffre" << std::endl;
				m_calcul.push_back(out);
				m_input.setString(m_calcul);
			}
		}
	}
}

void Calculator::update()
{
	m_window.update();
}

void Calculator::render()
{
	m_window.beginDraw(sf::Color(50, 50, 50));
	m_window.draw(m_input);
	m_window.draw(m_output);
	for (std::size_t i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].render(&m_window);
	}
	m_window.endDraw();
}

Window *Calculator::getWindow()
{
	return &m_window;
}

void Calculator::calcul()
{
	std::vector<std::string> nbrs;
	nbrs.clear();
	int nbr = 0;
	nbrs.push_back("");

	for (auto itr = m_calcul.begin(); itr != m_calcul.end();)
	{
		if ((*itr >= '0' && *itr <= '9') || *itr == '.')
		{
			nbrs[nbr].push_back(*itr);
			m_calcul.erase(itr);
		}
		else
		{
			itr++;
			nbrs.push_back("");
			nbr++;
		}
	}
	if (nbrs[nbrs.size() - 1] == "")
	{
		nbrs.pop_back();
		m_calcul.pop_back();
	}

	std::vector<std::string> nbrs2;
	auto itrc = m_calcul.begin();
	auto itrn = nbrs.begin();
	for (std::size_t i = 0; i < m_calcul.size();)
	{

		if (m_calcul[i] == '*')
		{

			itrc = m_calcul.begin() + i;
			itrn = nbrs.begin() + i + 1;
			nbrs[i] = (std::to_string((stof(nbrs[i]) * stof(nbrs[i + 1]))));
			nbrs.erase(itrn);
			m_calcul.erase(itrc);

			i--;
		}
		else if (m_calcul[i] == '/')
		{
			itrc = m_calcul.begin() + i;
			itrn = nbrs.begin() + i + 1;
			nbrs[i] = (std::to_string((stof(nbrs[i]) / stof(nbrs[i + 1]))));
			nbrs.erase(itrn);
			m_calcul.erase(itrc);
			std::cout << nbrs[i] << std::endl;

			i--;
		}
		++i;
	}

	// for (std::size_t x = 0; x < nbrs.size(); x++)
	// {
	// 	std::cout << nbrs[x] << std::endl;
	// }
	// std::cout << m_calcul << std::endl;

	for (std::size_t i = 0; i < m_calcul.size();)
	{

		if (m_calcul[i] == '+')
		{
			itrc = m_calcul.begin() + i;
			itrn = nbrs.begin() + i + 1;
			nbrs[i] = (std::to_string((stof(nbrs[i]) + stof(nbrs[i + 1]))));

			nbrs.erase(itrn);
			m_calcul.erase(itrc);
			// std::cout << "+" << std::endl;

			i--;
		}
		else if (m_calcul[i] == '-')
		{
			itrc = m_calcul.begin() + i;
			itrn = nbrs.begin() + i + 1;
			nbrs[i] = (std::to_string((stof(nbrs[i]) - stof(nbrs[i + 1]))));
			nbrs.erase(itrn);
			m_calcul.erase(itrc);
			// std::cout << "-" << std::endl;
			i--;
		}
		++i;
	}
	if (stof(nbrs[0]) - stoi(nbrs[0]) == 0)
		m_result = std::to_string(stoi(nbrs[0]));
	else
	{
		for (int i = nbrs[0].size() - 1; i > 0; i--)
		{
			if (nbrs[0][i] == '0')
			{
				nbrs[0].erase(nbrs[0].begin() + i);
			}
			else
			{
				i = 0;
			}
		}
		m_result = nbrs[0];
	}

	m_output.setString("=" + m_result);
	m_output.setPosition({m_window.getSize().x - m_output.getGlobalBounds().size.x - 5, 50});

	m_calcul.clear();
}