#include "HealthBarClass.h"

void HealthBarClass::draw() 
{
	mywindow.draw(barHelth);
	mywindow.draw(container);	
}

void HealthBarClass::changeOfsize(float size, sf::Time const& dt)
{
    m_duration += dt;

    if (m_duration > sf::milliseconds(20))
    {
        m_duration =sf:: milliseconds(0);


        if (sizeBar<100 || sizeBar > -100) sizeBar += size;

        if (vert)
        {
            barHelth.setSize(sf::Vector2f(25, sizeBar));
        }
        else
        {
            barHelth.setSize(sf::Vector2f(sizeBar, 25));
        }
    }

}

void HealthBarClass::setColorBar(sf::Color ColorHelth, sf::Color ColorContainer, float Thickness) 
{
    barHelth.setFillColor(ColorHelth);
    container.setOutlineColor(ColorContainer);
    container.setOutlineThickness(Thickness);
}

void HealthBarClass::reset() 
{
    sizeBar = 0.0f;
}