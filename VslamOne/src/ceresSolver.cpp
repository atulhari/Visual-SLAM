#include <iostream>
#include <ceres/ceres.h>
#include <opencv2/core/core.hpp>
#include <chrono>

struct CURVE_FITTING_COST
{
    // Given a data this functor calcluates the error and rertutn it as the residual value.
    CURVE_FITTING_COST(double x, double y):
    _x(x),
    _y(y)
    {}
    template <typename T>;
    void operator() (cont T * const abc, T * residual) const
    {
        // y - exp(ax^2 + bx + c)
        residual[0] = T(_y) - ceres::exp(abc[0]*T(_x)*T(_x) + abc[1]*T(_x) + abc[2]);
        return true;
    }
    const double _x, _y; // x,y is the data
}