#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

//index = 0.0588 * L - 0.296 * S - 15.8
// L = Promedio de letras cada 100 palabras
// S = Promedio de oraciones cada 100 palabras

int main(void)
{
    // CONTADORES: i para caracteres(ciclo for), z para letras, j para palabras y k para oraciones.

    int i = 0, grade = 0;
    float l = 0, s = 0, j = 0, k = 0, z = 0;

    string text = get_string("Text: ");

    for (i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            // Cuento letras
            z++;
        }
        else if (text[i] == ' ')
        {
            // Cuento palabras
            j++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            // Cuento puntuacion
            k++;
        }
    }
    // siempre cuando termine una oracion va a haber un '.', osea que al contador de palabras le va a faltar 1 contar una
    // lo agrego aca

    j++;

    l = (100 * z / j);

    s = (100 * k / j);

    grade = round(0.0588 * l - 0.296 * s - 15.8);

    if (grade >= 1 && grade <= 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }


    //printf("Letras: %0.0f\n", z);

    //printf("Palabras: %0.0f\n", j);

    //printf("Oraciones: %0.0f\n", k);

    //printf("L: %0.2f\n", l);

    //printf("S: %0.2f\n", s);
}