#include "preflop_holes.h"

#include "probtables.h"

static inline void swap(StdDeck_CardMask * a, StdDeck_CardMask * b) {
    StdDeck_CardMask t = *a;
    *a = *b;
    *b = t;
}

int compare_masks(const void *a, const void *b ) {
    const StdDeck_CardMask *arg1 = a;
    const StdDeck_CardMask *arg2 = b;
    
    if (arg1->cards_n > arg2->cards_n ) {
        return 1;
    } else if (arg1->cards_n < arg2->cards_n) {
        return -1;
    } else {
        return 0;
    }
}

void init_preflop_holes() {
    StdDeck_CardMask hole;
    StdDeck_CardMask empty_deck;
    StdDeck_CardMask_RESET(empty_deck);
    
    size_t i = 0;
    DECK_ENUMERATE_4_CARDS_D(StdDeck, hole, empty_deck, {
        if(hole.cards.spades >= hole.cards.clubs &&
                hole.cards.clubs >= hole.cards.diamonds &&
                hole.cards.diamonds >= hole.cards.hearts) {
            uniques[i++] = hole;
        }
    });
    
    qsort(uniques, i, sizeof(StdDeck_CardMask), compare_masks);
};

int get_preflop_index(StdDeck_CardMask hole) {
    if (hole.cards.spades < hole.cards.clubs) {
        hole.cards.spades ^= hole.cards.clubs;
        hole.cards.clubs ^= hole.cards.spades;
        hole.cards.spades ^= hole.cards.clubs;
    }
    
    if (hole.cards.diamonds < hole.cards.hearts) {
        hole.cards.diamonds ^= hole.cards.hearts;
        hole.cards.hearts ^= hole.cards.diamonds;
        hole.cards.diamonds ^= hole.cards.hearts;
    }
    
    if (hole.cards.spades < hole.cards.diamonds) {
        hole.cards.spades ^= hole.cards.diamonds;
        hole.cards.diamonds ^= hole.cards.spades;
        hole.cards.spades ^= hole.cards.diamonds;
    }
    
    if (hole.cards.clubs < hole.cards.hearts) {
        hole.cards.clubs ^= hole.cards.hearts;
        hole.cards.hearts ^= hole.cards.clubs;
        hole.cards.clubs ^= hole.cards.hearts;
    }
    
    if (hole.cards.clubs < hole.cards.diamonds) {
        hole.cards.clubs ^= hole.cards.diamonds;
        hole.cards.diamonds ^= hole.cards.clubs;
        hole.cards.clubs ^= hole.cards.diamonds;
    }
    
    StdDeck_CardMask const * card = bsearch(&hole, uniques, NUM_UNIQUES, sizeof(StdDeck_CardMask), compare_masks );
    return card - uniques;
}

po_probs preflop_probs(StdDeck_CardMask hole) {
    int index = get_preflop_index(hole);
    
    po_probs prob = {win_table[index], draw_table[index], loss_table[index]};
    return prob;
};


