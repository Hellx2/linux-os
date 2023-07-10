#pragma once

#ifndef _STRING_UTILS_

#define _STRING_UTILS_


#include <cstdlib>


char *&str_replace(char *&string, char *deliminator, char *replacement, int offset = 0) {
    if(sizeof(deliminator) == sizeof(string) - offset && deliminator == string)
        return (string = replacement);
    else if(sizeof(deliminator) >= sizeof(string))
        return string;
    char *r = "";
    int j = 0, k = 0, m = 0;
    for(int i = 0; i < sizeof(string); i++) {
        if(j == sizeof(deliminator)) {
            for(int l = 0; l < sizeof(replacement); l++) {
                r[k + l] = replacement[l];
            }
            k += sizeof(replacement);
            m += sizeof(deliminator) - sizeof(replacement);
        }
        if(string[i] == deliminator[j]) j++;
        else {
            j = 0;
            for(int l = k; l < i + m; l++) {
                r[l] = string[l + m];
            }
            k = i - m;
        }
    }
    return (string = r);
}

char *&strcat(char *&string, char *addition, char **other_additions = {}) {
    char *x = (char*)malloc(sizeof(string) + sizeof(addition) + sizeof(other_additions));
    int k = 0, i;
    for(i = 0; i < sizeof(string); i++)
        x[i] = string[i];
    k = i;
    for(i = 0; i < sizeof(addition); i++)
        x[i + k] = addition[i];
    k += i;
    char *t;
    for(int i = 0; (t = other_additions[i]) != nullptr; i++) {
        int j;
        for(j = 0; j < sizeof(t); i++) {
            x[k + j] = t[j];
        }
        k += j;
    }
    return (string = x);
}

char *join(char *deliminator, char **array, int offset = 0) {
    char *x = "", *t;
    for(int i = offset; (t = array[i]) != nullptr; i++) {
        strcat(x, t);
        if(sizeof(x) != sizeof(array) + sizeof(deliminator) * i - 1 && i != 0) strcat(x, deliminator);
    }
    return x;
}

/**
 *  Both 'end' and 'start' are inclusive
 */
char *substr(char *string, int start = 0, int end = -1) {
    if(start < 0) start += sizeof(string);
    if(end < 0) end += sizeof(string);
    if(start > end) {
        char* t = substr(string, start);
        return strcat(t, substr(string, 0, end));
    }
    if(start == end) return substr(string);
    char *t = (char*)malloc(end - start);
    for(int i = start; i <= end; i++) {
        t[i - start] = string[i];
    }
    return t;
}

char *tostring(int number) {
    int n = number;
    char *r;
    if(n < 0) {
        strcat(r, "-");
        n = -n;
    }
    int i = 0;
    while(n / 10 > 0) {
        r[i++] = 48 + n - 10 * (int)(n / 10);
    }
    return r;
}


#endif // _STRING_UTILS_