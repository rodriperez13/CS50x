#include <stdio.h>
#include <math.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//---------------------------------------------------------------------------------------
void Encrypt(char plaintext[], char *argv[], char Ciphertext[]);
void check_input(int argc, char *argv[]);
//---------------------------------------------------------------------------------------
int main(int argc, string argv[])
{
    check_input(argc, argv);

    printf("Enter plaintext: ");
    char plaintext[1000];
    scanf("%[^\n]s", plaintext);

    char Ciphertext[strlen(plaintext)];
    Ciphertext[strlen(plaintext + 1)] = '\0';

    Encrypt(plaintext, argv, Ciphertext);

    printf("ciphertext: %s\n", Ciphertext);
}
//---------------------------------------------------------------------------------------
void check_input(int argc, char *argv[])
{
    int n = 0, i = 0;
    if (argc == 2)
    {
         n = strlen(argv[1]);
         if (n == 26)
         {
             for (int j = 0; j < n; j++)
             {
                 //if ((argv[1][j] >= 'a' && argv[1][j] <= 'z') || (argv[1][j] >= 'A' && argv[1][j] <= 'Z'))
                 if (isalpha(argv[1][j]))
                 {
                    for (int k = j + 1; k <= n; k++)
                    {
                    if(argv[1][j] == argv[1][k])
                        {
                        printf("Key should not contain repeated characters.\n");
                        exit (1);
                        }
                    else
                        {
                        }
                    }
                 }
                 else
                 {
                     printf("Key must only contain alphabetic characters.\n");
                     exit (1);
                 }
             }
         }
         else
         {
             printf("Key must contain 26 characters.\n");
             exit (1);
         }
    }
    else
    {
        printf("Usage ./substitution KEY\n");
        exit (1);
    }
}
//--------------------------------------------------------------------------------------
void Encrypt(char plaintext[], char *argv[], char Ciphertext[])

{

    for(int i = 0; i < strlen(plaintext); i++)
        {
            if (islower(plaintext[i]))
            {
                int position = plaintext[i] - 97;
                Ciphertext[i] = argv[1][position];
                if(islower(Ciphertext[i]))
                {}
                else //if upper, change to lower.
                {
                    Ciphertext[i] += 32;
                }
            }
            else if (isupper(plaintext[i]))
            {
                int position = plaintext[i] - 65;
                Ciphertext[i] = argv[1][position];
                if(isupper(Ciphertext[i]))
                {}
                else //if upper, change to lower.
                {
                    Ciphertext[i] -= 32;
                }

            }
            else
            {
                Ciphertext[i] = plaintext[i];
            }
        }

}
//--------------------------------------------------------------------------------------------------------------------------------------