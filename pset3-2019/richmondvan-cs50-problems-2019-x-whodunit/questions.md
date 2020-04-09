# Questions

## What's `stdint.h`?

Defines the length of certain datatypes, with uint9_t, uint32_t, int32_t, uint16_t.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

So that every variable takes up a given amount of space that can be precalculated.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x4d42

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of the file, biSize is the size of the info header.

## What does it mean if `biHeight` is negative?

It means that the bitmap is built from the top down.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

if the file doesn't exist

## Why is the third argument to `fread` always `1` in our code?

it reads 1 byte of code.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

it moves forward in the memory

## What is `SEEK_CUR`?

position to seek to
