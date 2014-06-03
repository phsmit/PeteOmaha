/* 
 * File:   test_search.c
 * Author: psmit
 *
 * Created on June 2, 2014, 3:41 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "poker_defs.h"
#include "starting_hands.h"
/*
 * 
 */
int main(int argc, char** argv) {

    fill_uniques();
    
    StdDeck_CardMask hole;
    StdDeck_CardMask empty_deck;
    StdDeck_CardMask_RESET(empty_deck);
    
    
    DECK_ENUMERATE_4_CARDS_D(StdDeck, hole, empty_deck, {
        if(hole.cards.spades >= hole.cards.clubs &&
                hole.cards.clubs >= hole.cards.diamonds &&
                hole.cards.diamonds >= hole.cards.hearts) {
            
//            puts(StdDeck_maskString(hole));
            printf("%s: %d\n", StdDeck_maskString(hole), find_unique_index(hole));
        }
//        
    });
    
    return (EXIT_SUCCESS);
}

