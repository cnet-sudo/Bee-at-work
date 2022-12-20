#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


namespace game {

class GameMenu
{
    int max_menu;                // ������������ ���������� ������� ����
	int size_font;               // ������ ������
	int mainMenuSelected;        // �������� ����
	sf::Font font;               // ����� ���� 
	sf::Text * mainMenu;         // ������������ ������ �������� ����
	sf::Color menu_text_color;   // ���� ����
	sf::Color chose_text_color;  // ���� ������ ����
	sf::Color border_color;      // ���� ������� ������

	// ��������� ������ ����
	void setInitFont(sf::Text & text, std::string str, float xpos, float ypos);

public:
	
	GameMenu(float menux, float menuy, int sizeFont = 60, int step = 80, int len_menu = 4);
	// ������ ����
	void draw(sf::RenderWindow & window);

	void MoveUp();               // ����������� ���� �����

	void MoveDown();             // ����������� ���� ����
    
	void setStringMenu(int index,sf::String name);  // ����� ����

	void setColotTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor);  // ���� ����

	void setPositionX(int index, float x1);         // ��������� ��������� ������� ����
	
	int getMainMenuPressed()                        // ��������� ����� ��������� ��������
	{
		return mainMenuSelected;
	}
	~GameMenu()
	{
		delete[] mainMenu;
	}

};

}