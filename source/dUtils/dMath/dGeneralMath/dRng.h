#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"
#include "dUtils/dDiagnostics/dAssert.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

#include <random>

namespace doob {

    // random Number Generator class
    template <typename Type>
    class DRng {
    public:
        // constructor
        DRng() : rng(std::random_device{}()) {
            DB_INFO("DRng initialized with random seed");
        }

        // destuctor
        ~DRng() {}

        // generate a random value between min (inclusive and max(exclusive)
        Type next(Type min, Type max) {

            // validate input range
            if (min > max) {
                DB_WARN("next called with min > max, swapping values: min={}, max={}", min, max);
                std::swap(min, max);
            }

            if (std::is_same<Type, int>{}) {
                min = static_cast<float>(min);
                max = static_cast<float>(max);
                std::uniform_real_distribution<float> dist(min, max);
                int result = static_cast<int>(dist(rng));
                return result;
            }
            else if (std::is_same<Type, float>{}) {
                std::uniform_real_distribution<float> dist(min, max);
                return dist(rng);
            }
            else if (std::is_same<Type, double>{}) {
                std::uniform_real_distribution<double> dist(min, max);
                return dist(rng);
            }
            else if (std::is_same<Type, long double>{}) {
                std::uniform_real_distribution<long double> dist(min, max);
                return dist(rng);
            }
            else {
                reportError(errorLevel::D_ERROR, errorCode::RUNTIME_ERROR,
                    "Unsupported type for random generation.", __FILE__, __LINE__);
                return 0;
            }
        }

        // generate a random value following a gaussian(normal) distribution
        Type nextGaussian(Type mean, Type stddev) {
            if (std::is_same<Type, int>{}) {
                mean = static_cast<float>(mean);
                stddev = static_cast<float>(stddev);
                std::normal_distribution<float> dist(mean, stddev);
                int result = static_cast<int>(dist(rng));
                return result;
            }
            else if (std::is_same<Type, float>{}) {
                std::normal_distribution<float> dist(mean, stddev);
                return dist(rng);
            }
            else if (std::is_same<Type, double>{}) {
                std::normal_distribution<double> dist(mean, stddev);
                return dist(rng);
            }
            else if (std::is_same<Type, long double>{}) {
                std::normal_distribution<long double> dist(mean, stddev);
                return dist(rng);
            }
            else {
                reportError(errorLevel::D_ERROR, errorCode::RUNTIME_ERROR,
                    "Unsupported type for random generation.", __FILE__, __LINE__);
                return 0;
            }
        }

        // return a random element from the given collection
        Type nextElement(const dVector<Type>& collection) {
            D_ASSERT(collection.getSize() > 0, "Collection cannot be empty");

            if (collection.getSize() == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "nextElement called with an empty collection.", __FILE__, __LINE__);
            }

            std::uniform_int_distribution<size_t> dist(0, collection.getSize() - 1);
            return collection[dist(rng)];
        }

        void setSeed(Type seed) {
            DB_INFO("Random number generator seed set to: {}", seed);
            rng.seed(seed);
        }
    private:
        std::mt19937 rng;
    };
}