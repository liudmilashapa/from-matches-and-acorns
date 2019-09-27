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

private:

    const float innerRadius = 20.0;

    const float outerRadius = innerRadius / 0.866025404f;

public:

    FVector generateViewCoordinate(Coordinate & _2DCoordinate, FVector & StartPoint);
};