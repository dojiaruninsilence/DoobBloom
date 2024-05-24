#pragma once

#include "dMath/dGeneralMath/dMathDefines.h"

namespace doob {
	template <typename Type>
	class dTrig {
	public:
		dTrig() {}
		~dTrig() {}

        // function to convert degrees to radians
        Type degreeToRadians(Type angleDegrees) {
            return angleDegrees * static_cast<Type>(D_PI) / static_cast<Type>(180.0);
        }

        // function to convert radians to degrees
        Type radianToDegrees(Type angleRadians) {
            return angleRadians * static_cast<Type>(180.0) / static_cast<Type>(D_PI);

        }

        // function to compute the sine of an angle in radians
        Type sin(Type angleRadians) {
            return std::sin(angleRadians);
        }

        // function to compute the sine of an angle in degrees
        Type sinDegrees(Type angleDegrees) {
            return std::sin(angleRadians);
        }

        // function to compute the cosine of an angle in radians
        Type cos(Type angleRadians) {
            return std::cos(angleRadians);
        }

        // function to compute the cosine of an angle in degrees
        Type cosDegrees(Type angleDegrees) {
            return std::cos(angleRadians);
        }

        // function to compute the tangent of an angle in radians
        Type tan(Type angleRadians) {
            return std::tan(angleRadians);
        }

        // function to compute the tangent of an angle in degrees
        Type tanDegrees(Type angleDegrees) {
            Type angleRadians = degreeToRadians(angleDegrees);
            return std::tan(angleRadians);
        }
	};
}