#pragma once

#include "dUtils/dMath/dGeneralMath/dSqrRtAbsFunctions.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"

#include <algorithm>

namespace doob {
    template <typename Type>
    class dStats {
    public:
        // function to calculate the mean of a vector
        static Type mean(const dVector<Type>& vector) {
            Type sum = 0;
            for (size_t i = 0; i < vector.getSize(); ++i) {
                sum += vector[i];
            }
            return sum / vector.getSize();
        }

        // function to calculate the standard deviation of a vector
        static Type standardDeviation(const dVector<Type>& vector) {
            Type meanValue = mean(vector);
            Type sum = 0;
            for (size_t i = 0; i < vector.getSize(); ++i) {
                sum += (vector[i] - meanValue) * (vector[i] - meanValue);
            }
            return dSqrRtAbsFunctions<Type>::sqrt(sum / vector.getSize());
        }

        // function to calculate the variance of a vector
        static Type variance(const dVector<Type>& vector) {
            Type meanValue = mean(vector);
            Type sum = 0;
            for (size_t i = 0; i < vector.getSize(); ++i) {
                sum += (vector[i] - meanValue) * (vector[i] - meanValue);
            }
            return sum / vector.getSize();
        }

        // function to calculate the median of a vector
        static Type median(const dVector<Type>& vector) {
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

        // function to calculate the modes of a verctor
        static dVector<Type> mode(const dVector<Type>& vector) {
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

        // function to calculate the range of a vector
        static Type range(const dVector<Type>& vector) {
            if (vector.getSize() == 0) {
                return Type();
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