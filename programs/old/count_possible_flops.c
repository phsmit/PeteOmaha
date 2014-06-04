/* 
 * File:   count_possible_flops.c
 * Author: peter
 *
 * Created on June 3, 2014, 3:32 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "poker_defs.h"
#include "parsing.h"

void fill_group(StdDeck_CardMask card, int * groups) {
    int groupid = 0;
    int i;
    for (i = 0; i < 4; ++i) {
        groups[i] = -1;
    }
    
    groups[0] = groupid;
    if (card.cards.spades == card.cards.clubs) groups[1] = groupid;
    if (card.cards.spades == card.cards.diamonds) groups[2] = groupid;
    if (card.cards.spades == card.cards.hearts) groups[3] = groupid;
    
    if (groups[1] < 0) {
        groups[1] = ++groupid;
        if (card.cards.clubs == card.cards.diamonds) groups[2] = groupid;
        if (card.cards.clubs == card.cards.hearts) groups[3] = groupid;
    }
    
    if (groups[2] < 0) {
        groups[2] = ++groupid;
        if (card.cards.diamonds == card.cards.hearts) groups[3] = groupid;
    }
    
    if (groups[3] < 0) {
        groups[3] = ++groupid;
    }
}

int is_sorted_groupwise(StdDeck_CardMask card, int * groups) {
    int vals[4] = {card.cards.spades, card.cards.clubs, card.cards.diamonds, card.cards.hearts};
    
    int groupid, cardid;
    int cur_max;
    for (groupid = 0; groupid < 4; ++groupid) {
        cur_max = 0x2000;
        for(cardid = 0; cardid < 4; ++cardid) {
            if (groups[cardid] == groupid) {
                if (vals[cardid] > cur_max) {
                    return 0;
                } else {
                    cur_max = vals[cardid];
                }
            }
        }
    }
    return 1;
}
/*
 * 
 */
int main(int argc, char** argv) {

    unsigned long count = 0;
    unsigned long local_count = 0;
    
    StdDeck_CardMask hole;
    StdDeck_CardMask board;
    StdDeck_CardMask empty_deck;
    StdDeck_CardMask_RESET(empty_deck);
    
    int group[4];
    
    
    DECK_ENUMERATE_4_CARDS_D(StdDeck, hole, empty_deck, {
        if(hole.cards.spades >= hole.cards.clubs &&
                hole.cards.clubs >= hole.cards.diamonds &&
                hole.cards.diamonds >= hole.cards.hearts) {
                        
            fill_group(hole, group);
            local_count = 0;
            DECK_ENUMERATE_3_CARDS_D(StdDeck, board, hole, {
               if (is_sorted_groupwise(board, group)) {
                   count += 1;
                   local_count += 1;
               }
            });
//            puts(StdDeck_maskString(hole));
            printf("%s: %lu\n", StdDeck_maskString(hole), local_count);
        }
//        
    });
    printf("%lu\n", count);
    return (EXIT_SUCCESS);
    
//        DECK_ENUMERATE_4_CARDS_D(StdDeck, hole, empty_deck, {
    
//    hole = read_cards("[As,Ad,Ac,Ah]");
//        if(hole.cards.spades >= hole.cards.clubs &&
//                hole.cards.clubs >= hole.cards.diamonds &&
//                hole.cards.diamonds >= hole.cards.hearts) {
//                        
//            fill_group(hole, group);
//            local_count = 0;
//            DECK_ENUMERATE_3_CARDS_D(StdDeck, board, hole, {
//               if (is_sorted_groupwise(board, group)) {
//                   count += 1;
//                   local_count += 1;
//               }
//            });
////            puts(StdDeck_maskString(hole));
//            printf("%s: %lu\n", StdDeck_maskString(hole), local_count);
//        }
////        
////    });
//    printf("%lu\n", count);
//    return (EXIT_SUCCESS);
}

