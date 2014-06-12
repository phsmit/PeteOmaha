#include "omaha_calc.h"
#include "preflop_holes.h"
#include "eval_omaha.h"

typedef struct counts_t {
    long win;
    long draw;
    long loss;
    
    long my_hand[HandType_COUNT];
    long other_hand[HandType_COUNT];
} counts_t; 

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

static inline HandVal calc_handval(StdDeck_CardMask hole, StdDeck_CardMask board) {
    HandVal val;
    StdDeck_OmahaHi_EVAL(hole, board, &val);
    return val;
} 

static inline void calc_counts(StdDeck_CardMask my_hole, StdDeck_CardMask board, counts_t * counts, int num_trials) {
    HandVal my_value = calc_handval(my_hole, board);
    ++counts->my_hand[HandVal_HANDTYPE(my_value)];
    HandVal other_value;
    
    StdDeck_CardMask used_cards;
    StdDeck_CardMask other_hole;
    StdDeck_CardMask_OR(used_cards, my_hole, board);
    
    
    DECK_MONTECARLO_N_CARDS_D(StdDeck, other_hole, used_cards, 4, num_trials, {
        other_value = calc_handval(other_hole, board);
        ++counts->other_hand[HandVal_HANDTYPE(other_value)];
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
    
    counts_t counts = {0};
    
    switch (StdDeck_numCards(board)) {
        case 0:
            return preflop_probs(hole);
            break;
        case 3:
            DECK_ENUMERATE_2_CARDS_D(StdDeck, new_cards, used_cards, {
                StdDeck_CardMask_OR(complete_board, board, new_cards);
                calc_counts(hole, complete_board, &counts, 200);
            });
            break;
        case 4:
            DECK_ENUMERATE_1_CARDS_D(StdDeck, new_cards, used_cards, {
                StdDeck_CardMask_OR(complete_board, board, new_cards);
                calc_counts(hole, complete_board, &counts, 500);
            });
            break;
        case 5:
            calc_counts(hole, board, &counts, 1000);
            break;
    }
    
    double tot_samples = counts.win + counts.draw + counts.loss;
    po_probs prob;
    prob.win = counts.win / tot_samples;
    prob.draw = counts.draw / tot_samples;
    prob.loss = counts.loss / tot_samples;
    
    normalize_counts(counts.my_hand, prob.my_hands);
    normalize_counts(counts.other_hand, prob.other_hands);
    
    return prob;
}