#include "omaha_calc.h"
#include "preflop_holes.h"
#include "eval_omaha.h"

typedef struct counts_t {
    long win;
    long draw;
    long loss;
} counts_t; 

static inline HandVal calc_handval(StdDeck_CardMask hole, StdDeck_CardMask board) {
    HandVal val;
    StdDeck_OmahaHi_EVAL(hole, board, &val);
    return val;
} 

static inline void calc_counts(StdDeck_CardMask my_hole, StdDeck_CardMask board, counts_t * counts) {
    HandVal my_value = calc_handval(my_hole, board);
    HandVal other_value;
    
    StdDeck_CardMask used_cards;
    StdDeck_CardMask other_hole;
    StdDeck_CardMask_OR(used_cards, my_hole, board);
    
    
    DECK_MONTECARLO_N_CARDS_D(StdDeck, other_hole, used_cards, 4, 500, {
        other_value = calc_handval(other_hole, board);
        if (my_value > other_value) counts->win += 1;
        else if (my_value == other_value) counts->draw += 1;
        else counts->loss += 1;            
    });
}

po_probs get_probs(StdDeck_CardMask hole, StdDeck_CardMask board) {
    StdDeck_CardMask used_cards;
    StdDeck_CardMask complete_board;
    StdDeck_CardMask new_cards;
        
    StdDeck_CardMask_OR(used_cards, hole, board);
    
    counts_t counts = {0,0,0};
    
    switch (StdDeck_numCards(board)) {
        case 0:
            return preflop_probs(hole);
            break;
        case 3:
            DECK_ENUMERATE_2_CARDS_D(StdDeck, new_cards, used_cards, {
                StdDeck_CardMask_OR(complete_board, board, new_cards);
                calc_counts(hole, complete_board, &counts);
            });
            break;
        case 4:
            DECK_ENUMERATE_1_CARDS_D(StdDeck, new_cards, used_cards, {
                StdDeck_CardMask_OR(complete_board, board, new_cards);
                calc_counts(hole, complete_board, &counts);
            });
            break;
        case 5:
            calc_counts(hole, board, &counts);
            break;
    }
    
    double tot_samples = counts.win + counts.draw + counts.loss;
    
    po_probs prob = {counts.win / tot_samples, counts.draw / tot_samples, counts.loss / tot_samples};
    return prob;
}