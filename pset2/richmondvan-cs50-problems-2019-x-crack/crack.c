#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

char ALPHABET[52];
int LOWERCASE = 'a';
int UPPERCASE = 'A';


void printPW(char a[], int b)
{
    for (int i = 0; i < b; i++)
    {
        printf("%c", a[i]);
    }
    printf("\n");
}

int check(char a[], char b[])
{
    for (int i = 0; i < 13; i++)
    {
        if (a[i] != b[i])
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, string argv[])
{
    for (int i = 0; i < 26; i++)
    {
        ALPHABET[2 * i] = LOWERCASE + i;
        ALPHABET[2 * i + 1] = UPPERCASE + i;
    }
    if (argc != 2)
    {
        return 1;
    }
    string hash = argv[1];
    char salt[3];
    salt[2] = '\0';
    for (int i = 0; i < 2; i++)
    {
        salt[i] = hash[i];
    }
    char password1[2];
    password1[1] = '\0';
    for (int a = 0; a < 52; a++)
    {
        password1[0] = ALPHABET[a];
        string finalHash = crypt(password1, salt);
        if (check(hash, finalHash) == 0)
        {
            printPW(password1, 1);
            return 0;
        }
    }
    char password2[3];
    password2[2] = '\0';
    for (int a = 0; a < 52; a++)
    {
        password2[0] = ALPHABET[a];
        for (int b = 0; b < 52; b++)
        {
            password2[1] = ALPHABET[b];
            string finalHash = crypt(password2, salt);
            if (check(hash, finalHash) == 0)
            {
                printPW(password2, 2);
                return 0;
            }
        }
    }
    char password3[4];
    password3[3] = '\0';
    for (int a = 0; a < 52; a++)
    {
        password3[0] = ALPHABET[a];
        for (int b = 0; b < 52; b++)
        {
            password3[1] = ALPHABET[b];
            for (int c = 0; c < 52; c++)
            {
                password3[2] = ALPHABET[c];
                string finalHash = crypt(password3, salt);
                if (check(hash, finalHash) == 0)
                {
                    printPW(password3, 3);
                    return 0;
                }
            }
        }
    }
    char password4[5];
    password4[4] = '\0';
    for (int a = 0; a < 52; a++)
    {
        password4[0] = ALPHABET[a];
        for (int b = 0; b < 52; b++)
        {
            password4[1] = ALPHABET[b];
            for (int c = 0; c < 52; c++)
            {
                password4[2] = ALPHABET[c];
                for (int d = 0; d < 52; d++)
                {
                    password4[3] = ALPHABET[d];
                    string finalHash = crypt(password4, salt);
                    if (check(hash, finalHash) == 0)
                    {
                        printPW(password4, 4);
                        return 0;
                    }
                }
            }
        }
    }
    // 5 letter passwords
    char password5[6];
    password5[5] = '\0';
    for (int a = 0; a < 52; a++)
    {
        password5[0] = ALPHABET[a];
        for (int b = 0; b < 52; b++)
        {
            password5[1] = ALPHABET[b];
            for (int c = 0; c < 52; c++)
            {
                password5[2] = ALPHABET[c];
                for (int d = 0; d < 52; d++)
                {
                    password5[3] = ALPHABET[d];
                    for (int e = 0; e < 52; e++)
                    {
                        password5[4] = ALPHABET[e];
                        string finalHash = crypt(password5, salt);
                        if (check(hash, finalHash) == 0)
                        {
                            printPW(password5, 5);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    
}
