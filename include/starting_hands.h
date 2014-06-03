/* 
 * File:   starting_hands.h
 * Author: psmit
 *
 * Created on June 2, 2014, 3:04 PM
 */

#ifndef STARTING_HANDS_H
#define	STARTING_HANDS_H

#include "poker_defs.h"

#define NUM_UNIQUES 16432

StdDeck_CardMask uniques[NUM_UNIQUES];

static inline void swap(StdDeck_CardMask * a, StdDeck_CardMask * b) {
    StdDeck_CardMask t = *a;
    *a = *b;
    *b = t;
}

int compare_masks(const void *a, const void *b ) {
    const StdDeck_CardMask *arg1 = a;
    const StdDeck_CardMask *arg2 = b;
    
    if (*arg1->cards_n > *arg2->cards_n ) {
        return 1;
    } else if (*arg1->cards_n < *arg2->cards_n) {
        return -1;
    } else {
        return 0;
    }
}

void fill_uniques() {
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
}

StdDeck_CardMask* find_unique(StdDeck_CardMask unique) {
    
    StdDeck_CardMask const * card = bsearch(&unique, uniques, NUM_UNIQUES, sizeof(StdDeck_CardMask), compare_masks );
    return card;
}

static inline void get_unique(StdDeck_CardMask * hand) {
    if (hand->cards.spades < hand->cards.clubs) {
        swap(&hand->cards.spades, &hand->cards.clubs);
    }
    
    if (hand->cards.diamonds < hand->cards.hearts) {
        swap(&hand->cards.diamonds, &hand->cards.hearts);
    }
    
    if (hand->cards.spades < hand->cards.diamonds) {
        swap(&hand->cards.spades, &hand->cards.diamonds);
    }
    
    if (hand->cards.clubs < hand->cards.hearts) {
        swap(&hand->cards.clubs, &hand->cards.hearts);
    }
    
    if (hand->cards.clubs < hand->cards.diamonds) {
        swap(&hand->cards.clubs, &hand->cards.diamonds);
    }
}

void get_starting_hand_probs(StdDeck_CardMask cards, double * win, double * loss, double *draw) {
    
}

#endif	/* STARTING_HANDS_H */

