/* 
 * File:   parsing.h
 * Author: psmit
 *
 * Created on May 26, 2014, 3:03 PM
 */

#ifndef PARSING_H
#define	PARSING_H

#include "poker_defs.h"

#include <string.h>

typedef enum {
    PLAYER1,
    PLAYER2
} Player;

typedef struct po_settings {
    int time_bank;
    int time_per_move;
    int hands_per_level;
    int starting_stack;
    Player my_player;
} po_settings;

typedef struct po_match {
    int round;
    
    int stage; // 0=preflop, 1=flop, 2=turn, 3=river
    int small_blind;
    int big_blind;
    Player on_button;
    int my_stack;
    int opponent_stack;
    
    int max_win_pot;
    int amount_to_call;
    
    StdDeck_CardMask my_hand;
    StdDeck_CardMask table;
    
    int* bets;
    
} po_match;

int po_parse_next_line(char* line, po_match * match, po_settings * settings) {
    char* keyword_one = strtok(line, " ");
    char* keyword_two = strtok(NULL, " ");
    char* value = strtok(NULL, " ");
    
    if (!strcmp(keyword_one, "Setting")) {
        
    }
    else if (!strcmp(keyword_one, "Match")) {
        
    }
    else if (!strcmp(keyword_one, "Action")) {
        return atoi(value);
    }
    return 0;
}

#endif	/* PARSING_H */

