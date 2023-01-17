#pragma once
#include <SFML/Graphics.hpp>

class HealthBarClass
{
    sf::RectangleShape barHelth;  // ������ �����
    
    sf::RectangleShape container; // ����� �����

    sf::RenderWindow& mywindow;   // ������ �� ����������� ����
    sf::Time m_duration;
    float xpos;                   // ���������� �
    float ypos;                   // ���������� y
    bool vert;                    // ��������� ������ �����������, �������������
    float sizeBar;                // ���������� ��������� �����
    float divisionUnit;           // ������� ������

public:

    HealthBarClass(sf::RenderWindow & window, float x, float y, bool vertical, float sizeBar = 0.0f, float divisionUnit=1.0f) 
        :mywindow(window),xpos(x),ypos(y), vert(vertical), sizeBar(sizeBar), divisionUnit(divisionUnit)
    {
        barHelth.setPosition(xpos, xpos);
        barHelth.setFillColor(sf::Color::Red);
        container.setPosition(xpos, xpos);
        container.setFillColor(sf::Color(255, 255, 255, 0));
        container.setOutlineColor(sf::Color::Black);
        container.setOutlineThickness(3);

        if (vert) 
        {
        barHelth.setSize(sf::Vector2f(25, 0));
        container.setSize(sf::Vector2f(25, 100*divisionUnit));
        }
        else
        {
            barHelth.setSize(sf::Vector2f(0, 25));
            container.setSize(sf::Vector2f(100*divisionUnit, 25));
        }
    };

    void changeOfsize(float size, sf::Time const& dt);   // ��������� ���������� ������
    void draw();                                         // ��������� ������ �����
    void setColorBar(sf::Color ColorHelth, sf::Color ColorContainer, float Thickness);  // ��������� �����
    void reset();
};

