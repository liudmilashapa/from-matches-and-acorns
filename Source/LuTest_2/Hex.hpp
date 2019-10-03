#pragma once

#include "Coordinate.hpp"


class Hex
{

private:

    Coordinate  m_2dCoorditates;
    Coordinate  m_logicCoordinate;


    const float innerRadius = 20.0;

    const float outerRadius = innerRadius / 0.866025404f;


public:

    Hex(int _x, int _y)
    {
        m_2dCoorditates = Coordinate(_x, _y, 0);
        setAxialCoordinates();
    }

    
    void setAxialCoordinates();

    Coordinate * Get2DCoordinates();

    Coordinate * GetLogicCoordinates();

 };