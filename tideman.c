#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 9
//preferences[i][j]-number of voters who prefers i over j
//locked[i][j] means that arrow from i to j is fixed
int preferences[MAX][MAX];
bool locked[MAX][MAX];
typedef struct{
    int winner;
    int loser;
} pair;
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int pair_count;
int candidate_count;
//function for a voter's vote
bool vote(int rank, char name[], int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int start, int end);

int main(int argc, char *argv[]){
    if( argc < 2){
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }
    candidate_count = argc - 1;
    if(candidate_count > MAX){
        printf("Maximum number of candidates is %d\n", MAX);
        return 2;
    }
    //adding candidates
    for(int i = 0; i < candidate_count; i++){
        candidates[i] = argv[i + 1];
    }
    //Reset matrix locked
    for(int i = 0; i < candidate_count; i++){
        for( int j = 0; j < candidate_count; j++){
            locked[i][j] = false;
        }
    }
     pair_count = 0;
     int voter_count;
     printf("Number of voters: ");
     scanf("%d", &voter_count);
     for(int i = 0; i < voter_count; i++){
        int ranks[candidate_count];
        for(int j = 0; j < candidate_count; j++){
            char name[50];
            printf("Rank %d: ", j + 1);
            scanf("%s", name);
            if(!vote(j, name, ranks)){
                printf("Invalid vote. \n");
                return 1;
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

bool vote(int rank, char name[], int ranks[]){
     for( int i = 0; i < candidate_count; i++){
        if(strcmp(candidates[i], name) == 0){
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

//updating matrices of preferences for one voter 
void record_preferences(int ranks[]){
    for(int i = 0; i < candidate_count; i++){
        for(int j = i + 1; j < candidate_count; j++){
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// creating array of pairs
void add_pairs(void){
    pair_count = 0;
    for(int i = 0; i < candidate_count; i++){
        for( int j = i + 1; j < candidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if(preferences[j][i] > preferences[i][j]){
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// sorting pairs by the winning
void sort_pairs(void){
    for(int i = 0; i < pair_count - 1; i++){
        for( int j = 0; j < pair_count - i - 1;j++){
            int strength1 = preferences[pairs[j].winner][pairs[j].loser];
            int strength2 = preferences[pairs[j+1].winner][pairs[j+1].loser];
            if(strength1 < strength2){
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

bool check_cycle(int start, int end){
    // if we are coming to the start cycle ends
    if(end == start){
        return true;
    }
    for( int i = 0; i < candidate_count;i++){
        //if we have arrow from current element(end) to i
        if(locked[end][i]){
            if(check_cycle(start, i)){
                return true;
            }
        }
    }
    return false;
}

// locking pairs while cheking cycle
void lock_pairs(void){
   for(int i = 0; i < pair_count; i++){
    //checking, can't we reach from loser to winner
    if(!check_cycle(pairs[i].winner, pairs[i].loser)){
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
   }
}

// showing the winner
void print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        bool is_loser = false;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                is_loser = true;
                break;
            }
        }
        if (!is_loser) {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}