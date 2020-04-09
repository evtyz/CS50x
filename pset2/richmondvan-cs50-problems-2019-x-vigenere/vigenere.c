#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    int keyLength = strlen(argv[1]);
    for (int i = 0; i < keyLength; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            return 1;
        }
    }
    string prompt = get_string("plaintext: ");
    printf("ciphertext: ");
    int counter = 0;
    for (int i = 0; i < strlen(prompt); i++)
    {
        char character = prompt[i];
        if (isalpha(character) == 0)
        {
            printf("%c", character);
            continue;
        }
        int limit;
        if (islower(character) == 0)
        {
            limit = 'A';
        }
        else
        {
            limit = 'a';
        }
        char currentKey = argv[1][counter % strlen(argv[1])];
        int change;
        if (islower(currentKey))
        {
            change = currentKey - 'a';
        }
        else
        {
            change = currentKey - 'A';
        }
        char solution = (character + change - limit) % 26 + limit;
        printf("%c", solution);
        counter++;
    }
    printf("\n");
}
