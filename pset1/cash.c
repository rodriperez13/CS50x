#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
    {
        float owed;
        int owed_cents;
        do
        {
            owed = get_float("Change owed: ");
        } while (owed<=0.00);
        owed_cents = round(owed*100);

        int quarters = floor(owed_cents/25);
        owed_cents = owed_cents - quarters*25;

        int dimes = floor(owed_cents/10);
        owed_cents = owed_cents - dimes*10;

        int nickels = floor(owed_cents/5);
        owed_cents = owed_cents - nickels*5;

        int pennies = floor(owed_cents/1);
        owed_cents = owed_cents - pennies;

        int coins = quarters + dimes + nickels + pennies;
        printf ("%i\n", coins);


    }
