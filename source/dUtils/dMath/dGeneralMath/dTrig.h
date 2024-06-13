#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include "dMath/dGeneralMath/dMathDefines.h"

namespace doob {

    // @class dTrig
    // @brief Trigonometric functions for angles.
    // This class provides static methods to compute trigonometric functions such as sine, cosine, tangent,
    // and their inverse counterparts for both radians and degrees.
    // @tparam Type The type of angles(float, double, etc.).
	template <typename Type>
	class dTrig {
	public:
		dTrig() {}
		~dTrig() {}

        // @brief Convert degrees to radians.
        // @param angleDegrees The angle in degrees.
        // @return The angle converted to radians.
        static Type degreeToRadians(Type angleDegrees) {
            return angleDegrees * static_cast<Type>(D_PI) / static_cast<Type>(180.0);
        }

        // @brief Convert radians to degrees.
        // @param angleRadians The angle in radians.
        // @return The angle converted to degrees.
        static Type radianToDegrees(Type angleRadians) {
            return angleRadians * static_cast<Type>(180.0) / static_cast<Type>(D_PI);

        }

        // @brief Compute the sine of an angle in radians.
        // @param angleRadians The angle in radians.
        // @return The sine of the angle.
        static Type sin(Type angleRadians) {
            return std::sin(angleRadians);
        }

        // @brief Compute the sine of an angle in degrees.        
        // @param angleDegrees The angle in degrees.
        // @return The sine of the angle.
        static Type sinDegrees(Type angleDegrees) {
            return std::sin(degreeToRadians(angleDegrees));
        }

        // @brief Compute the arc sine (inverse sine) of an angle in radians.
        // @param angleRadians The angle in radians.
        // @return The arc sine of the angle.
        static Type asin(Type angleRadians) {

            if (angleRadians < -1 || angleRadians > 1) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Invalid input for asin function: angle must be within [-1, 1].",
                    __FILE__, __LINE__);
            }

            return std::asin(angleRadians);
        }

        // @brief Compute the arc sine (inverse sine) of an angle in degrees.
        // @param angleDegrees The angle in degrees.
        // @return The arc sine of the angle.
        static Type asinDegrees(Type angleDegrees) {
            return std::asin(degreeToRadians(angleDegrees));
        }

        // @brief Compute the cosine of an angle in radians.
        // @param angleRadians The angle in radians.
        // @return The cosine of the angle.
        static Type cos(Type angleRadians) {
            return std::cos(angleRadians);
        }

        // @brief Compute the cosine of an angle in degrees.
        // @param angleDegrees The angle in degrees.
        // @return The cosine of the angle.
        static Type cosDegrees(Type angleDegrees) {
            return std::cos(degreeToRadians(angleDegrees));
        }

        // @brief Compute the tangent of an angle in radians.
        // @param angleRadians The angle in radians.
        // @return The tangent of the angle.
        static Type tan(Type angleRadians) {
            return std::tan(angleRadians);
        }

        // @brief Compute the tangent of an angle in degrees.
        // @param angleDegrees The angle in degrees.
        // @return The tangent of the angle.
        static Type tanDegrees(Type angleDegrees) {
            return std::tan(degreeToRadians(angleDegrees));
        }

        // @brief Compute the arc tangent (inverse tangent) of an angle in radians.
        // @param angleRadians The angle in radians.
        // @return The arc tangent of the angle.
        static Type atan(Type angleRadians) {
            return std::atan(angleRadians);
        }

        // @brief Compute the arc tangent (inverse tangent) of an angle in degrees.
        // @param angleDegrees The angle in degrees.
        // @return The arc tangent of the angle.
        static Type atanDegrees(Type angleDegrees) {
            return std::atan(degreeToRadians(angleDegrees));
        }
	};
}