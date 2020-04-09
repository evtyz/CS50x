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
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            return 1;
        }
    }
    int key = atoi(argv[1]);
    string prompt = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(prompt); i++)
    {
        int originalCode = prompt[i];
        if ((originalCode >= (int)'A' && originalCode <= (int)'Z') || (originalCode >= (int)'a' && originalCode <= (int)'z'))
        {
            int lowLimit;
            if (isupper(prompt[i]) != 0)
            {
                lowLimit = (int)'A';
            }
            else
            {
                lowLimit = (int)'a';
            }
            int charCode = ((originalCode + key) - lowLimit) % 26 + lowLimit;
            printf("%c", charCode);            
        }
        else
        {
            printf("%c", prompt[i]);
        }
    }
    printf("\n");
    return 0;
}
