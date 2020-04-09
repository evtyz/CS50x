// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "dictionary.h"
#include <strings.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char *word;
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 20000;

// Hash table
node *table[N];




/**
 * Adopted from Neel Mehta at https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
 */
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }
    return hash % N;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hashValue = hash(word);
    node *subj = table[hashValue];
    while (subj->next != NULL)
    {
        char *wordcomp = subj->word;
        if (strcasecmp(word, wordcomp) == 0)
        {
            return true;
        }
        subj = subj->next;
    }
    // TODO
    return false;
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        table[i]->next = NULL;
        table[i]->word = NULL;
    }

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    int index = 0;
    char word[LENGTH + 1];
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string
                while ((c = fgetc(file)) != EOF && isalpha(c));

                // Prepare for new word
                index = 0;
            }
        }
        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';
            int hashing = hash(word);
            node *newHash = malloc(sizeof(node));
            int i = 0;
            newHash->word = calloc(1, 46);
            do
            {
                newHash->word[i] = word[i];
                i++;
            }
            while (word[i] != '\0');
            newHash->next = table[hashing];
            table[hashing] = newHash;
            // Prepare for next word
            index = 0;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int num = 0;
    for (int i = 0; i < N; i++)
    {
        node *subj = table[i];
        while (subj->next != NULL)
        {
            subj = subj->next;
            num++;
        }
    }
    return num;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *subj = table[i];
        while (subj->next != NULL)
        {
            node *old = subj;
            subj = subj->next;
            free(old->word);
            free(old);
        }
        free(subj);
    }
    return true;
}
