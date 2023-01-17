#include "HealthBarClass.h"

void HealthBarClass::draw() 
{
	mywindow.draw(barHelth);
	mywindow.draw(container);	
}

void HealthBarClass::increaseOfsize(float size, sf::Time const& dt)
{
    if (!full) {
    m_duration += dt;

    if (m_duration > sf::milliseconds(20))
    {
        m_duration =sf:: milliseconds(0);

        if (vert)
        {
            if (sizeBar > -100) sizeBar += size*-1; else full = true;
            barHelth.setSize(sf::Vector2f(thicknessBar, sizeBar));
        }
        else
        {
            if (sizeBar < 100) sizeBar += size; else full = true;
            barHelth.setSize(sf::Vector2f(sizeBar, thicknessBar));
        }
    }
   }
}

void HealthBarClass::increaseOfsize(float size)
{
    if (!full) {
        if (vert)
        {
            if (sizeBar > -100) sizeBar += size * -1; else full = true;
            barHelth.setSize(sf::Vector2f(thicknessBar, sizeBar));
        }
        else
        {
            if (sizeBar < 100) sizeBar += size; else full = true;
            barHelth.setSize(sf::Vector2f(sizeBar, thicknessBar));
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
    full = false;
    barHelth.setSize(sf::Vector2f(sizeBar, thicknessBar));
}

void HealthBarClass::setSizeBar(float size)
{
    sizeBar = size;
    barHelth.setSize(sf::Vector2f(sizeBar, thicknessBar));
}
