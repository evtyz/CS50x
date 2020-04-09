#include <cs50.h>
#include <stdio.h>

// Initialize some functions
int get_height(void);
void make_pyramid(int);

// Our main program
int main(void)
{
    int Height = get_height();
    make_pyramid(Height);
}

// Prompts the user for an integer value as "height", and then returns it
int get_height(void)
{
    int Height = 0;
    while (Height < 1 || Height > 8)
    {
        Height = get_int("Height: ");
    }
    return Height;
}

// Prints a pyramid for a given height
void make_pyramid(int Height)
{
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Height + 3 + i; j++)
        {
            if ((Height - j <= i + 1 && j < Height) || j > Height + 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }    
}
