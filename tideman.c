//function for a voter's vote
bool vote(int rank, char name[], int ranks[]){
    for( int i = 0; i < cantidate_count; i++){
        if(strcmp(cantidates[i], name) == 0){
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}
//updating matrices of preferences for one voter 
void record_preferences(int ranks[]){
    for(int i = 0; i < cantidated_count; i++){
        for(int j = i + 1; j < cantidate_count; j++){
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}
// creating array of pairs
void add_pairs(void){
    pair_count = 0;
    for(int i = 0; i < cantidate_count; i++){
        for( int j = 0; j < cantidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}
// sorting pairs by the winning
void sort_pairs(void){
    for(int i = 0; i < pair_count - 1; i++){
        for( int j = 0; j < pair_count - i - 1;j++){
            int strength1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int strength2 = preferences[pairs[j+1].winner][pairs[j+1].loser] - preferences[pairs[j+1].loser][pairs[j+1].winner];
            if(strength1 < strength2){
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}
// locking pairs while cheking cycle
void lock_pairs(void){
    for( int i = 0; i < cantidate_count; i++){
        bool is_loser = false;
        for(int j = 0; j < cantidate_count; j ++){
            if(locked[j][i]){
                is_loser = true;
                break;
            }
        }
        if(!is_loser){
            printf("%s\n",cantidates[i]);
            return;
        }
    }
}
