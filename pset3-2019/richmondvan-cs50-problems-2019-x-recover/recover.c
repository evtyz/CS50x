#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
BYTE IND[4] = {0xff, 0xd8, 0xff, 0xe0};

int indicator(BYTE a[], BYTE b[]);

int convert(int a, char *b);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    int counter = 0;
    int buffer = 512;
    char *output = malloc(100);
    FILE *outptr = fopen("000.jpg", "w");
    do
    {
        BYTE test[buffer];
        if (fread(&test, buffer, 1, inptr) == 0)
        {
            break;
        }
        if (indicator(IND, test) == 0)
        {
            fclose(outptr);
            sprintf(output, "%03d.jpg", counter);
            outptr = fopen(output, "w");
            counter++;
        }


        for (int i = 0; i < 512; i++)
        {
            fwrite(&test[i], 1, 1, outptr);
        }

    }
    while (!feof(inptr));

    // close infile
    fclose(inptr);
    fclose(outptr);
    free(output);



    // success
    return 0;
}

int indicator(BYTE a[], BYTE b[])
{
    int limit = a[3] + 16;
    for (int i = 0; i < 3; i++)
    {
        if (a[i] != b[i])
        {
            return 1;
        }
    }
    if (b[3] < a[3] && b[3] >= limit)
    {
        return 1;
    }
    return 0;
}




