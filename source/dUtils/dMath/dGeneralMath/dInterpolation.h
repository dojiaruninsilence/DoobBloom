#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

namespace doob {

    // class template for various interpolation methods
    template <typename Type>
    class dInterpolation {
    public:
        DInterpolation() {}
        ~DInterpolation() {}

        // linear interpolation
        // xValues: vector of x-coordinates
        // yValues: vector of y-coordinates
        // x: the x-coordinate for which to interpolate a value
        static Type linearInterpolation(
            const dVector<Type>& xValues, const dVector<Type>& yValues, Type x) {

            if (xValues.getSize() != yValues.getSize()) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Size mismatch between xValues and yValues.", __FILE__, __LINE__);
            }

            // find the two nearest data points in the xValues array
            size_t i = 0;
            while (i < xValues.getSize() && xValues[i] < x) {
                ++i;
            }

            // perform linear interpolation between the two nearest points
            if (i == 0) {
                // extrapolate using the first two points
                DB_INFO("Extrapolating using the first two points.");
                return yValues[0] + (yValues[1] - yValues[0]) * (x - xValues[0]) / (xValues[1] - xValues[0]);
            }
            else if (i == xValues.getSize()) {
                // extrapolate using the last two points
                DB_INFO("Extrapolating using the last two points.");
                return yValues[i - 2] + (yValues[i - 1] - yValues[i - 2]) * (x - xValues[i - 2]) / (xValues[i - 1] - xValues[i - 2]);
            }
            else {
                // interpolate between two points
                DB_INFO("Interpolating between points at indices {} and {}.", i - 1, i);
                return yValues[i - 1] + (yValues[i] - yValues[i - 1]) * (x - xValues[i - 1]) / (xValues[i] - xValues[i - 1]);
            }
        }

        // cubic interoplation
        // xValues: vector of x-coordinates
        // yValues: vector of y-coordinates
        // x: the x-coordinate for which to interpolate a value
        static Type cubicInterpolation(
            const dVector<Type>& xValues, const dVector<Type>& yValues, Type x) {

            if (xValues.getSize() != yValues.getSize()) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Size mismatch between xValues and yValues.", __FILE__, __LINE__);
            }

            // find the index of the nearest data point in the xValues array
            size_t i = 0;
            while (i < xValues.getSize() && xValues[i] < x) {
                ++i;
            }

            // perform cubic interpolation using neighboring points
            return cubicInterpolationHelper(xValues, yValues, x, i);
        }

    private:
        // helper funtions for cubic interpolation
        // xValues: vector of x-coordinates
        // yValues: vector of y-coordinates
        // x: the x-coordinate for which to interpolate a value
        // index: the index of the nearest data point in the xValues array
        static Type cubicInterpolationHelper(
            const dVector<Type>& xValues, const dVector<Type>& yValues, Type x, size_t index) {

            // ensure index is within bounds
            if (index < 1 || index >= xValues.getSize() - 2) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Index out of bounds for cubic interpolation.", __FILE__, __LINE__);
            }

            // define neighboring points
            Type x0 = xValues[index - 1];
            Type x1 = xValues[index];
            Type x2 = xValues[index + 1];
            Type x3 = xValues[index + 2];

            Type y0 = yValues[index - 1];
            Type y1 = yValues[index];
            Type y2 = yValues[index + 1];
            Type y3 = yValues[index + 2];

            // compute coefficients for cubic interpolation
            Type t = (x - x1) / (x2 - x1);
            Type t2 = t * t;
            Type t3 = t2 * t;

            Type c0 = y1;
            Type c1 = 0.5 * (y2 - y0);
            Type c2 = y0 - 2.5 * y1 + 2 * y2 - 0.5 * y3;
            Type c3 = 0.5 * (y3 - y0) + 1.5 * (y1 - y2);

            // perform cubic interpolation
            DB_INFO("Performing cubic interpolation at index {}.", index);
            return c0 + c1 * t + c2 * t2 + c3 * t3;
        }
    };
}