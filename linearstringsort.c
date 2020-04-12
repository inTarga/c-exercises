#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* sortString(char inString[]) {
    int strLength = strlen(inString);
    int charCounts[256] = {0};

    for(int i = 0; i < strLength; i++) {
        charCounts[inString[i]]++;
    }

    char* outString = malloc(strLength + 1);

    int k = 0;
    for(int i = 0; i < 256; i++) {
        for(int j = 0; j < charCounts[i]; j++) {
            outString[k] = i;
            k++;
        }
    }
    outString[strLength] = '\0';

    return outString;
}

int main(int argc, char* argv[]) {
    if(argc == 2) {
        printf("%s\n", sortString(argv[1]));
    }

    return 0;
}
