/* 
 * File:   calc.c
 * Author: psmit
 *
 * Created on June 9, 2014, 12:52 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "omaha_calc.h"


static inline void calc(int argc, char** argv) {   
    StdDeck_CardMask hole, board;
    StdDeck_CardMask card;
    StdDeck_CardMask_RESET(hole);
    StdDeck_CardMask_RESET(board);
    int i, cardi;
    
    po_probs probs;
    
    for(i = 1; i < 5; ++i) {
       StdDeck_stringToCard(argv[i], &cardi); 
       card = StdDeck_MASK(cardi);
       StdDeck_CardMask_OR(hole, hole, card);
    }
    
            
    if ( argc > 7) {
    for(i = 5; i < argc; ++i) {
       StdDeck_stringToCard(argv[i], &cardi); 
       card = StdDeck_MASK(cardi);
       StdDeck_CardMask_OR(board, board, card);
    }

    }
    
    probs = get_probs(hole, board);
    printf("%.4f", probs.win);
    printf("%.4f", probs.draw);
    
    for (i = 0; i < HandType_COUNT; ++i) {
        printf(" %.3f", probs.my_hands[i]);
    }   
    
    for (i = 0; i < HandType_COUNT; ++i) {
        printf(" %.3f", probs.other_hands[i]);
    }   
    
    
    
    printf("\n");
}

/*
 * 
 */
int main(int argc, char** argv) {
    init_preflop_holes();
    
    if(argc < 5) {
        size_t nbytes = 0;
        char *line = NULL;
        char* cards[15] = {};
        int num_cards;
        int i;
        size_t len;
        
        while(getline(&line, &nbytes, stdin) > 0) {
            len = strlen(line);
            num_cards = 1;
            for (i = 1; i <= len/3; ++i) {
                cards[i] = line + ((i-1) * 3);
                ++num_cards;
            }
            if (num_cards > 1) {
                calc(num_cards, cards);
            }
        }
    } else {
        calc(argc, argv);
    }
    return (EXIT_SUCCESS);
}

