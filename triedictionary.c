#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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
        struct trieNode* nextNode = currNode->children[word[i] - 'a'];
        if(!nextNode)
            return "no definition found";
        currNode = nextNode;
    }

    if(currNode->definition)
        return currNode->definition;
    return "no definition found";
}

void insert(struct trieNode* root, char* word, char* definition) {
    struct trieNode* currNode = root;

    for(int i = 0; i < strlen(word); i++) {
        struct trieNode* nextNode = currNode->children[word[i] - 'a'];
        if(!nextNode)
            nextNode = getNode();
        currNode = nextNode;
    }

    if(!currNode->definition)
        currNode->definition = definition;
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

    free(nodes[wordLen]);
    for(int i = wordLen-1; i > 0; i--) {
        if(nodes[i]->definition)
            break;
        free(nodes[i]);
    }
}

int main() {
    struct trieNode* root = getNode();
    return 0;
}
