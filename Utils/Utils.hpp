#pragma once
namespace Utils {

    template <class T>
    void swap(T *a, T *b) {
        T a_temp = *a;
        *a = *b;
        *b = a_temp;
    }
    template <class T>
    T max(T a, T b) {
        if (a > b)
            return a;
        return b;
    }
    template <class T>
    T min(T a, T b) {
        if (a < b)
            return a;
        return b;
    }
}