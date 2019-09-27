#include"Hex.hpp"

void Hex::setAxialCoordinates()
{
    m_logicCoordinate.SetX( m_2dCoorditates.GetX() - (m_2dCoorditates.GetY())/ 2);
    m_logicCoordinate.SetY(m_2dCoorditates.GetY());
    /* FVector _vector = getOffsetCoordinates(_x, _y, z_, Maxcount);
    float x = _vector.Component(0) - _vector.Component(1) % 2;*/
    m_logicCoordinate.SetZ(- m_logicCoordinate.GetX() - m_logicCoordinate.GetY());
}

Coordinate  Hex::Get2DCoordinates()
{
    return m_2dCoorditates;
}

Coordinate Hex::GetLogicCoordinates()
{
    return m_logicCoordinate;
}

