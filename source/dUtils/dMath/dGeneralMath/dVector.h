#pragma once

namespace dMath {
    template <typename Type>
    class dVec2 {
    public:
        Type x, y;

        dVec2(Type x = Type(), Type y = Type()) : x(x), y(y) {}
    };

    template <typename Type>
    class dVec3 {
    public:
        Type x, y, z;

        dVec3(Type x = Type(), Type y = Type(), Type z = Type()) : x(x), y(y), z(z) {}
    };

    template <typename Type>
    class dVec4 {
    public:
        Type x, y, z, w;

        dVec4(Type x = Type(), Type y = Type(), Type z = Type(), Type w = Type()) : x(x), y(y), z(z), w(w) {}
    };

    template <typename Type>
    class dVector {

    public:
        // iterator types
        using iterator = Type*;
        using const_iterator = const Type*;

        // constructor
        dVector() : data(nullptr), size(0), capacity(0) {}

        // destructor
        ~dVector() { delete[] data; }

        // method to add an element to the end of the vector
        void push_back(const Type& value) {
            if (size >= capacity) {
                reserve(capacity == 0 ? 1 : capacity * 2);
            }
            data[size++] = value;
        }

        void push_back(const Type* values, size_t numValues) {
            for (size_t i = 0; i < numValues; ++i) {
                push_back(values[i]);
            }
        }

        void push_back(const dVector<Type>& otherVector) {
            for (size_t i = 0; i < otherVector.getSize(); ++i) {
                push_back(otherVector[i]);
            }
        }

        // method to reserve space for a certain number of elements
        void reserve(size_t newCapacity) {
            if (newCapacity > capacity) {
                Type* newData = new Type[newCapacity];
                for (size_t i = 0; i < size; ++i) {
                    newData[i] = data[i];
                }
                delete[] data;
                data = newData;
                capacity = newCapacity;
            }
        }

        // method to get the number of elements in the vector
        size_t getSize() const { return size; }

        // method to find the minimum and maximum values in the vector
        Type min() const {
            if (size == 0) {
                return 0;
            }
            Type minValue = data[0];
            for (size_t i = 1; i < size; ++i) {
                if (data[i] < minValue) {
                    minValue = data[i];
                }
            }
            return minValue;
        }

        Type max() const {
            if (size == 0) {
                return 0;
            }
            Type maxValue = data[0];
            for (size_t i = 1; i < size; ++i) {
                if (data[i] > maxValue) {
                    maxValue = data[i];
                }
            }
            return maxValue;
        }

        // Returns an iterator to the beginning of the container
        iterator begin() { return data; }
        const_iterator begin() const { return data; }

        // Returns an iterator to the end of the container
        iterator end() { return data + size; }
        const_iterator end() const { return data + size; }

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
                    data[i] = value;
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
                subvec.push_back(data[i]);
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
                data[startIndex + i] = otherVector[i];
            }
        }

        // method to access elements by index
        Type& operator[](size_t index) { return data[index]; }
        const Type& operator[](size_t index) const { return data[index]; }

    private:
        Type* data; // Pointer to the dynamic array holding the elements
        size_t size; // Number of elements in the vector
        size_t capacity; // Capacity of the dynamic array
    };
}