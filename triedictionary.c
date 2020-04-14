#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//struct to represent a node in a trie. A root node is used to represent the trie as a whole.
struct trieNode {
    struct trieNode *children[26];
    char *definition;
    int childCount;
};

//allocates memory for a trie node and nulls the field pointers. Returns a pointer to that memory.
struct trieNode *getNode() {
    struct trieNode *node = malloc(sizeof(struct trieNode));

    node->definition = NULL;

    for (int i = 0; i < 26; i++)
        node->children[i] = NULL;

    return node;
}

//looks up the definition to a word in a trie, and returns that definition.
char *lookup(struct trieNode *root, char *word) {
    struct trieNode *currNode = root;

    //walking the trie to reach the node that will contain the definition.
    for (int i = 0; i < strlen(word); i++) {
        if (!currNode->children[word[i] - 'a'])
            //return early if the path is incomplete, as the definition can't exist.
            return "no definition found";
        currNode = currNode->children[word[i] - 'a'];
    }

    //return the definition if it exists.
    if (currNode->definition)
        return currNode->definition;
    return "no definition found";
}

//inserts a definition for a word into a trie.
void insert(struct trieNode *root, char *word, char *definition) {
    struct trieNode *currNode = root;
    currNode->childCount++;

    //walking the trie to reach the node that will contain the definition.
    for (int i = 0; i < strlen(word); i++) {
        if (!currNode->children[word[i] - 'a'])
            //create new nodes if the path is incomplete.
            currNode->children[word[i] - 'a'] = getNode();
        currNode = currNode->children[word[i] - 'a'];
        currNode->childCount++;
    }

    //free any existing definition, allocate memory for the new one it, and point to it.
    if (currNode->definition)
        free(currNode->definition);
    currNode->definition = malloc(strlen(definition) + 1);
    strcpy(currNode->definition, definition);
}

//deletes the definition of a word from a trie, and clean up the nodes this obsolesces.
void delete(struct trieNode *root, char *word) {
    //first check that the definition actually exists...
    if (!strcmp(lookup(root, word), "no definition found"))
        return;

    //walk the trie.
    struct trieNode *currNode = root;
    struct trieNode *nextNode;
    for (int i = 0; i < strlen(word); i++) {
        nextNode = currNode->children[word[i] - 'a'];
        //decrement childCount since we're going to be removing a child.
        currNode->childCount--;

        //if the next node will have no children, null the pointer to it.
        if (nextNode->childCount == 1)
            currNode->children[word[i] - 'a'] = NULL;

        //if this node has no children and isn't the root, free it.
        if (currNode->childCount == 0 && i != 0)
            free(currNode);

        currNode = nextNode;
    }

    //clean up the final node.
    free(currNode->definition);
    currNode->definition = NULL;
    if (currNode->childCount == 0)
        free(currNode);
}

int main() {
    struct trieNode *root = getNode();
    char command[7];
    char word[20];
    char definition[20];

    printf("Welcome to the trie dictionary. ");

    while (true) {
        printf("Please input one of the following commands:\n  insert, lookup, delete, quit.\n>");
        scanf("%7s", command);

        if (!strcmp(command, "insert")) {
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
