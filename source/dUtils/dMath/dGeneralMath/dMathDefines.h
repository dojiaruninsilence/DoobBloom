#pragma once

#define D_PI 3.14159265358979323846
#define D_TWO_PI (2.0 * D_PI)
#define D_HALF_PI (D_PI / 2.0)
#define D_QUARTER_PI (D_PI / 4.0)
#define D_E 2.71828182845904523536
#define D_LOG2E 1.44269504088896340736
#define D_LOG10E 0.434294481903251827651
#define D_LN2 0.693147180559945309417
#define D_LN10 2.30258509299404568402
#define D_SQRT2 1.41421356237309504880
#define D_SQRT1_2 0.707106781186547524401
#define D_SQRT3 1.73205080756887729352
#define D_INV_PI 0.318309886183790671538
#define D_INV_TWO_PI 0.159154943091895335769
#define D_DEG_TO_RAD (D_PI / 180.0)
#define D_RAD_TO_DEG (180.0 / D_PI)

// Some common mathematical functions as inline functions for convenience
inline double degreesToRadians(double degrees) {
    return degrees * D_DEG_TO_RAD;
}

inline double radiansToDegrees(double radians) {
    return radians * D_RAD_TO_DEG;
}

inline double square(double x) {
    return x * x;
}

inline double cube(double x) {
    return x * x * x;
}

inline double clamp(double x, double lower, double upper) {
    return (x < lower) ? lower : (x > upper) ? upper : x;
}

inline double lerp(double a, double b, double t) {
    return a + t * (b - a);
}