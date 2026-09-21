// File: src/myfilefunctions.c
#include "../include/myfilefunctions.h"
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

/* Counts lines, words, and characters in an already-open file.
   Rewinds the file pointer when done so callers can reuse it. */
int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (file == NULL || lines == NULL || words == NULL || chars == NULL)
        return -1;

    *lines = 0;
    *words = 0;
    *chars = 0;

    int c;
    int inWord = 0; /* 0 = we are currently between words */

    while ((c = fgetc(file)) != EOF) {
        (*chars)++;

        if (c == '\n')
            (*lines)++;

        if (c == ' ' || c == '\t' || c == '\n') {
            inWord = 0;
        } else if (inWord == 0) {
            inWord = 1;
            (*words)++;
        }
    }

    rewind(file);
    return 0;
}

/* Searches every line of fp for search_str. On success, allocates an
   array of heap-allocated strings (the matching lines) into *matches
   and returns how many were found. Caller is responsible for freeing
   each string and the array itself. Returns -1 on failure. */
int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (fp == NULL || search_str == NULL || matches == NULL)
        return -1;

    char line[MAX_LINE_LEN];
    int matchCount = 0;

    /* First pass: count matching lines */
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, search_str) != NULL)
            matchCount++;
    }

    if (matchCount == 0) {
        rewind(fp);
        *matches = NULL;
        return 0;
    }

    *matches = (char**)malloc(matchCount * sizeof(char*));
    if (*matches == NULL) {
        rewind(fp);
        return -1;
    }

    /* Second pass: actually copy the matching lines */
    rewind(fp);
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL && i < matchCount) {
        if (strstr(line, search_str) != NULL) {
            int len = strlen(line);
            (*matches)[i] = (char*)malloc(len + 1);
            if ((*matches)[i] == NULL) {
                /* cleanup on failure */
                for (int j = 0; j < i; j++)
                    free((*matches)[j]);
                free(*matches);
                *matches = NULL;
                rewind(fp);
                return -1;
            }
            strcpy((*matches)[i], line);
            i++;
        }
    }

    rewind(fp);
    return matchCount;
}
