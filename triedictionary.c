#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//struct to represent a node in a trie. A root node is used to represent the trie as a whole.
struct trieNode {
    struct trieNode* children[26];
    char* definition;
};

//allocates memory for a trie node and nulls the field pointers. Returns a pointer to that memory.
struct trieNode* getNode() {
    struct trieNode* node = malloc(sizeof(struct trieNode));

    node->definition = NULL;

    for(int i = 0; i < 26; i++)
        node->children[i] = NULL;

    return node;
}

//looks up the definition to a word in a trie, and returns that definition.
char* lookup(struct trieNode* root, char* word) {
    struct trieNode* currNode = root;

    //walking the trie to reach the node that will contain the definition.
    for(int i = 0; i < strlen(word); i++) {
        if(!currNode->children[word[i] - 'a'])
            //return early if the path is incomplete, as the definition can't exist.
            return "no definition found";
        currNode = currNode->children[word[i] - 'a'];
    }

    //return the definition if it exists.
    if(currNode->definition)
        return currNode->definition;
    return "no definition found";
}

//inserts a definition for a word into a trie, if it does not already exist.
void insert(struct trieNode* root, char* word, char* definition) {
    struct trieNode* currNode = root;

    //walking the trie to reach the node that will contain the definition.
    for(int i = 0; i < strlen(word); i++) {
        if(!currNode->children[word[i] - 'a'])
            //create new nodes if the path is incomplete.
            currNode->children[word[i] - 'a'] = getNode();
        currNode = currNode->children[word[i] - 'a'];
    }

    //if the definition doesn't already exist, allocate memory for it, and point to it.
    if(!currNode->definition) {
        currNode->definition = malloc(strlen(definition) + 1);
        strcpy(currNode->definition, definition);
    }
}

//deletes the definition of a word from a trie, and clean up the nodes this obsolesces.
void delete(struct trieNode* root, char* word) {
    size_t wordLen = strlen(word);
    //create an array to hold pointers to the trie nodes that make up the path to where the definition is found.
    struct trieNode** nodes = malloc((wordLen+1)*sizeof(struct trieNode*));
    //the first node in this array is obviously the root.
    nodes[0] = root;

    //walking the trie to reach the node that will contain the definition, while placing nodes into the path array.
    for(int i = 0; i < wordLen; i++) {
        nodes[i+1] = nodes[i]->children[word[i] - 'a'];
        if(!nodes[i+1])
            //if the path is incomplete return early, as the definiton can't exist.
            return;
    }

    //for the last node, check if it has any children
    for(int i = 0; i < 26; i++) {
        if(nodes[wordLen]->children[i]) {
            //if it has, just delete the definition and null the pointer to it.
            free(nodes[wordLen]->definition);
            nodes[wordLen]->definition = NULL;
            //then return early as the path must remain.
            return;
        }
    }

    //delete the definition and null the pointer to it.
    free(nodes[wordLen]->definition);
    free(nodes[wordLen]);

    //walk the path in reverse, cleaning up the nodes until we hit one that has a definition, or is the root.
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
        scanf("%7s", command);

        if(!strcmp(command, "insert")) {
            printf("\nInput a word to insert.\n>");
            scanf("%20s", word);
            //check validity of word?

            printf("\nInput a definition for this word.\n>");
            scanf("%20s", definition);

            insert(root, word, definition);

            printf("\nInsert complete!\n\n");
        } else if (!strcmp(command, "lookup")) {
            printf("\nInput a word to lookup.\n>");
            scanf("%20s", word);
            printf("\nLooking up %s...\n", word);

            printf("\n%s - %s\n\n", word, lookup(root, word));
        } else if (!strcmp(command, "delete")) {
            printf("\nInput a word to delete.\n>");
            scanf("%20s", word);

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
