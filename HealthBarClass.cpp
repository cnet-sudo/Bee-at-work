#include "HealthBarClass.h"

void HealthBarClass::draw() 
{
	mywindow.draw(barHelth);
	mywindow.draw(container);	
}

void HealthBarClass::changeOfbar(double size, sf::Time const& dt)
{
    
    m_duration += dt;

    if (m_duration > sf::milliseconds(20))
    {
        m_duration =sf:: milliseconds(0);
        sizeBar += size;
        if (vert)
        {
            if (size > 0)
            {
                if (sizeBar >= 100) { sizeBar = 100; full = true; }
                barHelth.setOrigin(0, sizeBar * divisionUnit);
                barHelth.setSize(sf::Vector2f(thicknessBar, sizeBar * divisionUnit));
            }
            else
            {
                if (sizeBar <= 0) { empty = true; sizeBar = 0; }
                barHelth.setOrigin(0, sizeBar * divisionUnit);
                barHelth.setSize(sf::Vector2f(thicknessBar, sizeBar * divisionUnit));
            }
        }
        else
        {
            if (size > 0)
            {
                if (sizeBar >= 100) { sizeBar = 100; full = true; }
                barHelth.setSize(sf::Vector2f(sizeBar * divisionUnit,thicknessBar));
            }
            else
            {
                if (sizeBar <= 0) { empty = true; sizeBar = 0; }
                barHelth.setSize(sf::Vector2f(sizeBar * divisionUnit,thicknessBar ));
            }
        }
    
   }
}

void HealthBarClass::changeOfbar(double size)
{   
    sizeBar += size;
    if (vert)
    {   
        if (size > 0)
        {    
            if (sizeBar >= 100) { sizeBar = 100; full = true; } 
            barHelth.setOrigin(0, sizeBar * divisionUnit);
            barHelth.setSize(sf::Vector2f(thicknessBar, sizeBar * divisionUnit));
        }
        else
        {
            if (sizeBar <= 0) {empty = true; sizeBar = 0;}
            barHelth.setOrigin(0, sizeBar * divisionUnit);
            barHelth.setSize(sf::Vector2f(thicknessBar, sizeBar * divisionUnit));
        }
    }
    else
    {
        if (size > 0)
        {
            if (sizeBar >= 100) { sizeBar = 100; full = true; }
            barHelth.setSize(sf::Vector2f(sizeBar * divisionUnit, thicknessBar));
        }
        else
        {
            if (sizeBar <= 0) { empty = true; sizeBar = 0; }
            barHelth.setSize(sf::Vector2f(sizeBar * divisionUnit, thicknessBar));
        }
    }

}

void HealthBarClass::setColorBar(sf::Color ColorHelth, sf::Color ColorContainer, float Thickness) 
{
    this->ColorHelth = ColorHelth;
    barHelth.setFillColor(ColorHelth);
    container.setOutlineColor(ColorContainer);
    container.setOutlineThickness(Thickness);
}



void HealthBarClass::reset() 
{
    sizeBar = resetBar;
    if (resetBar==100) full = true; else full = false;
    if (resetBar == 0) empty = true; else empty = false;
    if (vert)
    {
        barHelth.setOrigin(0, sizeBar* divisionUnit);
        barHelth.setSize(sf::Vector2f(thicknessBar, sizeBar* divisionUnit));
    }
    else
    {
        barHelth.setSize(sf::Vector2f(sizeBar* divisionUnit, thicknessBar));
    }
}

void HealthBarClass::setSizeBar(float size)
{
    sizeBar = size;
    if (sizeBar == 0)  empty = true;
    if (vert)
    {
        barHelth.setOrigin(0, sizeBar* divisionUnit);
        barHelth.setSize(sf::Vector2f(thicknessBar, sizeBar* divisionUnit));
    }
    else
    {
        barHelth.setSize(sf::Vector2f(sizeBar* divisionUnit,thicknessBar));
    }
}
