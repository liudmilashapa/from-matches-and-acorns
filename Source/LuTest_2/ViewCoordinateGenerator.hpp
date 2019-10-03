#pragma once

#include "CoreMinimal.h"
#include "TransformCoordinate.hpp"
#include "Coordinate.hpp"
#include <vector>
#include <random>
#include <stdint.h>
#include <time.h>



class ViewCoordinateGenerator
{

public:

    static const float innerRadius;

    static const float outerRadius;// = innerRadius / 0.866025404f;

public:

    FVector generateViewCoordinate(Coordinate & _2DCoordinate, FVector & StartPoint);
};