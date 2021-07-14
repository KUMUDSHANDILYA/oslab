#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void countWords(char a[], int n) {
    int i = 0, count=0;
    while(a[i] != '\0' && n != 0) {
        if (a[i] == ' ' && a[i+1] != '\0') {
            count++;
        }
        i++;
    }
    if (n != 0) {
        count++;
    }
    printf("Number of words = %d\n", count);
}

void countVowels(char a[], int n) {
    int i = 0, count=0;
    while(a[i] != '\0' && n != 0) {
        if (a[i] == 'a' || a[i] == 'A'
            || a[i] == 'e' || a[i] == 'E'
            || a[i] == 'i' || a[i] == 'I'
            || a[i] == 'o' || a[i] == 'O'
            || a[i] == 'u' || a[i] == 'U') {
            count++;
        }
        i++;
    }
    printf("Number of Vowels = %d\n", count);
}

int main(int* agc, char* argv[]) {
    char line[] = "This is a sample sentence";
    int length = strlen(line);
    int id = fork();
    if (id == 0) {
        wait(NULL);
        countWords(line, length);
        printf("Child process terminated...\n");
    } else {
        countVowels(line, length);
        printf("Parent Process terminated...\n");
        //wait(NULL);
    }
    return 0;
}
