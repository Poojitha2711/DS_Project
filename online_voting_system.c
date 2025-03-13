#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CANDIDATES 5
#define MAX_VOTES 15

struct Candidate {
    char name[50];
    int vote_count;
};

// Queue structure for managing votes
struct Queue {
    int items[MAX_VOTES];
    int front, rear;
};

void enqueue(struct Queue* q, int vote);
int dequeue(struct Queue* q);
void cast_vote(struct Queue* q, int vote);
void count_votes(struct Queue* q, struct Candidate candidates[], int size);

int main() {
    struct Candidate candidates[MAX_CANDIDATES] = {
        {"Aravind Kejriwal", 0}, {"Parvesh Singh", 0}, {"Ramesh Bidhuri", 0}, {"Alka Lamba", 0}, {"Sandeep Dikshit", 0}
    };
    struct Queue voteQueue = {-1, -1}; 
    printf("\t............ONLINE VOTING SYSTEM...........\n\n");

    while (1) {
        int age, vote;
        char id[10];
        
        
        printf("\nEnter age:\n");
        scanf("%d", &age);
        printf("Enter VoterId:\n");
        scanf("%s", id);

        // Validate voter eligibility based on age and voter ID
        if (age < 18 || strlen(id) != 10 || !isalpha(id[0]) || !isdigit(id[3])) {
            printf("You are not eligible to vote.\n");
            break;
        }

        printf("\nYou are eligible to vote!\n\n");
        for (int i = 0; i < MAX_CANDIDATES; i++) {
            printf("Enter %d for %s\n", i + 1, candidates[i].name);
        }
        printf("Enter 6 to exit\n");
        printf("\nEnter your vote:\n");
        scanf("%d", &vote);

        if (vote == 6) break;  
        if (vote >= 1 && vote <= 5) {
            cast_vote(&voteQueue, vote - 1); 
        } else {
            printf("Invalid vote! Please select a valid candidate number.\n");
        }
    }

    count_votes(&voteQueue, candidates, MAX_CANDIDATES);
    
    // Find the candidate with the maximum votes
    int winnerIndex = 0;
    for (int i = 1; i < MAX_CANDIDATES; i++) {
        if (candidates[i].vote_count > candidates[winnerIndex].vote_count) {
            winnerIndex = i;
        }
    }
    
    // Declare the winner
    printf("\nWINNER: %s\n", candidates[winnerIndex].name);

    return 0;
}


void enqueue(struct Queue* q, int vote) {
    if (q->rear < MAX_VOTES - 1) {
        q->items[++q->rear] = vote;
        if (q->front == -1) q->front = 0;  
    }
}

int dequeue(struct Queue* q) {
    if (q->front == -1) return -1; 
    return q->items[q->front++];
}


void cast_vote(struct Queue* q, int vote) {
    enqueue(q, vote);
    printf("Vote Casted Successfully!!!\n");
}


void count_votes(struct Queue* q, struct Candidate candidates[], int size) {
    for (int i = 0; i < size; i++) {
        candidates[i].vote_count = 0;  
    }

    // Count votes from the queue
    for (int i = q->front; i <= q->rear; i++) {
        candidates[q->items[i]].vote_count++;  
    }
}
