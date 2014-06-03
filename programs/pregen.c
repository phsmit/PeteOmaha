/* 
 * File:   pregen.c
 * Author: psmit
 *
 * Created on May 30, 2014, 1:01 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "poker_defs.h"
#include "eval_omaha.h"


typedef struct po_res_counts {
    long losses;
    long wins;
    long draws;
} po_res_counts;

void clear_counts(po_res_counts * counts) {
    counts->losses = 0;
    counts->wins = 0;
    counts->draws = 0;
}

static inline void get_win(StdDeck_CardMask my_hole,StdDeck_CardMask other_hole, StdDeck_CardMask board, po_res_counts * counts) {
    
//    fprintf(stderr, "my hole: %s\n", StdDeck_maskString(my_hole));
//    fprintf(stderr, "ot hole: %s\n", StdDeck_maskString(other_hole));
//    fprintf(stderr, "board  : %s\n", StdDeck_maskString(board));
    
    HandVal my_score;
    HandVal other_score;
    StdDeck_OmahaHi_EVAL(my_hole, board, &my_score);
    StdDeck_OmahaHi_EVAL(other_hole, board, &other_score);
    
//    fprintf(stderr, "mine: %s\n", handTypeNamesPadded[HandVal_HANDTYPE(my_score)]);
//    fprintf(stderr, "othe: %s\n", handTypeNamesPadded[HandVal_HANDTYPE(other_score)]);
    
    if (my_score > other_score) {
        counts->wins += 1;
    }
    else if (other_score > my_score) {
        counts->losses += 1;
    } else {
        counts->draws += 1;
    }
    
}

static inline void hole_chance(StdDeck_CardMask hole, po_res_counts * counts) {
    StdDeck_CardMask board;
    StdDeck_CardMask hole2;
    StdDeck_CardMask used_cards;
    
//    StdDeck_CardMask_OR(used_cards, hole, board);

    DECK_MONTECARLO_N_CARDS_D(StdDeck, board, hole, 5, 10000, {
        StdDeck_CardMask_OR(used_cards, hole, board);
        DECK_MONTECARLO_N_CARDS_D(StdDeck, hole2, used_cards, 4, 10000, {
            get_win(hole, hole2, board, counts);
        } );
    }
            
    );
    
}


/*
 * 
 */
int main(int argc, char** argv) {
    
    StdDeck_CardMask hole;
    StdDeck_CardMask empty_deck;
    StdDeck_CardMask_RESET(empty_deck);
    
    po_res_counts counts;
    long sum;// = counts.draws + counts.wins + counts.losses;
    
    DECK_ENUMERATE_4_CARDS_D(StdDeck, hole, empty_deck, {
        clear_counts(&counts);
        hole_chance(hole, &counts);
        sum = counts.draws + counts.wins + counts.losses;
        printf("%.2f %.2f %.2f %s\n", (double) counts.wins / (double)sum * 100.0,
                            (double) counts.draws / (double)sum * 100.0,
                            (double) counts.losses / (double)sum * 100.0, StdDeck_maskString(hole));
//        
    });
    return (EXIT_SUCCESS);
}

