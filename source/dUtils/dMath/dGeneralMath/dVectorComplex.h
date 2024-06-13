#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include <vector>
#include <complex>

namespace doob {

    // @class dVectorComplex
    // @brief a dynamic array class for storing complex numbers.
    // @tparam type The type of elements in the complex numbers.
    template <typename Type>
    class dVectorComplex {
    public:
        // constuctor/destuctor
        dVectorComplex() {}
        ~dVectorComplex() {}

        // @brief add a complex number to the vector.
        // @param value the complex number to add.
        void push_back(const std::complex<Type>& value) {
            //value = static_cast<std::complex<float>>(value);
            data.push_back(value);
        }

        // @brief add an array of complex numbers to the vector.
        // @param values pointer to the array of complex numbers.
        // @param numValues number of complex numbers in the array.
        void push_back(const std::complex<Type>* values, size_t numValues) {
            for (size_t i = 0; i < numValues; ++i) {
                push_back(values[i]);
            }
        }

        // @brief add the elements of another dVectorComplex to this vector.
        // @param otherVector the other dVectorComplex to add elements from.
        void push_back(const DVectorComplex<std::complex<Type>>& otherVector) {
            for (size_t i = 0; i < otherVector.getSize(); ++i) {
                push_back(otherVector[i]);
            }
        }

        // @brief get the number of elements in the vector.
        // @return the number of elements in the vector.
        size_t getSize() const { return data.size(); }

        // @brief access a complex number by index.
        // @param index the index of the complex number.
        // @return a reference to the complex number.
        std::complex<Type>& operator[](size_t index) { 

            if (index >= data.size()) {
                reportError(errorLevel::D_ERROR, errorCode::OUT_OF_BOUNDS, "Index out of bounds.", __FILE__, __LINE__);
            }

            return data[index]; 
        }

        // @brief access a complex number by index (const version).
        // @param index the index of the complex number.
        // @return a const reference to the complex number.
        const std::complex<Type>& operator[](size_t index) const { 

            if (index >= data.size()) {
                reportError(errorLevel::D_ERROR, errorCode::OUT_OF_BOUNDS, "Index out of bounds.", __FILE__, __LINE__);
            }

            return data[index]; 
        }
    private:
        std::vector<std::complex<Type>> data; ///< the underlying container for storing complex numbers.
    };
}