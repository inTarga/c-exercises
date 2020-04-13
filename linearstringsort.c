#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//takes a string, and returns a lexically sorted copy in O(n) time.
char* sortString(char inString[]) {
    int strLength = strlen(inString);
    //setting up an int array to store the number of appearances of each character in the string.
    int charCounts[256] = {0};

    //walk the string populating the above array.
    for(int i = 0; i < strLength; i++) {
        charCounts[inString[i]]++;
    }

    //allocate memory for the output string.
    char* outString = malloc(strLength + 1);

    //walk the appearance count array, to put characters in the output string in lexical order.
    int k = 0;
    for(int i = 0; i < 256; i++) {
        for(int j = 0; j < charCounts[i]; j++) {
            outString[k] = i;
            k++;
        }
    }
    //terminate the string.
    outString[strLength] = '\0';

    return outString;
}

int main(int argc, char* argv[]) {
    //only run with 1 command line argument (the string to be sorted).
    if(argc == 2) {
        //sort the string and print the sorted string to stdout.
        printf("%s\n", sortString(argv[1]));
    }

    return 0;
}
