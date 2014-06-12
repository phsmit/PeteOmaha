/* 
 * File:   classify_hands.c
 * Author: peter
 *
 * Created on June 2, 2014, 10:38 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "poker_defs.h"
#include "eval_omaha.h"

/*
 * 
 */

static inline void normalize_counts(long  counts[HandType_COUNT], double  probs[HandType_COUNT]) {
    int i;
    long total = 0;
    for (i = 0; i < HandType_COUNT; ++i) {
        total += counts[i];
    }
    
    for (i = 0; i < HandType_COUNT; ++i) {
        probs[i] = (double)counts[i] / total;
    }
}


typedef struct po_res_counts {
    long losses;
    long wins;
    long draws;
    
    long my_hand[HandType_COUNT];
    long other_hand[HandType_COUNT];
    
} po_res_counts;

static inline void clear_counts(po_res_counts * counts) {
    counts->losses = 0;
    counts->wins = 0;
    counts->draws = 0;
    
    memset(&counts->my_hand, 0, sizeof(long)*(HandType_COUNT));
    memset(&counts->other_hand, 0, sizeof(long)*(HandType_COUNT));
    
}

static inline void hole_chance(StdDeck_CardMask hole, po_res_counts * counts) {
    StdDeck_CardMask board;
    StdDeck_CardMask hole2;
    StdDeck_CardMask used_cards;
    
    HandVal my_score;
    HandVal other_score;
    
//    StdDeck_CardMask_OR(used_cards, hole, board);

    DECK_MONTECARLO_N_CARDS_D(StdDeck, board, hole, 5, 1000, {
        StdDeck_OmahaHi_EVAL(hole, board, &my_score);
        
        ++counts->my_hand[HandVal_HANDTYPE(my_score)];
        
        StdDeck_CardMask_OR(used_cards, hole, board);
        
        DECK_MONTECARLO_N_CARDS_D(StdDeck, hole2, used_cards, 4, 100, {
            StdDeck_OmahaHi_EVAL(hole2, board, &other_score);
            ++counts->other_hand[HandVal_HANDTYPE(other_score)];
            if (my_score > other_score) {
                counts->wins += 1;
            }
            else if (other_score > my_score) {
                counts->losses += 1;
            } else {
                counts->draws += 1;
            }
        } );
    }
            
    );
    
}


int main(int argc, char** argv) {
    size_t nbytes = 100;
    char *line;
    line = (char *) malloc(nbytes + 1);
    
    StdDeck_CardMask hand, card;
    int i, card_i;
    
    po_res_counts counts;
    long sum;
    
    double probs[HandType_COUNT];
    
    while(getline(&line, &nbytes, stdin)  > 0)
    {        
        StdDeck_CardMask_RESET(hand);
        for (i = 0; i < 4; ++i) {
            StdDeck_stringToCard(line+i*3, &card_i); 
            card = StdDeck_MASK(card_i);
            StdDeck_CardMask_OR(hand, hand, card);
        }
        
        
        clear_counts(&counts);
        hole_chance(hand, &counts);
        sum = counts.draws + counts.wins + counts.losses;
        printf("%s %.3f %.3f", StdDeck_maskString(hand), 
                (double) counts.wins / sum ,
                            (double) counts.draws / sum);
        
        normalize_counts(counts.my_hand, probs);
        for (i = 0; i < HandType_COUNT; ++i) {
            printf(" %.3f", probs[i]);
        }
        
//        printf("  ");
        
        normalize_counts(counts.other_hand, probs);
        for (i = 0; i < HandType_COUNT; ++i) {
            printf(" %.3f", probs[i]);
        }
        
        printf("\n");
        
        
    }
    return (EXIT_SUCCESS);
}

