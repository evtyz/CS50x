// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    double f = atof(argv[1]);
    if (f < 0 || f > 100)
    {
        fprintf(stderr, "f must be between 0 and 100\n");
        return 1;
    }
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }


    BITMAPFILEHEADER nbf;
    BITMAPINFOHEADER nbi;

    nbi.biWidth = (int)(f * bi.biWidth);
    nbi.biHeight = (int)(f * bi.biHeight);

    int finalWidth[nbi.biWidth];
    int finalHeight[abs(nbi.biHeight)];

    for (int i = 0; i < nbi.biWidth; i++)
    {
        finalWidth[i] = floor((float) i / nbi.biWidth * bi.biWidth);
    }
    for (int i = 0; i < abs(nbi.biHeight); i++)
    {
        finalHeight[i] = floor((float) i / abs(nbi.biHeight) * abs(bi.biHeight));
    }

    int paddingReq;
    if (nbi.biWidth % 4 == 0)
    {
        paddingReq = 0;
    }
    else
    {
        paddingReq = 4 - (nbi.biWidth * 3 % 4);
    }

    nbi.biSizeImage = (3 * nbi.biWidth + paddingReq) * abs(nbi.biHeight);

    nbf.bfType = bf.bfType;
    nbf.bfSize = 54 + nbi.biSizeImage;
    nbf.bfReserved1 = bf.bfReserved1;
    nbf.bfReserved2 = bf.bfReserved2;
    nbf.bfOffBits = bf.bfOffBits;

    nbi.biSize = bi.biSize;
    nbi.biPlanes = bi.biPlanes;
    nbi.biBitCount = bi.biBitCount;
    nbi.biCompression = bi.biCompression;
    nbi.biXPelsPerMeter = bi.biXPelsPerMeter;
    nbi.biYPelsPerMeter = bi.biYPelsPerMeter;
    nbi.biClrUsed = bi.biClrUsed;
    nbi.biClrImportant = bi.biClrImportant;

    // write outfile's BITMAPFILEHEADER
    fwrite(&nbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&nbi, sizeof(BITMAPINFOHEADER), 1, outptr);




    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    RGBTRIPLE original[abs(bi.biHeight)][bi.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {

            // read RGB triple from infile
            fread(&original[i][j], sizeof(RGBTRIPLE), 1, inptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }


    for (int i = 0, biHeight = abs(nbi.biHeight); i < biHeight; i++)
    {
        int ogH = finalHeight[i];
        // iterate over pixels in scanline
        for (int j = 0; j < nbi.biWidth; j++)
        {
            int ogW = finalWidth[j];
            RGBTRIPLE triple = original[ogH][ogW];
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
        // then add it back (to demonstrate how)
        for (int k = 0; k < paddingReq; k++)
        {
            fputc(0x00, outptr);
        }
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
