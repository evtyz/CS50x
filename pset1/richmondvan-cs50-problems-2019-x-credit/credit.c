#include <cs50.h>
#include <stdio.h>

// Initializing functions
long power(long);
long amex(long);
long mastercard(long);
long visa(long);
long luhn(long, long);
long get_digit_long(long, long);
long sum_digits(long);

// Our main program
int main(void)
{
    long n = get_long("Number: \n");
    if (amex(n) == 1)
    {
        printf("AMEX\n");
    }
    else if (mastercard(n) == 1)
    {
        printf("MASTERCARD\n");
    }
    else if (visa(n) == 1)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Returns 1 if the card is AMEX, and 0 otherwise.
long amex(long n)
{
    if ((n >= 34 * power(13) && n < 35 * power(13)) || (n >= 37 * power(13) && n < 38 * power(13)))
    {
        return luhn(n, 15);
    }
    return 0;
}

// Returns 1 if the card is MASTERCARD, and 0 otherwise.
long mastercard(long n)
{
    if (n >= 51 * power(14) && n < 56 * power(14))
    {
        return luhn(n, 16);
    }
    return 0;
}

// Returns 1 if the card is VISA, and 0 otherwise.
long visa(long n)
{
    if (n >= 4 * power(12) && n < 5 * power(12))
    {
        return luhn(n, 13);
    }
    else if (n >= 4 * power(15) && n < 5 * power(15))
    {
        return luhn(n, 16);
    }
    return 0;    
}

// Returns 10 to the power of n.
long power(long n)
{
    long solution = 1;
    for (int i = 0; i < n; i++)
    {
        solution *= 10;
    }
    return solution;
}

// Returns the dth digit of n.
long get_digit_long(long n, long d)
{
    long remainder = n % power(d);
    long solution = remainder - (remainder % (power(d - 1)));
    return solution / power(d - 1);
}

// Sums up the digits of any number between 1 and 19 inclusive.
long sum_digits(long n)
{
    if (n < 10)
    {
        return n;
    }
    else
    {
        return n - 9;
    }
}

// Checks if a number passes Luhn's algorithm.
long luhn(long n, long d)
{
    long sum = 0;
    long currentDigit;
    for (long i = 1; i <= d; i++)
    {
        if (i % 2 == 0)
        {
            currentDigit = get_digit_long(n, i);
            long add = sum_digits(2 * currentDigit);
            sum += add;
        }
        else
        {
            sum += get_digit_long(n, i);
        }
    }
    if (get_digit_long(sum, 1) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
