/**
 * @file
 * @brief Printing the words contained in a file "file.txt" in alphabetical order 
 * and also their frequencies
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

/**
 * Structure defining a node in the binary tree
 */
struct Node {
    char *word;
    unsigned int frequency;
    struct Node *left;
    struct Node *right;
};

/**
 * Read words from file to binary tree
 * @param file file to be read from
 * @param root top node of tree
 */
struct Node *readWordsInFileToTree(FILE *file, struct Node *root) {
    char *inputString = (char *)malloc(46 * sizeof(char));
    // longest english word = 45 chars
    // +1 for '\0' = 46 chars
    char inputChar;
    bool isPrevCharAlpha = false;
    int pos = 0;
    while((inputChar = fgetc(file)) != EOF) {
        if(pos > 0)
          isPrevCharAlpha = isalpha(inputString[pos - 1]);
        
        //check if character is letter
        if(isalpha(inputChar)) {
            inputString[pos++] = tolower(inputChar);
            continue;
        }
        
        //check if char is ' or - and if it is preceded by a letter
        //eg yours-not, persons' (valid)
        if((inputChar == '\'' || inputChar == '-') && isPrevCharAlpha) {
            inputString[pos++] = inputChar;
            continue;
        }

        //making sure that there is something valid in inputString
        if(pos == 0) continue;
        
        //if last character is not letter and is not ' then replace by \0
        if(!isPrevCharAlpha && inputString[pos - 1] != '\'') pos--;
        inputString[pos] = '\0';
        pos = 0;
        isPrevCharAlpha = false;
        root = addWordToTree(inputString, root);
    }
    //this is to catch the case for the EOF 
    //being immediately after the last letter or '
    if(pos > 0) {
        if(!isPrevCharAlpha && inputString[pos - 1] != '\'') pos--;
        inputString[pos] = '\0';
        root = addWordToTree(inputString, root);
    }

    free(inputString);
    return root;
}

/**
 * Adding words in to the correct position in the tree
 * @param word word to be inserted in to the tree
 * @param currentNode current node of the tree which we comparing against
 */
struct Node *addWordToTree(char *word, struct Node *currentNode) {
    if(currentNode == NULL) {
        struct Node *currentNode = allocateMemoryForNode();
        currentNode->word = getPointerToWord(word);
        currentNode->frequency = 1;
        currentNode->left = NULL;
        currentNode->right = NULL;
        return currentNode;
    }
    int compared = strcmp(word, currentNode->word);
    
    if(compared > 0)
        currentNode->right = addWordToTree(word, currentNode->right);
    else if(compared < 0) 
        currentNode->left = addWordToTree(word, currentNode->left);
    else{
        currentNode->frequency++;
    }
    return currentNode;
}

/**
 * Writes contents of the tree to another file alphabetically
 * @param node current node to be printed to file
 * @param file pointer to file to be written to
 */
void writeContentOfTreeToFile(struct Node *node, FILE *file) {
    static int i = 1;
    if(node != NULL){
        writeContentOfTreeToFile(node->left, file);
        fprintf(file, "%-5d \t %-9u \t %s \n", i++, node->frequency, node->word);
        writeContentOfTreeToFile(node->right, file);
    }
}

/**
 * Stores a word and returns address to memory
 * @param word word to be stored in memory
 */
char *getPointerToWord(char *word) {
    char *string = (char *)malloc((strlen(word) + 1) * sizeof(char));
    // + 1 is for the '\0' character
    if(string != NULL) {
        strcpy(string, word);
        return string;
    }
    endProgramAbruptly("\n A problem occurred while reserving memory for word \n");
    return NULL;
}

/**
 * Reserves memory capable of storing a node and returns the address
 */
struct Node *allocateMemoryForNode() {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if(node != NULL) return node;
    endProgramAbruptly("\n A problem occured while reserving memory for structure \n");
    return NULL;
}

/**
 * Closes a file when the read or write process is done
 * @param file pointer to file to be closed
 */
void closeFile(FILE *file) {
    int closed = fclose(file);
    if(closed != 0) 
        endProgramAbruptly(" \n A Problem Occurred while closing a file \n");
}

/**
 * Freeing memory when program is terminating
 * @param node pointer to node to free
 */
void freeTreeMemory(struct Node *node) {
    if(node != NULL) {
        freeTreeMemory(node->left);
        freeTreeMemory(node->right);
        free(node->word);
        //freeing node->word because memory was allocated using malloc
        free(node);
        //freeing node because memory was allocated using malloc
    }
}

/**
 * Ending the program due to an error
 * @param errorMessage This is the error message to be printed
 */
void endProgramAbruptly(char *errorMessage) {
    fprintf(stderr, "%s\n", errorMessage);
    exit(EXIT_FAILURE);
}

void test() {
    struct Node *root = NULL;
    FILE *file = NULL;

    file = fopen("file.txt", "r");
    root = readWordsInFileToTree(file, root);
    closeFile(file);

    file = fopen("wordcount.txt", "a");
    fprintf(file, "%-5s \t %9s \t %s \n", "S/N", "FREQUENCY", "WORD");
    writeContentOfTreeToFile(root, file);
    closeFile(file);
    
    freeTreeMemory(root);
    
    return 0;
}

int main(void){
	test();
	return 0;
}
