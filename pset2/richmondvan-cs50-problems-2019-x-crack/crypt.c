#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

int main(void)
{
    string a = crypt("a", "50");
    printf("%s\n", a);
}
// 50XcgR31jl/4M
// 50OqznXGVcOJU
