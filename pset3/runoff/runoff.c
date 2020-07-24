#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    // Armado del array CANDIDATES
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    //Los votantes son mas de 100?
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    // i = 0 --> PRIMER VOTANTE
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        // j = 0 ---> PRIMER ELECCION
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }

        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        printf("la menor cantidad de votos obtenidas fue de %i votos", min);
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("Los ganadores son %s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int k = 0; k < candidate_count; k++)
    {
        //Esto funciona, lo que necesito es que no se repita el voto
        //Como no me pide explicitamente que tengo q hacer en caso q se repita el voto, no lo hago
        if (strcmp(name, candidates[k].name) == 0)
        {
            preferences[voter][rank] = k;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        while (candidates[preferences[i][j]].eliminated == true)
        {
            j++;
        }
        candidates[preferences[i][j]].votes++;
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //Chequeo si alguno de los candidates tiene mas de la mayoria(Votantes/2)
    for (int k = 0; k < candidate_count; k++)
    {
        if (candidates[k].votes > voter_count / 2)
        {
            printf("%s\n", candidates[k].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = 100;
    for (int k = 0; k < candidate_count; k++)
    {
        if (!candidates[k].eliminated)
        {
            if (candidates[k].votes < min)
            {
                min = candidates[k].votes;
            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int count_min = 0, count_eliminated = 0, remaining = 0;
    for (int k = 0; k < candidate_count; k++)
    {
        if (candidates[k].eliminated == true)
        {
            count_eliminated++;
        }
        else
        {
            if (candidates[k].votes == min)
            {
                count_min++;
            }
        }
    }
    remaining = candidate_count - count_eliminated;
    if (remaining == count_min)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int k = 0; k < candidate_count; k++)
    {
        if (!candidates[k].eliminated)
        {
            if (candidates[k].votes == min)
            {
                candidates[k].eliminated = true;
            }
        }
    }
    return;
}
