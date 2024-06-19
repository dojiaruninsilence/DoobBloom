#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include <memory>
#include <algorithm>

namespace doob {

    // @class dVec2
    // @brief A 2D vector class.
    // @tparam Type The type of elements in the vector.
    template <typename Type>
    class dVec2 {
    public:
        Type x, y;

        dVec2(Type x = Type(), Type y = Type()) : x(x), y(y) {}
    };

    // @class dVec3
    // @brief A 3D vector class.
    // @tparam Type The type of elements in the vector.
    template <typename Type>
    class dVec3 {
    public:
        Type x, y, z;

        dVec3(Type x = Type(), Type y = Type(), Type z = Type()) : x(x), y(y), z(z) {}
    };

    // @class dVec4
    // @brief A 4D vector class.
    // @tparam Type The type of elements in the vector.
    template <typename Type>
    class dVec4 {
    public:
        Type x, y, z, w;

        dVec4(Type x = Type(), Type y = Type(), Type z = Type(), Type w = Type()) : x(x), y(y), z(z), w(w) {}
    };

    // @class dVector
    // @brief A dynamic array class.
    // @tparam Type The type of elements in the vector.
    template <typename Type>
    class dVector {

    public:
        // iterator types
        using iterator = Type*;
        using const_iterator = const Type*;

        // default constructor
        dVector() : m_data(nullptr), size(0), capacity(0) {}

        // size constructor
        dVector(size_t initialSize) : size(initialSize), capacity(initialSize) {
            m_data = new Type[capacity];
        }

        // destructor
        ~dVector() { delete[] m_data; }

        // move constructor
        dVector(dVector&& other) noexcept {
            size = other.size;
            capacity = other.capacity;
            m_data = other.m_data;
            other.size = 0;
            other.capacity = 0;
            other.m_data = nullptr;
        }

        // move assignment operator
        dVector& operator=(dVector&& other) noexcept {
            if (this != &other) {
                delete[] m_data;
                size = other.size;
                capacity = other.capacity;
                m_data = other.m_data;
                other.size = 0;
                other.capacity = 0;
                other.m_data = nullptr;
            }
            return *this;
        }

        // method to add an element to the end of the vector
        void push_back(Type&& value) {
            if (size >= capacity) {
                reserve(capacity == 0 ? 1 : capacity * 2);
            }
            m_data[size++] = std::move(value);
        }

        void push_back(const Type& value) {
            if (size >= capacity) {
                reserve(capacity == 0 ? 1 : capacity * 2);
            }
            m_data[size++] = value;
        }

        void push_back(const Type* values, size_t numValues) {
            for (size_t i = 0; i < numValues; ++i) {
                push_back(values[i]);
            }
        }

        void push_back(const dVector<Type>& otherVector) {
            for (size_t i = 0; i < otherVector.getSize(); ++i) {
                push_back(std::move(otherVector[i]));
            }
        }

        // method to reserve space for a certain number of elements
        void reserve(size_t newCapacity) {
            if (newCapacity > capacity) {
                Type* newData = new Type[newCapacity];
                for (size_t i = 0; i < size; ++i) {
                    newData[i] = std::move(m_data[i]);
                }
                delete[] m_data;
                m_data = newData;
                capacity = newCapacity;
            }
        }

        // method to get the number of elements in the vector
        size_t getSize() const { return size; }

        // method to find the minimum and maximum values in the vector
        Type min() const {
            if (size == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR, "Vector size is zero.", __FILE__, __LINE__);
                return Type();
            }
            Type minValue = m_data[0];
            for (size_t i = 1; i < size; ++i) {
                if (m_data[i] < minValue) {
                    minValue = m_data[i];
                }
            }
            return minValue;
        }

        Type max() const {
            if (size == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR, "Vector size is zero.", __FILE__, __LINE__);
                return Type();
            }
            Type maxValue = m_data[0];
            for (size_t i = 1; i < size; ++i) {
                if (m_data[i] > maxValue) {
                    maxValue = m_data[i];
                }
            }
            return maxValue;
        }

        // Returns an iterator to the beginning of the container
        iterator begin() { return m_data; }
        const_iterator begin() const { return m_data; }

        // Returns an iterator to the end of the container
        iterator end() { return m_data + size; }
        const_iterator end() const { return m_data + size; }

        // method to access the underlying array
        Type* data() { return m_data; }
        const Type* data() const { return m_data; }

        // method to resize the vector
        void resize(size_t newSize) {
            if (newSize <= size) {
                size = newSize;
            }
            else {
                reserve(newSize);
                size = newSize;
            }
        }

        void resize(size_t newSize, const Type& value) {
            if (newSize <= size) {
                size = newSize;
            }
            else {
                reserve(newSize);
                for (size_t i = size; i < newSize; ++i) {
                    m_data[i] = value;
                }
                size = newSize;
            }
        }

        // Method to clear the vector
        void clear() {
            // Free the memory and reset size to 0
            delete[] elements;
            elements = nullptr;
            size = 0;
            capacity = 0;
        }

        dVector<Type> subVector(size_t start, size_t end) const {
            start = std::min(start, size);
            end = std::min(end, size);

            DVector<Type> subvec;
            size_t subvecSize = end - start;
            subvec.reserve(subvecSize);

            for (size_t i = start; i < end; ++i) {
                subvec.push_back(m_data[i]);
            }

            return subvec;
        }

        dVector<Type> subVector(size_t start) const { return subVector(start, size); }

        // method to set a sub-vector from another vector
        void setSubVector(size_t startIndex, const dVector<Type>& otherVector) {
            size_t otherSize = otherVector.getSize();
            if (startIndex + otherSize > size) {
                reserve(startIndex + otherSize);
                size = startIndex + otherSize;
            }
            for (size_t i = 0; i < otherSize; ++i) {
                m_data[startIndex + i] = otherVector[i];
            }
        }

        // method to access elements by index
        Type& operator[](size_t index) { return m_data[index]; }
        const Type& operator[](size_t index) const { return m_data[index]; }

        // method to erase an element by index
        void erase(size_t index) {
            if (index < size) {
                for (size_t i = index; i < size - 1; ++i) {
                    m_data[i] = std::move(m_data[i + 1]);
                }
                --size;
            }
        }

    private:
        Type* m_data; // Pointer to the dynamic array holding the elements
        size_t size; // Number of elements in the vector
        size_t capacity; // Capacity of the dynamic array
    };
}
