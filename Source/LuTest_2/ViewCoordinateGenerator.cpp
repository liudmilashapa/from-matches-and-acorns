
#include "ViewCoordinateGenerator.hpp"



FVector ViewCoordinateGenerator::generateViewCoordinate(Coordinate & _2DCoordinate, FVector & StartPoint)
{
        /*  float x = outerRadius * (3 * _x +1.5*(_y % 2));
          float y = innerRadius * _y;
          float z = 0;*/
        float x = outerRadius * (1.5*_2DCoordinate.GetY() + StartPoint.X);
        float y = innerRadius * (2 * _2DCoordinate.GetX() + _2DCoordinate.GetY() % 2 + StartPoint.Y);
        float z = StartPoint.Z;

        return FVector(x, y, z);
}


const float ViewCoordinateGenerator::innerRadius(20.0);

const float ViewCoordinateGenerator::outerRadius(innerRadius / 0.866025404f);
