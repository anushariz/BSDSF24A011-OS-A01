// File: src/main.c
#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("--- Testing String Functions ---\n");

    char buf1[50];
    int len = mystrlen("Hello, OS Assignment!");
    printf("mystrlen(\"Hello, OS Assignment!\") = %d\n", len);

    mystrcpy(buf1, "Copied string");
    printf("mystrcpy result: %s\n", buf1);

    char buf2[10];
    mystrncpy(buf2, "TruncateMe", 5);
    buf2[5] = '\0';
    printf("mystrncpy (5 chars) result: %s\n", buf2);

    char buf3[50] = "Hello ";
    mystrcat(buf3, "World!");
    printf("mystrcat result: %s\n", buf3);

    printf("\n--- Testing File Functions ---\n");

    /* Create a sample file to test on */
    FILE* out = fopen("sample.txt", "w");
    if (out == NULL) {
        perror("fopen for writing failed");
        return 1;
    }
    fprintf(out, "This is line one.\n");
    fprintf(out, "This line has the word target in it.\n");
    fprintf(out, "Another line without the keyword.\n");
    fprintf(out, "Second target appears here too.\n");
    fclose(out);

    FILE* in = fopen("sample.txt", "r");
    if (in == NULL) {
        perror("fopen for reading failed");
        return 1;
    }

    int lines, words, chars;
    if (wordCount(in, &lines, &words, &chars) == 0) {
        printf("wordCount -> lines: %d, words: %d, chars: %d\n",
               lines, words, chars);
    } else {
        printf("wordCount failed.\n");
    }

    char** matches = NULL;
    int matchCount = mygrep(in, "target", &matches);
    if (matchCount >= 0) {
        printf("mygrep found %d line(s) containing \"target\":\n", matchCount);
        for (int i = 0; i < matchCount; i++) {
            printf("  %s", matches[i]);
            free(matches[i]);
        }
        free(matches);
    } else {
        printf("mygrep failed.\n");
    }

    fclose(in);
    return 0;
}
