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
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
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
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
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
    for (int i = 0; i < candidate_count; i++) {
        //check if voter put in valid candidate name
        if (strcmp(candidates[i].name, name) == 0) {
            //add candidate INDEX to rank in voter preference
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //update number of VOTES each candidate has
    //every voter votes for their top-preferred candidate
        //who has not already been eliminated

    //while main loop already resets all candidate votes to zero every loop

    //preference[i][j] = candidate index

    //go through each voter
    for (int i = 0; i < voter_count; i++) {
        //go through each of their votes
        //assume that all voters will rank all of
        //the candidates in their preferred order.
        for (int j = 0; j < candidate_count; j++) {
            //if their candidate is not eliminated,
            if (candidates[preferences[i][j]].eliminated == false) {
                //add a vote to them
                candidates[preferences[i][j]].votes++;
                //then go to the next voter
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //if a candidate has more than half the votes
    for (int i = 0; i < candidate_count; i++) {
        //MISTAKE WAS CANDIDATE_COUNT INSTEAD OF VOTER_COUNT
        if (candidates[i].votes > voter_count * 0.5) {
            //print winner
            printf("%s\n",candidates[i].name);
            //return true
            return true;
        }
    }
    //else, return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //used to eliminate last place candidate(s)
    int minVotes = voter_count;
    for (int i = 0; i < candidate_count; i++) {
        //make sure theyre not already eliminated
        if (candidates[i].eliminated == false) {
            if (candidates[i].votes < minVotes) {
                minVotes = candidates[i].votes;
            }
        }
    }
    return minVotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int remainCandidates = 0;
    //go through and see how many candidates are left
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].eliminated == false) {
            remainCandidates++;
        }
    }
    //then see if the number of candidates with the minimum amount of votes
    //is equal to the number of remaining candidates
    int minCandidates = 0;
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].eliminated == false) {
            if (candidates[i].votes == min) {
                minCandidates++;
            }
        }
    }
    if (minCandidates == remainCandidates) {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == min) {
            candidates[i].eliminated = true;
        }
    }
    return;
}
