#pragma once

#ifndef _ALTERNATE_CLASSES_

#define _ALTERNATE_CLASSES_


#include <array_utils.hh>


template <typename T> class AlternateArray {
    private:
        T* values;
    public:
        AlternateArray(T* values) {
            this.values = values;
        }

        AlternateArray(int length) {
            this.values = (T*)malloc(length * sizeof(T));
        }

        T operator[](int i) {
            return values[i];
        }

        operator delete() {
            values = nullptr;
        }

        AlternateArray<T> operator+(AlternateArray<T> arr) {
            return AlternateArray<T>(merge<T>(arr.values, values));
        }

        AlternateArray<T> &operator+=(AlternateArray<T> arr) {
            values = merge<T>(arr.values, values);
            return this;
        }

        AlternateArray<T> operator+(T* arr) {
            return AlternateArray<T>(merge(arr, values))
        }

        AlternateArray<T> &operator+=(T* arr) {
            values = merge(arr, values);
            return this;
        }

        AlternateArray<T> operator+(T item) {
            T* x = { item };
            return AlternateArray<T>(merge(x, values));
        }

        AlternateArray<T> operator+=(T item) {
            T* x = { item }
            values = merge(x, values);
            return this;
        }
};


#endif // _ALTERNATE_CLASSES_