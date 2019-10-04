#include "Coordinate.hpp"

Coordinate::Coordinate(int _x, int _y, int _z)
{
    m_x = _x;
    m_y = _y;
    m_z = _z;
    m_vectorCoordinate = FVector(_x, _y, _z);
}

Coordinate::Coordinate( FVector & vector)
{
    m_x = vector.X;
    m_y = vector.Y;
    m_z = vector.Z;
    m_vectorCoordinate = vector;
}

bool Coordinate::IsEqual(Coordinate _coordinate1) const
{
    return (_coordinate1.GetX() == m_x && _coordinate1.GetY() == m_y && _coordinate1.GetZ() == m_z);
}

int Coordinate::GetX()
{
    return m_x;
}

int Coordinate::GetY()
{
    return m_y;
}

int Coordinate::GetZ()
{
    return m_z;
}

void Coordinate::SetX(int x)
{
    m_x = x;
}

void Coordinate::SetY(int y)
{
    m_y = y;

}

void Coordinate::SetZ(int z)
{
    m_z = z;
}

FVector & Coordinate::GetFVector() 
{
    return m_vectorCoordinate;
}

bool Coordinate::operator == (Coordinate & _coordinate)
{
    return (m_x == _coordinate.GetX() && m_y == _coordinate.GetY() && m_z == _coordinate.GetZ());
}
