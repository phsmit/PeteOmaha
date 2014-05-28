/* 
 * File:   my_poker_calc.h
 * Author: psmit
 *
 * Created on May 27, 2014, 11:37 AM
 */

#ifndef MY_POKER_CALC_H
#define	MY_POKER_CALC_H

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

void get_win_chance(StdDeck_CardMask hole, StdDeck_CardMask board, po_res_counts * counts) {
    StdDeck_CardMask gen_cards;
    StdDeck_CardMask new_board;
    StdDeck_CardMask used_cards;
    StdDeck_CardMask_OR(used_cards, hole, board);
   
    switch (StdDeck_numCards(board)) {
        case 3:
            DECK_ENUMERATE_2_CARDS_D(StdDeck, gen_cards, used_cards, {
            StdDeck_CardMask_OR(new_board, board, gen_cards);
            get_win_chance(hole, new_board, counts);
            });
            break;
        case 4:
            DECK_ENUMERATE_1_CARDS_D(StdDeck, gen_cards, used_cards, {
            StdDeck_CardMask_OR(new_board, board, gen_cards);
            get_win_chance(hole, new_board, counts);
            });
            break;
        case 5:
//            DECK_ENUMERATE_4_CARDS_D(StdDeck, gen_cards, used_cards, {
//                get_win(hole, gen_cards, board, counts);
//            }
            
            DECK_MONTECARLO_N_CARDS_D(StdDeck, gen_cards, used_cards, 4, 500, {
                get_win(hole, gen_cards, board, counts);
            }
            
            );
            break;
    }
}



#endif	/* MY_POKER_CALC_H */

