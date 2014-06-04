/* 
 * File:   test_starting_hands.c
 * Author: peter
 *
 * Created on June 2, 2014, 10:08 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "poker_defs.h"

/*
 * 
 */
int main(int argc, char** argv) {

    StdDeck_CardMask hole;
    StdDeck_CardMask empty_deck;
    StdDeck_CardMask_RESET(empty_deck);
    
    int total_hands = 0;
    int unique_hands = 0;
    
    DECK_ENUMERATE_4_CARDS_D(StdDeck, hole, empty_deck, {
        total_hands += 1;
        if(hole.cards.spades >= hole.cards.clubs &&
                hole.cards.clubs >= hole.cards.diamonds &&
                hole.cards.diamonds >= hole.cards.hearts) {
            unique_hands += 1;
        }
//        
    });
    
    printf("%d total hands\n%d unique hands\n", total_hands, unique_hands);
    return (EXIT_SUCCESS);
}

