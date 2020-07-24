#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>

char get_index(c)
{
    if (c == '\'')
    {
        return 27;
    }
    else if (c >= 'a' && c <= 'z')
    {
        return c - 'a';
    }
    else if (c == ' ')
    {
        return -1;
    }
    else if (c >= 'A' && c <= 'Z')
    {
        return c - 'A';
    }
    return -2;
}

int main()
{
    FILE *fp = fopen("hpla.txt", "r");
    while(true)
    {
        char c = fgetc(fp);
        int index = get_index(c);
        if(feof(fp))
        {
            break;
        }
        else
        {
            printf("%c   %i \n",c,index);
            break;
        }
    }
}

