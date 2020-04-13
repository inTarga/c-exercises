#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct trieNode {
    struct trieNode* children[26];
    char* definition;
};

struct trieNode* getNode() {
    struct trieNode* node = malloc(sizeof(struct trieNode));

    node->definition = NULL;

    for(int i = 0; i < 26; i++)
        node->children[i] = NULL;

    return node;
}

char* lookup(struct trieNode* root, char* word) {
    struct trieNode* currNode = root;

    for(int i = 0; i < strlen(word); i++) {
        if(!currNode->children[word[i] - 'a'])
            return "no definition found";
        currNode = currNode->children[word[i] - 'a'];
    }

    if(currNode->definition)
        return currNode->definition;
    return "no definition found";
}

void insert(struct trieNode* root, char* word, char* definition) {
    struct trieNode* currNode = root;

    for(int i = 0; i < strlen(word); i++) {
        if(!currNode->children[word[i] - 'a'])
            currNode->children[word[i] - 'a'] = getNode();
        currNode = currNode->children[word[i] - 'a'];
    }

    if(!currNode->definition)
        currNode->definition = malloc(strlen(definition) + 1);
        strcpy(currNode->definition, definition);
}

void delete(struct trieNode* root, char* word) {
    int wordLen = strlen(word);
    struct trieNode** nodes = malloc((wordLen+1)*sizeof(struct trieNode*));
    nodes[0] = root;

    for(int i = 0; i < wordLen; i++) {
        nodes[i+1] = nodes[i]->children[word[i] - 'a'];
        if(!nodes[i+1])
            break;
    }

    for(int i = 0; i < 26; i++) {
        if(nodes[wordLen]->children[i]) {
            nodes[wordLen]->definition = NULL;
            return;
        }
    }

    free(nodes[wordLen]);
    for(int i = wordLen - 1; i >= 0; i--) {
        if(nodes[i]->definition){
            nodes[i]->children[word[i] - 'a'] = NULL;
            break;
        }
        if(i == 0) {
            nodes[i]->children[word[i] - 'a'] = NULL;
        } else {
            free(nodes[i]);
        }
    }
}

int main() {
    struct trieNode* root = getNode();
    char command[7];
    char word[20];
    char definition[20];

    printf("Welcome to the trie dictionary. ");

    while(true) {
        printf("Please input one of the following commands:\n  insert, lookup, delete, quit.\n>");
        scanf("%s", command);

        if(!strcmp(command, "insert")) {
            printf("\nInput a word to insert.\n>");
            scanf("%s", word);
            //check validity of word?

            printf("\nInput a definition for this word.\n>");
            scanf("%s", definition);

            insert(root, word, definition);

            printf("\nInsert complete!\n\n");
        } else if (!strcmp(command, "lookup")) {
            printf("\nInput a word to lookup.\n>");
            scanf("%s", word);
            printf("\nLooking up %s...\n", word);

            printf("\n%s - %s\n\n", word, lookup(root, word));
        } else if (!strcmp(command, "delete")) {
            printf("\nInput a word to delete.\n>");
            scanf("%s", word);

            delete(root, word);

            printf("\nDelete complete!\n\n");
        } else if (!strcmp(command, "quit")) {
            break;
        } else {
            printf("\nCommand not recognised.\n");
        }
    }

    printf("\nGoodbye.\n");
    return 0;
}
