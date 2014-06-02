/* 
 * File:   classify_hands.c
 * Author: peter
 *
 * Created on June 2, 2014, 10:38 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "poker_defs.h"
#include "eval_omaha.h"

/*
 * 
 */

typedef struct po_res_counts {
    long losses;
    long wins;
    long draws;
} po_res_counts;

static inline void clear_counts(po_res_counts * counts) {
    counts->losses = 0;
    counts->wins = 0;
    counts->draws = 0;
}

static inline void hole_chance(StdDeck_CardMask hole, po_res_counts * counts) {
    StdDeck_CardMask board;
    StdDeck_CardMask hole2;
    StdDeck_CardMask used_cards;
    
    HandVal my_score;
    HandVal other_score;
    
//    StdDeck_CardMask_OR(used_cards, hole, board);

    DECK_MONTECARLO_N_CARDS_D(StdDeck, board, hole, 5, 10000, {
        StdDeck_OmahaHi_EVAL(hole, board, &my_score);
        
        StdDeck_CardMask_OR(used_cards, hole, board);
        
        DECK_MONTECARLO_N_CARDS_D(StdDeck, hole2, used_cards, 4, 1000, {
            StdDeck_OmahaHi_EVAL(hole2, board, &other_score);
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
    
    
    while(getline(&line, &nbytes, stdin)  > 0)
    {
        //strip newline
//        line[strlen(line)-2] = '\0';
        
        StdDeck_CardMask_RESET(hand);
        for (i = 0; i < 4; ++i) {
            StdDeck_stringToCard(line+i*3, &card_i); 
            card = StdDeck_MASK(card_i);
            StdDeck_CardMask_OR(hand, hand, card);
        }
        
        
        clear_counts(&counts);
        hole_chance(hand, &counts);
        sum = counts.draws + counts.wins + counts.losses;
        printf("%s %.2f %.2f %.2f\n", StdDeck_maskString(hand), (double) counts.wins / (double)sum * 100.0,
                            (double) counts.draws / (double)sum * 100.0,
                            (double) counts.losses / (double)sum * 100.0);
        
        
        
    }
    return (EXIT_SUCCESS);
}

