#pragma once

#include <vector>
#include <complex>

namespace doob {
    template <typename Type>
    class dVectorComplex {
    public:
        // constuctor/destuctor
        dVectorComplex() {}
        ~dVectorComplex() {}

        // add a complex number to the vector
        void push_back(const std::complex<Type>& value) {
            //value = static_cast<std::complex<float>>(value);
            data.push_back(value);
        }

        void push_back(const std::complex<Type>* values, size_t numValues) {
            for (size_t i = 0; i < numValues; ++i) {
                push_back(values[i]);
            }
        }

        void push_back(const DVectorComplex<std::complex<Type>>& otherVector) {
            for (size_t i = 0; i < otherVector.getSize(); ++i) {
                push_back(otherVector[i]);
            }
        }

        // get the number of elements in the vector
        size_t getSize() const { return data.size(); }

        // access a complex number by index
        std::complex<Type>& operator[](size_t index) { return data[index]; }
        const std::complex<Type>& operator[](size_t index) const { return data[index]; }
    private:
        std::vector<std::complex<Type>> data;
    };
}