#pragma once

#include "dUtils/dMath/dGeneralMath/dVector.h"

#include <random>

namespace doob {
    template <typename Type>
    class DRng {
    public:
        // constructor/destuctor
        DRng() : rng(std::random_device{}()) {}
        ~DRng() {}

        // generate a random value between min (inclusive and max(exclusive)
        Type next(Type min, Type max) {
            if (min > max) {
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
                return 0;
            }
        }

        // return a random element from the given collection
        Type nextElement(const dVector<Type>& collection) {
            if (collection.getSize() == 0) {
                throw std::out_of_range("Empty collection");
            }

            std::uniform_int_distribution<size_t> dist(0, collection.getSize() - 1);
            return collection[dist(rng)];
        }

        void setSeed(Type seed) {
            rng.seed(seed);
        }
    private:
        std::mt19937 rng;
    };
}