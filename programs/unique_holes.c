/* 
 * File:   print_unique_hands.c
 * Author: peter
 *
 * Created on June 2, 2014, 10:29 AM
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
    
    
    DECK_ENUMERATE_4_CARDS_D(StdDeck, hole, empty_deck, {
        if(hole.cards.spades >= hole.cards.clubs &&
                hole.cards.clubs >= hole.cards.diamonds &&
                hole.cards.diamonds >= hole.cards.hearts) {
            puts(StdDeck_maskString(hole));
            //print hand
        }
//        
    });
    return (EXIT_SUCCESS);
}
