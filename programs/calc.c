/* 
 * File:   calc.c
 * Author: psmit
 *
 * Created on June 9, 2014, 12:52 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "omaha_calc.h"


/*
 * 
 */
int main(int argc, char** argv) {
    init_preflop_holes();
    
    StdDeck_CardMask hole, board;
    StdDeck_CardMask card;
    StdDeck_CardMask_RESET(hole);
    StdDeck_CardMask_RESET(board);
    int i, cardi;
    if(argc < 5) return (EXIT_FAILURE);
    
    for(i = 1; i < 5; ++i) {
       StdDeck_stringToCard(argv[i], &cardi); 
       card = StdDeck_MASK(cardi);
       StdDeck_CardMask_OR(hole, hole, card);
    }
    po_probs probs;
    probs = get_probs(hole, board);
    printf("%.4f", probs.win + probs.draw);
            
    if ( argc > 7) {
    for(i = 5; i < 8; ++i) {
       StdDeck_stringToCard(argv[i], &cardi); 
       card = StdDeck_MASK(cardi);
       StdDeck_CardMask_OR(board, board, card);
    }
    probs = get_probs(hole, board);
    printf(" %.4f", probs.win + probs.draw);
    }
    
    if ( argc > 8) {
        i = 8;
       StdDeck_stringToCard(argv[i], &cardi); 
       card = StdDeck_MASK(cardi);
       StdDeck_CardMask_OR(board, board, card);
    
    probs = get_probs(hole, board);
    printf(" %.4f", probs.win + probs.draw);
    }
    
    if ( argc > 9) {
        i = 9;
       StdDeck_stringToCard(argv[i], &cardi); 
       card = StdDeck_MASK(cardi);
       StdDeck_CardMask_OR(board, board, card);
    
    probs = get_probs(hole, board);
    printf(" %.4f", probs.win + probs.draw);
    }
    
    
    
    
    printf("\n");
    return (EXIT_SUCCESS);
}

