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
    double sizeBar;                // ���������� ��������� ������ ������
    float thicknessBar;           // �������
    float divisionUnit;           // ������� ������
    bool full=false;              // ����������
    bool empty=true;              // ����������
    float resetBar;
    sf::Color ColorHelth = sf::Color::Red;      // ���� ������ �����
public:

    HealthBarClass(sf::RenderWindow & window, float x, float y, bool vertical, float sizeBar = 0.0f, float thicknessBar = 25.0f, float divisionUnit=1.0f)
        :mywindow(window),xpos(x),ypos(y), vert(vertical), sizeBar(sizeBar), thicknessBar(thicknessBar), divisionUnit(divisionUnit)
    {
        if (sizeBar > 0) empty = false;
        if (sizeBar == 100) full = true;
        resetBar = sizeBar;
        barHelth.setPosition(xpos, ypos);
        barHelth.setFillColor(ColorHelth);
        container.setPosition(xpos, ypos);
        container.setFillColor(sf::Color(255, 255, 255, 0));
        container.setOutlineColor(sf::Color::Black);
        container.setOutlineThickness(3);

        if (vert) 
        {
        barHelth.setOrigin(0, sizeBar * divisionUnit);
        barHelth.setSize(sf::Vector2f(thicknessBar, sizeBar* divisionUnit));
        container.setOrigin(0, 100* divisionUnit);
        container.setSize(sf::Vector2f(thicknessBar, 100 * divisionUnit));
        }
        else
        {
            barHelth.setSize(sf::Vector2f(sizeBar * divisionUnit, thicknessBar));
            container.setSize(sf::Vector2f(100*divisionUnit, thicknessBar));
        }
    };

    bool getFull() const
    {
        return full;
    }
    bool getEmpty() const
    {
        return empty;
    }
    double getSizeBar() const {
    return sizeBar;
     }

    sf::Color getColorHelth() const
    {
        return ColorHelth;
    }

    void changeOfbar(double size, sf::Time const& dt);   // ��������� ���������� ������
    void changeOfbar(double size);
    void draw();                                         // ��������� ������ �����
    void setColorBar(sf::Color ColorHelth, sf::Color ColorContainer, float Thickness);  // ��������� �����
    void setSizeBar(float size);
    void reset();
};

