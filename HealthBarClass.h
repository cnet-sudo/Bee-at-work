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
    float sizeBar;                // Переменная изменения длинны полосы
    float thicknessBar;           // Толщина
    float divisionUnit;           // Масштаб полосы
    bool full=false;              // Наполнение

public:

    HealthBarClass(sf::RenderWindow & window, float x, float y, bool vertical, float sizeBar = 0.0f, float thicknessBar = 25.0f, float divisionUnit=1.0f)
        :mywindow(window),xpos(x),ypos(y), vert(vertical), sizeBar(sizeBar), thicknessBar(thicknessBar), divisionUnit(divisionUnit)
    {
        barHelth.setPosition(xpos, ypos);
        barHelth.setFillColor(sf::Color::Red);
        container.setPosition(xpos, ypos);
        container.setFillColor(sf::Color(255, 255, 255, 0));
        container.setOutlineColor(sf::Color::Black);
        container.setOutlineThickness(3);

        if (vert) 
        {
        barHelth.setSize(sf::Vector2f(thicknessBar, 0));
        container.setSize(sf::Vector2f(thicknessBar, -100*divisionUnit));
        }
        else
        {
            barHelth.setSize(sf::Vector2f(0, thicknessBar));
            container.setSize(sf::Vector2f(100*divisionUnit, thicknessBar));
        }
    };

    bool getFull() 
    {
        return full;
    }
    float getSizeBar() {
    return sizeBar;
     }
    void increaseOfsize(float size, sf::Time const& dt);   // Изменение наполнения полосы
    void draw();                                         // Рисования полосы жизни
    void setColorBar(sf::Color ColorHelth, sf::Color ColorContainer, float Thickness);  // Установка цвета
    void setSizeBar(float size);
    void increaseOfsize(float size);
    void reset();
};

