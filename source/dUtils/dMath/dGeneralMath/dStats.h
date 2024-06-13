#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include "dUtils/dMath/dGeneralMath/dSqrRtAbsFunctions.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"

#include <algorithm>

namespace doob {

    
    // @class dStats
    // @brief statistical functions for vectors.    
    // this class provides static methods to calculate various statistical measures such as mean,
    // standard deviation, variance, median, mode, and range for vectors.
    // @tparam Type The type of elements in the vector.
    template <typename Type>
    class dStats {
    public:

        // @brief calculate the mean of a vector. 
        // @param vector The input vector.
        // @return the mean of the vector.
        static Type mean(const dVector<Type>& vector) {

            if (vector.getSize() == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Vector size is zero.", __FILE__, __LINE__);
            }

            Type sum = 0;
            for (size_t i = 0; i < vector.getSize(); ++i) {
                sum += vector[i];
            }
            return sum / vector.getSize();
        }

        // @brief calculate the standard deviation of a vector.
        // @param vector The input vector.
        // @return the standard deviation of the vector.
        static Type standardDeviation(const dVector<Type>& vector) {

            if (vector.getSize() == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Vector size is zero.", __FILE__, __LINE__);
            }

            Type meanValue = mean(vector);
            Type sum = 0;
            for (size_t i = 0; i < vector.getSize(); ++i) {
                sum += (vector[i] - meanValue) * (vector[i] - meanValue);
            }
            return dSqrRtAbsFunctions<Type>::sqrt(sum / vector.getSize());
        }

        // @brief calculate the variance of a vector.
        // @param vector The input vector.
        // @return the variance of the vector.
        static Type variance(const dVector<Type>& vector) {

            if (vector.getSize() == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Vector size is zero.", __FILE__, __LINE__);
            }

            Type meanValue = mean(vector);
            Type sum = 0;
            for (size_t i = 0; i < vector.getSize(); ++i) {
                sum += (vector[i] - meanValue) * (vector[i] - meanValue);
            }
            return sum / vector.getSize();
        }

        // @brief calculate the median of a vector.        
        // @param vector The input vector.
        // @return the median of the vector.
        static Type median(const dVector<Type>& vector) {

            if (vector.getSize() == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Vector size is zero.", __FILE__, __LINE__);
            }

            dVector<Type> sortedVector = vector;
            std::sort(sortedVector.data, sortedVector.data + sortedVector.size);

            if (sortedVector.size % 2 == 0) {
                size_t middleIndex1 = sortedVector.size / 2 - 1;
                size_t middleIndex2 = middleIndex1 + 1;
                return (sortedVector[middleIndex1] + sortedVector[middleIndex2]) / static_cast<Type>(2);
            }
            else {
                size_t middleIndex = sortedVector.size / 2;
                return sortedVector[middleIndex];
            }
        }

        // @brief calculate the modes of a vector.        
        // @param vector The input vector.
        // @return a vector containing the mode(s) of the input vector.
        static dVector<Type> mode(const dVector<Type>& vector) {

            if (vector.getSize() == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Vector size is zero.", __FILE__, __LINE__);
            }

            std::unordered_map<Type, size_t> frequencyMap;

            for (size_t i = 0; i < vector.getSize(); ++i) {
                frequencyMap[vector[i]]++;
            }

            size_t maxFrequency = 0;
            for (const auto& pair : frequencyMap) {
                maxFrequency = std::max(maxFrequency, pair.second);
            }

            dVector<Type> modes;
            for (const auto& pair : frequencyMap) {
                if (pair.second == maxFrequency) {
                    modes.push_back(pair.first);
                }
            }

            return modes;
        }

        // @brief calculate the range of a vector.
        // @param vector The input vector.
        // @return the range of the vector.
        static Type range(const dVector<Type>& vector) {

            if (vector.getSize() == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Vector size is zero.", __FILE__, __LINE__);
            }

            Type minVal = vector[0];
            Type maxVal = vector[0];

            for (size_t i = 1; i < vector.getSize(); ++i) {
                minVal = std::min(minVal, vector[i]);
                maxVal = std::max(maxVal, vector[i]);
            }

            return maxVal - minVal;
        }
    };
}