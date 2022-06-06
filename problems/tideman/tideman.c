#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If user's input matched the name of one of the candidates, rank its preferences and return true, else return false
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Checking by pair and incrementing by one the preferences variable
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int index = 0;
    int ties = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Assigning index of winning candidate to the pairs
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[index].winner = i;
                pairs[index].loser = j;
                index++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[index].winner = j;
                pairs[index].loser = i;
                index++;
            }
            else if (preferences[j][i] == preferences[i][j])
            {
                ties++;
            }
        }
    }
    pair_count = (candidate_count * (candidate_count - 1) / 2) - ties;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair tmp;
    while (true)
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            // Sort pairs using bubble sort
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                tmp = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = tmp;
            }
        }
        // Check if everything is in the right order
        int count = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] >= preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                count++;
            }
        }
        if (count == pair_count - 1)
        {
            break;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        bool exit = false;
        while (!exit && winner != loser)
        {
            bool matched = false;
            // Checking by tracing backwards, i.e., winner is defeated by which candidate, and so on until it creates a cycle or there is no more match in the loop
            for (int j = 0; j < candidate_count; j++)
            {
                if (locked[j][winner])
                {
                    matched = true;
                    winner = j;
                }
            }
            if (!matched)
            {
                exit = true;
            }
        }
        if (winner != loser)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int row = 0; row < candidate_count; row++)
    {
        // Check every column in a row, if everything is not locked, it is the source
        bool isLoser = false;
        for (int col = 0; col < candidate_count; col++)
        {
            if (locked[col][row])
            {
                isLoser = true;
            }
        }
        if (isLoser)
        {
            continue;
        }
        else
        {
            printf("%s\n", candidates[row]);
        }
    }
}