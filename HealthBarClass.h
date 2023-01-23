#pragma once
#include <SFML/Graphics.hpp>

class HealthBarClass
{
    sf::RectangleShape barHelth;  // Полоса жизни 
    sf::RectangleShape container; // Сосуд жизни
    sf::RenderWindow& mywindow;   // ссылка на графическое окно
    sf::Time m_duration;
    float xpos;                   // Координаты х
    float ypos;                   // Координаты y
    bool vert;                    // Положение полосы вертикально, горизонтально
    double sizeBar;                // Переменная изменения длинны полосы
    float thicknessBar;           // Толщина
    float divisionUnit;           // Масштаб полосы
    bool full=false;              // Наполнение
    bool empty=true;              // Наполнение
    float resetBar;
public:

    HealthBarClass(sf::RenderWindow & window, float x, float y, bool vertical, float sizeBar = 0.0f, float thicknessBar = 25.0f, float divisionUnit=1.0f)
        :mywindow(window),xpos(x),ypos(y), vert(vertical), sizeBar(sizeBar), thicknessBar(thicknessBar), divisionUnit(divisionUnit)
    {
        if (sizeBar > 0) empty = false;
        if (sizeBar == 100) full = true;
        resetBar = sizeBar;
        barHelth.setPosition(xpos, ypos);
        barHelth.setFillColor(sf::Color::Red);
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

    void changeOfbar(double size, sf::Time const& dt);   // Изменение наполнения полосы
    void changeOfbar(double size);
    void draw();                                         // Рисования полосы жизни
    void setColorBar(sf::Color ColorHelth, sf::Color ColorContainer, float Thickness);  // Установка цвета
    void setSizeBar(float size);
    void reset();
};

