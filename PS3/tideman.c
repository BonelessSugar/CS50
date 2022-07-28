//this doesn't work, but I don't want to work on it any longer

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
bool iscycle(int, int);

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
    // ranks[i] is voter's ith preference
    for (int i = 0; i < candidate_count; i++) {
        //candidates[i] = name of candidate
        if (strcmp(candidates[i], name) == 0) {
            ranks[rank] = i;
            //if successfully recorded
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //0, 1, 2, 3
    //0 v 1
    //0 v 2
    //0 v 3
    //1 v 2
    //1 v 3
    //2 v 3
    //works because ranks[i] is the ith person they want in office
    //so they will always prefer i over j
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (i != j && i < j) {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //add all pairs of candidates where
    //one candidate is preferred to the PAIRS array
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            //preference[0][1] > preference[1][0]
            //winner is big, loser is small in preference[i][j]
            //preferences[i][j] is the amount of votes for the preference
            if (preferences[i][j] > preferences[j][i]) {
                //go through each pair starting with the first
                //and update winner and loser
                //then update pair_count

                //[i][j] = [winner][loser]
                //i = index of candidate
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            //else, preference is equal to itself and not counted
            //ex: preference[0][0] vs preference[0][0]
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //sort PAIRS array in descending order of strength of victory
    //AKA, sorted strongest victory to weakest victory
        //strength of victory = number of voters who perfer
            //the preferred candidate
            //= preferences[i][j]
    //if multiple pairs have same strength,
        //assume order does not matter
    //edit: I initially sorted it reverse of what it should be
        //my bad, instructions were unclear

    //1 5 3 4 2 2
    //[5] 1 3 4 2 2
    //5 [4] 3 1 2 2
    //5 4 [3] 1 2 2
    //5 4 3 [2] 2 1
    //5 4 3 2 [2] 1
    for (int i = 0; i < pair_count; i++) {
        //set default to furthest left unsorted number
        int biggestNum = preferences[pairs[i].winner][pairs[i].loser];
        //set default index to it
        int biggestNumIndex = i;
        //iterate through all the remaining unsorted numbers
        for (int j = i + 1; j < pair_count; j++) {
            //if there exists a preference with a higher amount of votes
            //(preference[i][j] is amount of votes i has over j)
            if (preferences[pairs[j].winner][pairs[j].loser] > biggestNum) {
                //set it to the biggest number
                biggestNum = preferences[pairs[j].winner][pairs[j].loser];
                //and update index
                biggestNumIndex = j;
            }
        }
        //update pairs array to set biggest number place to place of
            //last unsorted number
        //store temp value of biggest num's location
        pair temp = pairs[biggestNumIndex];
        //ex:
            //1 5 3 4 2 2
            //1 [1] 3 4 2 2
            //we are setting 5 (index big) to 1 (index i)
        pairs[biggestNumIndex] = pairs[i];
        //then set last unsorted position to biggest number
        //ex:
            //1 5 3 4 2 2
            //[5] 1 3 4 2 2
            //we are setting 1 (index i) to 5 (index big)
        pairs[i] = temp;
    }
    return;
}

//this works because it catches a cycle before one would occur
//therefore no cycles will be made, and none can exist in the locked[][]
bool isCycle(int i, int firstWinner) {
    //if you've returned to the original candidate
    if (i == firstWinner) {
        //a cycle exists
        return true;
    }
    //go through every candidate
    for (int j = 0; j < candidate_count; j++) {
        //if there already exists an arrow
        if (locked[pairs[i].loser][j]) {
            //go into that arrow and check that it doesn't cycle
            return isCycle(j, firstWinner);
        }
    }
    //no cycle has occured
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //create a locked graph
    //adding all edge cases in decreasing order of victory strength
        //so long as the edge would not create a cycle
    //locked[i][j] being true represents the existance
        //of an edge pointing from candidate i to candidate j
    //graph says: charlie is the source (no arrow pointing towards Charlie)
        //so charlie is the winner
    for (int i = 0; i < pair_count; i++) {
        if (!isCycle(i, pairs[i].winner)) {
            //pairs[i].winner is the index of the candidate
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //print out candidate who is the source of the graph
        //there will not be more than one source
    //locked[win][lose] = true
    //arrow from win to lose
    //find the case where candidate has no arrows pointing to them

    //check every candidate
    for (int i = 0; i < candidate_count; i++) {
        //instantiate break variable
        bool lose = false;
        //and check every candidate against them
        for (int j = i + 1; j < candidate_count; j++) {
            if (locked[i][j]) {
                lose = true;
                break;
            }
        }
        if (!lose) {
            printf("%s\n",candidates[i]);
        }
    }
    return;
}
