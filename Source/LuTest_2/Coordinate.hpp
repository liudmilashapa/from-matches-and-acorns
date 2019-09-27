#pragma once


class Coordinate
{
private:

    int m_x;
    int m_y;
    int m_z;

public:


    Coordinate() {};

    Coordinate(int _x, int _y, int _z);

    bool IsEqual(Coordinate _coordinate1) const;

    int GetX();
    int GetY();
    int GetZ();

    void SetX(int x);
    void SetY(int y);
    void SetZ(int z);

    FVector ToFVector() const;
};
