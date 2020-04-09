#include <stdio.h>
#include <cs50.h>

// This is the program!
int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}
