// File: src/mystrfunctions.c
#include "../include/mystrfunctions.h"

/* Returns number of characters before the terminating '\0' */
int mystrlen(const char* s) {
    int n = 0;
    while (s[n] != '\0')
        n++;
    return n;
}

/* Copies src (including '\0') into dest. Returns number of chars copied
   (not counting '\0'). Caller must make sure dest is big enough. */
int mystrcpy(char* dest, const char* src) {
    int i = 0;
    while ((dest[i] = src[i]) != '\0')
        i++;
    return i;
}

/* Copies at most n chars. Like the real strncpy: if src is shorter than n,
   the rest of dest is padded with '\0'; if src is n or longer, dest is
   NOT null-terminated. Returns number of chars copied from src. */
int mystrncpy(char* dest, const char* src, int n) {
    int i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    int copied = i;
    while (i < n)
        dest[i++] = '\0';
    return copied;
}

/* Appends src at the end of dest. Returns new length of dest. */
int mystrcat(char* dest, const char* src) {
    int d = mystrlen(dest);          // position of dest's '\0'
    int i = 0;
    while ((dest[d + i] = src[i]) != '\0')
        i++;
    return d + i;
}
