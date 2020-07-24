#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;

bool jorge = true;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf (stderr,"Usage ./recover image\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not read the file\n");
        return 1;
    }
    BYTE buffer[512];
    int imageCount = 0;
    char filename[8];
    FILE *outptr = NULL;
    while (jorge)
    {
        //Leo los bloques y almaceno en bytesRead cuantos leyo, si esta variable es = 0 significa que el return de fread es 0 y que se quedo sin datos pa leer
        size_t bytesRead = fread(buffer, sizeof(BYTE), 512, inptr);
        //Sale del loop cuando termina de leer la tarjeta
        if (bytesRead == 0 && feof(inptr))
        {
            break;
        }
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 && outptr != NULL)
        {
            fclose(outptr);
            imageCount++;
        }
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", imageCount);
            outptr = fopen(filename, "w");
        }
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, outptr);
        }

    }
    fclose(outptr);
    fclose(inptr);
    return 0;
}
