#pragma once

#ifndef _ARRAY_UTILS_

#define _ARRAY_UTILS_


#include <type_traits>
#include <cstdlib>


template <typename T> T* merge(T* arr1, T* arr2) {
    T* arr = (T*)malloc(sizeof(arr1) + sizeof(arr2)), t;
    int i;
    for(i = 0; (t = arr1[i]) != nullptr; i++)
        arr[i] = arr1[i];
    for(int j = i; (t = arr2[i - j]) != nullptr; i++)
        arr[i] = arr2[i - j];
    return arr;
}

template <typename T> T* subarr(T* array, int start = 0, int end = -1) {
    int l = 0;
    if(std::is_pointer(T)) {
        int so = sizeof(std::remove_pointer(T));
        T t;
        while((t = array[l++]) != nullptr);
    } else l = sizeof(array) / sizeof(T);
    if(start < 0) start += l;
    if(end < 0) end += l;
    if(start > end)
        return merge(subarr(array, start), subarr(array, 0, end));
    T* r = (T*)malloc((end - start) * sizeof(T));
    for(int i = start; i <= end; i++)
        r[i - start] = array[i];
    return r;
}

#endif // _ARRAY_UTILS_