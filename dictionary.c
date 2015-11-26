/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdbool.h>
#include "dictionary.h"
node* wordArray[SIZE];
unsigned int wordsInDictionary = 0;
/**
* Returns the Hash Address of a letter.
*/
unsigned int hashTable(const char* word){
    unsigned int hashAddress = 0;
    for(unsigned int counter = 0; word[counter]!='\0'; counter++){
        hashAddress = word[counter] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
    }
    return (hashAddress % SIZE);
}
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word){
    int wordLength = strlen(word);
    char lowerCase[wordLength];
    
    for(int i = 0; i < wordLength; i++){
        lowerCase[i] = tolower(word[i]);
    }
    lowerCase[wordLength] = '\0';
    node* compareNode = wordArray[hashTable(lowerCase)];
    while(compareNode != NULL){
        if(strcmp(compareNode->word, lowerCase) == 0){
            return true;
        }
        compareNode = compareNode->next;
    }
    return false;
}
/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary){
    FILE* dictWords = fopen(dictionary, "r");
    char* string = malloc((LENGTH + 1) * sizeof(char));
    int index = 0;
    char c;
    while((c = fgetc(dictWords)) != EOF){
        if(c == '\n'){
            string[index] = '\0';
            node* newWordNode = malloc(sizeof(node));
            newWordNode->word = malloc((strlen(string) +1) * sizeof(char));
            newWordNode->next = NULL;
            strcpy(newWordNode->word, string);
            int hashIndex = hashTable(string);
            if((wordArray[hashIndex]) == NULL){
                wordArray[hashIndex] = newWordNode;
            }
            else{
            node* ptr = wordArray[hashIndex];
            while(ptr->next != NULL){
                ptr = ptr->next;
            }
            ptr->next = newWordNode;
            }
            index = 0;
            wordsInDictionary++;
        }
        else{
            string[index] = c;
            index++;
        }
    }
    free(string);
    fclose(dictWords);
    return true;
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void){
    if(wordsInDictionary >= 1){
        return wordsInDictionary;
    }
    return 0;
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void){
    for(int i = 0; i < SIZE; i++){
        while(wordArray[i] != NULL){
            free(wordArray[i]->word);
            node* next = wordArray[i]->next;
            free(wordArray[i]);
            wordArray[i] = next;
        } 
    }
    return true;
}
